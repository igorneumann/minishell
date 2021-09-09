/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narroyo- <narroyo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 16:11:11 by narroyo-          #+#    #+#             */
/*   Updated: 2021/09/09 22:45:37 by narroyo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_envp	*copy_env(t_envp *envp)
{
	t_envp	*copy_last;
	t_envp	*copy;

	copy_last = NULL;
	while (envp->prev)
		envp = envp->prev;
	while (envp)
	{
		copy = (t_envp *)malloc(sizeof(t_envp));
		if (envp->next && copy_last)
			copy_last->next = copy;
		copy->key = ft_strdup(envp->key);
		if (envp->value != NULL)
			copy->value = ft_strdup(envp->value);
		else
			copy->value = NULL;
		copy->prev = copy_last;
		copy_last = copy;
		envp = envp->next;
	}
	copy->prev->next = copy_last;
	copy->next = NULL;
	while (copy->prev)
		copy = copy->prev;
	return (copy);
}

void	envp_to_arr(t_cmd *cmd)
{
	int		i;
	char	*aux;
	t_envp	*copy;

	i = 0;
	copy = copy_env(cmd->envp);
//	if (cmd->env)
//	{
//		free_split(cmd->env);
//		cmd->env = NULL;
//	}
	cmd->env = (char **)malloc(sizeof(char *) * lst_size((t_envp *)&cmd->envp));
	while (copy->prev)
		copy = copy->prev;
	while (copy)
	{
		aux = ft_strjoin(copy->key, "=");
		cmd->env[i] = ft_strjoin(aux, copy->value);
		free(aux);
		copy = copy->next;
		i++;
	}
//	free_env(copy);
}
