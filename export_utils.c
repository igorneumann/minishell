/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineumann <ineumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 16:11:11 by narroyo-          #+#    #+#             */
/*   Updated: 2021/09/13 16:55:16 by ineumann         ###   ########.fr       */
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

void	envp_to_arr(t_cmd *cmd, int i)
{
	char	*aux;
	t_envp	*copy;
	t_envp	*tmp;

	copy = copy_env(cmd->envp);
	if (cmd->env != cmd->envorg)
		free_split(cmd->env);
	cmd->env = (char **)malloc(sizeof(char *)
			* (lst_size((t_envp *)&cmd->envp) + 1));
	while (copy->prev)
		copy = copy->prev;
	while (copy)
	{
		aux = ft_strjoin(copy->key, "=");
		cmd->env[i] = ft_strjoin(aux, copy->value);
		free(aux);
		tmp = copy;
		copy = copy->next;
		i++;
	}
	cmd->env[i] = NULL;
	while (tmp->prev)
		tmp = tmp->prev;
	free_env(tmp);
}
