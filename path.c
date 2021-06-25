/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineumann <ineumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 19:10:00 by narroyo-          #+#    #+#             */
/*   Updated: 2021/06/25 18:16:15 by ineumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	addpath(t_cmd *cmd, char *tmp)
{
	char	*to_find;

	to_find = ft_strjoin(tmp, cmd->other_cmd);
	free(tmp);
	tmp = NULL;
	if (open(to_find, O_RDONLY) == -1)
	{
		free(to_find);
		to_find = NULL;
		return (1);
	}
	else
	{
		tmp = cmd->other_cmd;
		free(tmp);
		free (cmd->in);
		cmd->in = to_find;
		to_find = NULL;
		cmd->other_cmd = NULL;
		tmp = NULL;
	}
	return (0);
}

void	ft_path(t_cmd *cmd)
{
	int		i;
	char	*tmp;

	i = 0;
	while (cmd->envp->prev)
		cmd->envp = cmd->envp->prev;
	while (ft_strcmp(cmd->envp->key, "PATH") != 0)
		cmd->envp = cmd->envp->next;
	cmd->path = ft_split(cmd->envp->value, ':');
	while (cmd->path[i])
	{
		tmp = ft_strjoin(cmd->path[i], "/");
		if (addpath(cmd, tmp) == 0)
			break ;
		else
			i++;
	}
}

/*void	ft_path(t_cmd *cmd) // OLD PATH
{
	int		i;
	char	*to_find;
	char	*tmp;
	char	**command;
	pid_t	pid;

	i = 0;
	pid = fork();
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &cmd->raw->orig);
	command = ft_split(cmd->other_cmd, ' ');
	if (pid == -1)
		perror("fork error");
	while (cmd->envp->prev)
		cmd->envp = cmd->envp->prev;
	while (ft_strcmp(cmd->envp->key, "PATH") != 0)
		cmd->envp = cmd->envp->next;
	cmd->path = ft_split(cmd->envp->value, ':');
	while (cmd->path[i])
	{
		tmp = ft_strjoin(cmd->path[i], "/");
		to_find = ft_strjoin(tmp, command[0]);
		free(tmp);
		if (open(to_find, O_RDONLY) == -1)
		{
			free(to_find);
			i++;
		}
		else if (pid == 0)
		{
			tmp = command[0];
			command[0] = to_find;
			free(tmp);
			execve(to_find, command, cmd->env);
			exit(0);
		}
	}
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &cmd->raw->raw);
}*/
