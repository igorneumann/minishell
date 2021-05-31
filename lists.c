/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineumann <ineumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 17:17:03 by narroyo-          #+#    #+#             */
/*   Updated: 2021/05/31 18:24:38 by ineumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data	*ft_new(char *in)
{
	t_data	*new;

	new = (t_data *)calloc(1, sizeof(t_data));
	if (!new)
		return (NULL);
	new->prev = NULL;
	new->in = ft_strdup(in);
	new->next = NULL;
	return (new);
}

void	ft_lst_add_front(t_data **in, t_data *new)
{
	t_data	*tmp;
	
	if (!(*in))
	{
		*in = new;
		return ;
	}
	tmp = *in;
	*in = new;
	new->next = tmp;
	(tmp)->prev = new;
}

void	ft_lst_add_back(t_data *in, t_data *new)
{
	t_data	*last;

	last = ft_lst_last(in);
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
