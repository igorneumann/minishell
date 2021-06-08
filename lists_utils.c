/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narroyo- <narroyo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 09:35:29 by narroyo-          #+#    #+#             */
/*   Updated: 2021/06/08 18:56:36 by narroyo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data	*ft_lst_last(t_data *elem)
{
	if (elem)
	{
		while (elem->next)
			elem = elem->next;
	}
	return (elem);
}

t_data	*ft_lst_first(t_data *elem)
{
	if (elem)
	{
		while (elem->prev)
			elem = elem->prev;
	}
	return (elem);
}

t_envp	*search_elem(t_envp *elem, char *wanted)
{
	if (elem)
	{
		while (elem->prev)
			elem = elem->prev;
		while (elem->next)
		{
			if (ft_strcmp(elem->key, wanted) != 0)
				elem = elem->next;
			else
				break ;
		}
	}
	return (elem);
}

t_envp	*change_value(t_envp *elem, char *new_value)
{
	if (elem)
	{
		free(elem->value);
		elem->value = ft_strdup(new_value);
	}
	return (elem);
}

t_envp	*remove_elem(t_envp *elem)
{
	if (elem->prev && elem->next && elem)
	{
		elem->prev->next = elem->next;
		elem->next->prev = elem->prev;
		elem = elem->prev;
	}
	if (!elem->prev && elem->next && elem)
	{
		elem->next->prev = NULL;
		elem = elem->next;
	}
	if (elem->prev && !elem->next && elem)
	{
		elem->prev->next = NULL;
		elem = elem->prev;
	}
	return (elem);
}
