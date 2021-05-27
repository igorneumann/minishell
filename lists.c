/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narroyo- <narroyo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 17:17:03 by narroyo-          #+#    #+#             */
/*   Updated: 2021/05/27 10:18:52 by narroyo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data	*ft_new(char *in)
{
	t_data	*new;

	new = (t_data *)malloc(sizeof(t_data));
	if (!new)
		return (NULL);
	new->prev = NULL;
	new->in = in;
	new->next = NULL;
	return (new);
}

void	ft_lst_add_front(t_data **in, t_data *new)
{
	t_data	*first;

	if (!in)
	{
		*in = new;
		return ;
	}
	first = ft_lst_first(*in);
	new->next = first;
	first->prev = new;
}

void	ft_lst_add_back(t_data **in, t_data *new)
{
	t_data	*last;

	if (!in)
	{
		*in = new;
		return ;
	}
	last = ft_lst_last(*in);
	new->prev = last;
	last->next = new;
}

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
