/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narroyo- <narroyo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 16:11:11 by narroyo-          #+#    #+#             */
/*   Updated: 2021/06/30 19:41:08 by narroyo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_envp	*copy_env(t_envp *envp)
{
	t_envp	*copy;

	while (envp->prev)
		envp = envp->prev;
	while (envp->next)
	{
		copy = (t_envp *)malloc(sizeof(t_envp));
		copy->prev = envp->prev;
		copy->key = ft_strdup(envp->key);
		if (envp->value != NULL)
			copy->value = ft_strdup(envp->value);
		else
			copy->value = NULL;
		copy->next = envp->next;
		envp = envp->next;
	}
	while (copy->prev)
		copy = copy->prev;
	return (copy);
}
