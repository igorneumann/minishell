/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narroyo- <narroyo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 19:10:00 by narroyo-          #+#    #+#             */
/*   Updated: 2021/10/01 15:52:01 by narroyo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	addpath(t_cmd *cmd, char *tmp)
{
	char	*to_find;
	int		i;

	to_find = ft_strjoin(tmp, cmd->buff);
	free(tmp);
	tmp = NULL;
	i = open(to_find, O_RDONLY);
	if (i == -1)
	{
		free(to_find);
		to_find = NULL;
		return (1);
	}
	else
	{
		tmp = cmd->buff;
		free(tmp);
		free (cmd->in);
		cmd->in = to_find;
		to_find = NULL;
		cmd->buff = NULL;
		tmp = NULL;
	}
	close(i);
	return (0);
}

void	ft_path(t_cmd *cmd, int i)
{
	char	*tmp;

	i = 0;
	while (cmd->envp->prev)
		cmd->envp = cmd->envp->prev;
	while (cmd->envp->next && ft_strcmp(cmd->envp->key, "PATH") != 0)
		cmd->envp = cmd->envp->next;
	cmd->path = ft_split(cmd->envp->value, ':');
	cmd->buff = ft_strduptochar(cmd->in, 32, '\0');
	while (cmd->path[i])
	{
		tmp = ft_strjoin(cmd->path[i], "/");
		if (addpath(cmd, tmp) == 0)
			break ;
		else
			i++;
	}
	i = 0;
	while (cmd->path[i])
	{
		free(cmd->path[i]);
		i++;
	}
	free(cmd->path);
	cmd->path = NULL;
}

int	pipexector(char *file, char *const *argv, char *const *envp, t_cmd *cmd)
{
	char	*error;

	if (cmd->redpip == 1)
	{
		redirout(cmd, 0);
		cmd->redpip = -1;
	}
	execve(file, argv, envp);
	error = ft_strjoin(file, ": command not found\r\n");
	ft_putstr_fd(error, 2);
	free(error);
	exit(127);
	return (-1);
}

int	returnoutput(t_cmd *cmd)
{
	if (cmd->redpip == -1)
	{
		redirout(cmd, 1);
		return (1);
	}
	return (-1);
}
