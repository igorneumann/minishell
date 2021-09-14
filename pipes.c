/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineumann <ineumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 19:10:34 by ineumann          #+#    #+#             */
/*   Updated: 2021/09/14 19:56:48 by ineumann         ###   ########.fr       */
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
		if (cmd->original[i] == '|'
			&& countleft(cmd->original, i, '\'', '\"') % 2 == 0)
		{
			cmd->original[i] = '\0';
			while (cmd->original[i + j] == ' ')
				j++;
			ft_lst_add_front(&cmd->nexpip, ft_new(&cmd->original[i + j]));
			free (cmd->in);
			cmd->in = ft_strdup(cmd->original);
		}
		i--;
	}
	return (0);
}

int	ft_startpipe(char *str, t_cmd *cmd)
{
	int		status;
	int		pid;
	char	**parm_list;

	pipe(cmd->fd1);
	pid = fork();
	parm_list = copyparam(cmd);
	if (pid == 0)
	{
		close(cmd->fd1[READ_END]);
		dup2(cmd->fd1[WRITE_END], STDOUT_FILENO);
		close(cmd->fd1[WRITE_END]);
		if (!ft_arguments(cmd))
			return (pipexector(str, parm_list, cmd->env));
	}
	else
		close(cmd->fd1[WRITE_END]);
	free(parm_list);
	wait(&status);
	return (0);
}

int	ft_midpipe(char *str, t_cmd *cmd, int *fd_in, int *fd_out)
{
	int		status;
	int		pid;
	char	**parm_list;

	pid = fork();
	parm_list = copyparam(cmd);
	if (pid == 0)
	{
		close(fd_out[READ_END]);
		dup2(fd_in[READ_END], STDIN_FILENO);
		close(fd_in[READ_END]);
		dup2(fd_out[WRITE_END], STDOUT_FILENO);
		close(fd_out[WRITE_END]);
		if (!ft_arguments(cmd))
			return (pipexector(str, parm_list, cmd->env));
	}
	else
	{
		close(fd_in[READ_END]);
		close(fd_out[WRITE_END]);
	}
	free(parm_list);
	wait(&status);
	return (0);
}

int	ft_endpipe(char *str, t_cmd *cmd, int i)
{
	int		status;
	int		pid;
	char	**parm_list;
	int		*fd;

	if (i % 2 == 0)
		fd = cmd->fd1;
	else
		fd = cmd->fd2;
	pid = fork();
	parm_list = copyparam(cmd);
	if (pid == 0 && !cmd->nexpip->next)
	{
		dup2(fd[READ_END], STDIN_FILENO);
		close(fd[READ_END]);
		redirout(cmd, 0);
		if (!ft_arguments(cmd))
			return (pipexector(str, parm_list, cmd->env));
	}
	else
		close(fd[READ_END]);
	free(parm_list);
	wait(&status);
	return (0);
}

int	middlepiper(char *str, t_cmd *cmd, int i)
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
	return (ft_midpipe(str, cmd, fd_in, fd_out));
}
