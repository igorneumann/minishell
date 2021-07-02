/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineumann <ineumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 19:10:34 by ineumann          #+#    #+#             */
/*   Updated: 2021/07/02 19:02:43 by ineumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pipes(t_cmd *cmd)
{
	int		i;
	int		j;

	i = ft_strlen(cmd->in);
	while (i > 0)
	{
		j = 1;
		if (cmd->in[i] == '|')
		{
			cmd->in[i] = '\0';
			while (cmd->in[i + j] == ' ')
				j++;
			ft_lst_add_front(&cmd->nexpip, ft_new(&cmd->in[i + j]));
		}
		else if (cmd->in[i] == '>')
		{
			cmd->in[i] = '\0';
			while (cmd->in[i + j] == ' ')
				j++;
			cmd->outp = ft_strdup(&cmd->in[i + j]);
		}
		i--;
	}
	return (0);
}

void	ft_startpipe(char *str, t_cmd *cmd)
{
	int		status;
	int		pid;
	char	**parmList;

	pid = fork();
	parmList = copyparam(cmd);
	if (pid == 0)
	{
		close(cmd->fd1[READ_END]);
		dup2(cmd->fd1[WRITE_END], STDOUT_FILENO);
		close(cmd->fd1[WRITE_END]);
		 if (!ft_arguments(cmd))
			execve(str, parmList, cmd->envorg);
	}
	else
		close(cmd->fd1[WRITE_END]);
	wait(&status);
}

void	ft_midpipe(char *str, t_cmd *cmd)
{
	int		status;
	int		pid;
	char	**parmList;

	pid = fork(); //crea fork
	parmList = copyparam(cmd); //copia parametros
	if (pid == 0) // SI PID0
	{
		close(cmd->fd2[READ_END]);
		dup2(cmd->fd1[READ_END], STDIN_FILENO);
		close(cmd->fd1[READ_END]);
		dup2(cmd->fd2[WRITE_END], STDOUT_FILENO);
		close(cmd->fd2[WRITE_END]);
		if (!ft_arguments(cmd)) //si no esta entre los comandos internos
			execve(str, parmList, cmd->envorg);
	}
	else /* padre */
	{
		close(cmd->fd1[READ_END]);
		close(cmd->fd2[WRITE_END]);
	}
	wait(&status); // espera que haga su magia
}

void	ft_endpipe(char *str, t_cmd *cmd)
{
	int		status;
	int		pid;
	char	**parmList;


	pid = fork();
	parmList = copyparam(cmd);
	if (pid == 0 && !cmd->nexpip->next)
	{
		dup2(cmd->fd1[READ_END], STDIN_FILENO);
		close(cmd->fd1[READ_END]);
		if (!ft_arguments(cmd))
			execve(str, parmList, cmd->envorg);
	}
	else
		close(cmd->fd1[READ_END]);
	wait(&status);
}

void	pipenator(t_cmd *cmd)
{
	pipe(cmd->fd1); //conecta FD1
	ft_startpipe(ft_strduptochar(cmd->in, 32), cmd); //copia parametros y empieza pipe
	while (cmd->nexpip->next) //mientras haya siguiente pipe, ejecuta el medio
	{
		pipe(cmd->fd2); //conecta FDX
		cmd->param = freelist(cmd->param); //borra listado de argumentos
		cmd->in = ft_strdup(cmd->nexpip->in); //copia ssiguiente comando
		ft_lst_add_arguments(&cmd->param, cmd->nexpip->in); //recoje argumentos de IN
		cmd->buff = ft_strduptochar(cmd->in, 32); //duplica el comando sin argumentos a buffer
		ft_path(cmd); // recoge path correcto
		ft_midpipe(ft_strduptochar(cmd->in, 32), cmd);
		cmd->nexpip = cmd->nexpip->next;
	}
	cmd->param = freelist(cmd->param); //borra listado de argumentos
	cmd->in = ft_strdup(cmd->nexpip->in);
	ft_lst_add_arguments(&cmd->param, cmd->nexpip->in); //recoje argumentos de IN
	cmd->buff = ft_strduptochar(cmd->in, 32); //duplica el comando sin argumentos a buffer
	ft_path(cmd); // recoge path correcto
	ft_endpipe(ft_strduptochar(cmd->in, 32), cmd); //ejecuta final del pipe
	cmd->param = freelist(cmd->param);
	cmd->nexpip = freelist(cmd->nexpip);
}
