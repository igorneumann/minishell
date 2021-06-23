/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narroyo- <narroyo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 19:10:00 by narroyo-          #+#    #+#             */
/*   Updated: 2021/06/23 16:39:43 by narroyo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_path(t_cmd *cmd)
{
	int		i;
	char	*to_find;
	char	*tmp;
	char	**args;
	pid_t	pid;

	i = 0;
	pid = fork();
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &cmd->raw->orig);
	args = ft_split(cmd->other_cmd, ' ');
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
		to_find = ft_strjoin(tmp, args[0]);
		free(tmp);
		if (open(to_find, O_RDONLY) == -1)
		{
			free(to_find);
			i++;
		}
		else if (pid == 0)
		{
			tmp = args[0];
			args[0] = to_find;
			free(tmp);
			execve(to_find, args, cmd->env);
			exit(0);
		}
	}
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &cmd->raw->raw);
}
