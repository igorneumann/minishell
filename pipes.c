/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineumann <ineumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 19:10:34 by ineumann          #+#    #+#             */
/*   Updated: 2021/07/01 17:33:54 by ineumann         ###   ########.fr       */
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

/*void	printpip(t_cmd *cmd) //YA NO LO NECESITO
{
	int	i;

	i = 0;
	if (cmd->nexpip != NULL)
	{
		while (cmd->nexpip->next != NULL)
		{
			i++;
			ft_putstr("Pipe ");
			ft_putstr(ft_itoa(i));
			ft_putstr(cmd->nexpip->in);
			ft_putstr("\r\n");
			cmd->nexpip = cmd->nexpip->next;
		}
		ft_putstr("Pipe ");
		ft_putstr(ft_itoa(++i));
		ft_putstr(cmd->nexpip->in);
		ft_putstr("\r\n");
	}
	if (cmd->outp != NULL)
	{
		ft_putstr("Output is ");
		ft_putstr(cmd->outp);
		ft_putstr("\r\n");
	}
}*/

void	ft_midpipe(t_cmd *cmd)
{
	int		status;
	char	**parmList;
	int		pid;

	pipe(cmd->fd2);
	parmList = copyparam(cmd);
	pid = fork();
	if (pid == 0 && !cmd->nexpip->next)
	{
		ft_putstr("YAY, MIDPIPE!\r\n");
		cmd->buff = ft_strduptochar(cmd->nexpip->in, 32);
		ft_path(cmd);
		close(cmd->fd2[READ_END]);
		dup2(cmd->fd1[READ_END], STDIN_FILENO);
		close(cmd->fd1[READ_END]);
		dup2(cmd->fd2[WRITE_END], STDOUT_FILENO);
		close(cmd->fd2[WRITE_END]);
		if (!ft_arguments(cmd))
			execve(cmd->in, parmList, cmd->envorg);
	}
	else
	{
		close(cmd->fd1[READ_END]);
		close(cmd->fd2[WRITE_END]);
	}
	wait(&status);
}

void	ft_startpipe(t_cmd *cmd)
{
	int		status;
	char	**parmList;
	int		pid;

	pipe(cmd->fd1);
	parmList = NULL;
	pid = fork();
	parmList = copyparam(cmd);
	if (pid == 0)
	{
		ft_putstr("YAY, STARTPIPE!\r\n");
		close(cmd->fd1[READ_END]);
		dup2(cmd->fd1[WRITE_END], STDOUT_FILENO);
		close(cmd->fd1[WRITE_END]);
		if (!ft_arguments(cmd))
			execve(cmd->in, parmList, cmd->envorg);
	}
	else
	{
		close(cmd->fd1[READ_END]);
		close(cmd->fd1[WRITE_END]);
	}
	wait(&status);
}

void	ft_endpipe(t_cmd *cmd)
{
	int		status;
	char	**parmList;
	int		pid;

	pid = fork();
	parmList = copyparam(cmd);
	if (pid == 0 && !cmd->nexpip->next)
	{
		ft_putstr("YAY, ENDPIPE!\r\n");
		cmd->buff = ft_strduptochar(cmd->nexpip->in, 32);
		ft_path(cmd);
		dup2(cmd->fd1[READ_END], STDIN_FILENO);
		close(cmd->fd1[READ_END]);
		if (!ft_arguments(cmd))
			execve(cmd->in, parmList, cmd->envorg);
	}
	else
		close(cmd->fd1[READ_END]);
	wait(&status);
}

void	pipenator(t_cmd *cmd)
{
	ft_startpipe(cmd);
/*	while (cmd->nexpip->next)
	{
		cmd->param = freelist(cmd->param);
		ft_lst_add_arguments(&cmd->param, cmd->nexcom->in);
		ft_midpipe(cmd);
		cmd->nexpip = cmd->nexpip->next;
	}*/
	cmd->param = freelist(cmd->param);
//	if (cmd->nexpip->in)
//		ft_lst_add_arguments(&cmd->param, cmd->nexpip->in);
	ft_endpipe(cmd);
	cmd->nexpip = freelist(cmd->nexpip);
}
