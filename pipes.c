/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineumann <ineumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 19:10:34 by ineumann          #+#    #+#             */
/*   Updated: 2021/07/06 17:27:45 by ineumann         ###   ########.fr       */
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
		i--;
	}
	return (0);
}

void	ft_startpipe(char *str, t_cmd *cmd)
{
	int		status;
	int		pid;
	char	**parmList;

	pipe(cmd->fd1);
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

void	ft_midpipe(char *str, t_cmd *cmd, int *fd_in, int *fd_out)
{
	int		status;
	int		pid;
	char	**parmList;

	pid = fork();
	parmList = copyparam(cmd);
	if (pid == 0)
	{
		close(fd_out[READ_END]);
		dup2(fd_in[READ_END], STDIN_FILENO);
		close(fd_in[READ_END]);
		dup2(fd_out[WRITE_END], STDOUT_FILENO);
		close(fd_out[WRITE_END]);
		if (!ft_arguments(cmd))
			execve(str, parmList, cmd->envorg);
	}
	else
	{
		close(fd_in[READ_END]);
		close(fd_out[WRITE_END]);
	}
	wait(&status);
}

void	ft_endpipe(char *str, t_cmd *cmd, int i)
{
	int		status;
	int		pid;
	char	**parmList;
	int		*fd;

	if (i % 2 == 0)
		fd = cmd->fd1;
	else
		fd = cmd->fd2;
	pid = fork();
	parmList = copyparam(cmd);
	if (pid == 0 && !cmd->nexpip->next)
	{
		dup2(fd[READ_END], STDIN_FILENO);
		close(fd[READ_END]);
		if (!ft_arguments(cmd))
			execve(str, parmList, cmd->envorg);
	}
	else
		close(fd[READ_END]);
	wait(&status);
}

void	middlepiper(char *str, t_cmd *cmd, int i)
{
	int	*fd_in;
	int	*fd_out;

	if (i % 2 == 1)
	{
		fd_in = cmd->fd1;
		fd_out = cmd->fd2;
	}
	else
	{
		fd_in = cmd->fd2;
		fd_out = cmd->fd1;
	}
	pipe(fd_out);
	ft_midpipe(str, cmd, fd_in, fd_out);
}
