/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   morelists.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineumann <ineumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 18:36:03 by ineumann          #+#    #+#             */
/*   Updated: 2021/06/18 19:13:15 by ineumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data	*freelist(t_data *lst)
{
	t_data	*last;
	t_data	*prev;

	last = ft_lst_last(lst);
	while (last->prev != NULL)
	{
		prev = last->prev;
		free (last->in);
		last->in = NULL;
		last->next = NULL;
		last->prev = NULL;
		free (last);
		last = prev;
	}
	last->next = NULL;
	last->prev = NULL;
	free (last->in);
	last->in = NULL;
	free(last);
	return (NULL);
}
