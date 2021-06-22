/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narroyo- <narroyo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 19:10:00 by narroyo-          #+#    #+#             */
/*   Updated: 2021/06/22 20:47:34 by narroyo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_path(t_cmd *cmd)
{
	int		i;
	char	*to_find;

	i = 0;
	while (cmd->envp->prev)
		cmd->envp = cmd->envp->prev;
	while (ft_strcmp(cmd->envp->key, "PATH") != 0)
		cmd->envp = cmd->envp->next;
	cmd->path = ft_split(cmd->envp->value, ':');
	while (cmd->path[i])
	{
		to_find = ft_strjoin(cmd->path[i], cmd->other_cmd);
		if (open(to_find, O_RDONLY) == -1)
		{
			free(to_find);
			i++;
		}
		else

	}
}
