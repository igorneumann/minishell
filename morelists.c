/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   morelists.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineumann <ineumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 18:36:03 by ineumann          #+#    #+#             */
/*   Updated: 2021/08/20 18:15:14 by ineumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data	*freelist(t_data *lst)
{
	t_data	*prev;

	if (lst != NULL)
	{
		lst = ft_lst_last(lst);
		while (lst->prev != NULL)
		{
			prev = lst->prev;
			free (lst->in);
			free (lst->copy);
			lst->in = NULL;
			lst->copy = NULL;
			lst->next = NULL;
			lst->prev = NULL;
			free (lst);
			lst = prev;
		}
		lst->next = NULL;
		free (lst->in);
		lst->in = NULL;
		free (lst->copy);
		lst->copy = NULL;
		free(lst);
	}
	return (NULL);
}
