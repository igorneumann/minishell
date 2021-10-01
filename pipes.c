/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narroyo- <narroyo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 19:10:34 by ineumann          #+#    #+#             */
/*   Updated: 2021/10/01 16:00:09 by narroyo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pipes(t_cmd *cmd)
{
	int		i;
	int		j;
	int		k;

	i = ft_strlen(cmd->original);
	while (i > 0)
	{
		j = 1;
		if (cmd->original[i] == '|'
			&& countleft(cmd->original, i, '\'', '\"') % 2 == 0)
		{
			k = 0;
			while (cmd->in[k] != '|'
				&& countleft(cmd->original, i, '\'', '\"') % 2 == 0)
				k++;
			cmd->in[k] = '\0';
			while (cmd->original[i + j] == ' ')
				j++;
			ft_lst_add_front(&cmd->nexpip, ft_new(&cmd->in[k + j]));
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
	redir(cmd, ft_strlen(cmd->in), 0, 1);
	if (pid == 0)
	{
		close(cmd->fd1[READ_END]);
		dup2(cmd->fd1[WRITE_END], STDOUT_FILENO);
		close(cmd->fd1[WRITE_END]);
		if (!ft_arguments(cmd))
			return (pipexector(str, parm_list, cmd->env, cmd));
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
			return (pipexector(str, parm_list, cmd->env, cmd));
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
		if (!ft_arguments(cmd))
			return (pipexector(str, parm_list, cmd->env, cmd));
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
