/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narroyo- <narroyo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 01:31:41 by narroyo-          #+#    #+#             */
/*   Updated: 2021/03/05 09:39:40 by narroyo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*tmp;
	t_list	*begin;

	if (lst)
	{
		tmp = lst;
		begin = ft_lstnew(f(tmp->content));
		if (!begin)
			return (NULL);
		tmp = tmp->next;
		while (tmp)
		{
			new = ft_lstnew(f(tmp->content));
			if (!new)
			{
				ft_lstclear(&begin, del);
				return (NULL);
			}
			ft_lstadd_back(&begin, new);
			tmp = tmp->next;
		}
		return (begin);
	}
	return (NULL);
}
