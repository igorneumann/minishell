/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narroyo- <narroyo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 17:17:03 by narroyo-          #+#    #+#             */
/*   Updated: 2021/06/02 10:20:36 by narroyo-         ###   ########.fr       */
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
	else
	{
		*in = ft_lst_first(*in);
		tmp = *in;
		*in = new;
		new->next = tmp;
		(tmp)->prev = new;
	}
}

void	ft_lst_remove_front(t_data *in)
{
	t_data	*tmp;
	
	tmp = in;
	in = in->next;
	free(tmp);
}

void	ft_lst_add_back(t_data **in, t_data *new)
{
	t_data	*last;

	if (!(*in))
	{
		*in = new;
		return ;
	}
	last = ft_lst_last(*in);
	new->prev = last;
	last->next = new;
}
