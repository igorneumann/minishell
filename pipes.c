/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineumann <ineumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 19:10:34 by ineumann          #+#    #+#             */
/*   Updated: 2021/07/01 20:24:58 by ineumann         ###   ########.fr       */
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

void	ft_midpipe(t_cmd *cmd, char **parmList)
{
	int		status;
	int		pid;

	pipe(cmd->fd2);
	ft_putstr("YAY, MIDPIPE!\r\n");
	pid = fork();
	if (pid == 0 && !cmd->nexpip->next)
	{
		cmd->buff = ft_strduptochar(cmd->nexpip->in, 32);
		ft_path(cmd);
		close(cmd->fd2[READ_END]);
		dup2(cmd->fd1[READ_END], STDIN_FILENO);
		close(cmd->fd1[READ_END]);
		dup2(cmd->fd2[WRITE_END], STDOUT_FILENO);
		close(cmd->fd2[WRITE_END]);
		if (!ft_arguments(cmd))
		{
			execve(cmd->in, parmList, cmd->envorg);
		}
	}
	else
	{
		close(cmd->fd1[READ_END]);
		close(cmd->fd2[WRITE_END]);
	}
	wait(&status);
}

void	ft_startpipe(t_cmd *cmd, char **parmList)
{
	int		status;
	int		pid;

	pid = fork(); //crea fork
	if (pid == 0) // si PID0
	{
		if (cmd->param->prev)
			printf("cmd START is %s\r\nparmList 0 is %s\r\nparmList 1 is %s\r\ncmd->envorg 0 is %s\r\n", cmd->in, parmList[0], parmList[1], cmd->envorg[0]);
		close(cmd->fd1[READ_END]);
		dup2(cmd->fd1[WRITE_END], STDOUT_FILENO);
		close(cmd->fd1[WRITE_END]);
		if (!ft_arguments(cmd)) //si no esta entre los comandos internos
			execve(cmd->in, parmList, cmd->envorg);
	}
	else
	{
		close(cmd->fd1[READ_END]);
		close(cmd->fd1[WRITE_END]);
	}
	wait(&status); // espera que haga su magia
}

void	ft_endpipe(t_cmd *cmd, char **parmList)
{
	int		status;
	int		pid;

	pid = fork(); //crea fork
	if (pid == 0 && !cmd->nexpip->next) // SI PID0 y no hay siguiente comando
	{
		if (cmd->param->prev)
				printf("cmd END in is %s\r\nparmList 0 is %s\r\nparmList 1 is %s\r\ncmd->envorg 0 is %s\r\n", cmd->in, parmList[0], parmList[1], cmd->envorg[0]);
		dup2(cmd->fd1[READ_END], STDIN_FILENO);
		close(cmd->fd1[READ_END]);
		if (!ft_arguments(cmd)) //si no esta entre los comandos internos
			execve(cmd->in, parmList, cmd->envorg);
	}
	else
		close(cmd->fd1[READ_END]);
	wait(&status); // espera que haga su magia
}

void	pipenator(t_cmd *cmd)
{
	pipe(cmd->fd1); //conecta FD1
	ft_startpipe(cmd, copyparam(cmd));
/*	while (cmd->nexpip->next) //mientras haya siguiente pipe, ejecuta eel medio
	{
		cmd->param = freelist(cmd->param);
		ft_lst_add_arguments(&cmd->param, cmd->nexcom->in);
		ft_midpipe(cmd, copyparam(cmd));
		cmd->nexpip = cmd->nexpip->next;
	}*/
	cmd->param = freelist(cmd->param); //borra listado de argumentos
	if (cmd->nexpip->in) //si hay siguiente comando
		cmd->in = ft_strdup(cmd->nexpip->in); //pasa siguiente comando a IN
	ft_lst_add_arguments(&cmd->param, cmd->nexpip->in); //recoje argumentos de IN
	cmd->buff = ft_strduptochar(cmd->in, 32); //duplica el comando sin argumentos a buffer
	ft_path(cmd); // recoge path correcto
	ft_endpipe(cmd, copyparam(cmd)); //ejecuta final del pipe
	cmd->param = freelist(cmd->param);
	cmd->nexpip = freelist(cmd->nexpip);
}
