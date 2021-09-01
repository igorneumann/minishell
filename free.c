/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineumann <ineumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 16:12:33 by narroyo-          #+#    #+#             */
/*   Updated: 2021/09/01 19:59:53 by ineumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data	*free_list(t_data *lst)
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
			lst->next = NULL;
			lst->prev = NULL;
			free (lst);
			lst = prev;
		}
		lst->next = NULL;
		free (lst->in);
		free (lst->copy);
		free(lst);
	}
	return (NULL);
}

t_envp	*free_env(t_envp *lst)
{
	t_envp	*actual;

	if (lst != NULL)
	{
		while (lst->prev != NULL)
			lst = lst->prev;
		while (lst)
		{
			actual = lst;
			lst = lst->next;
			free(actual->key);
			free(actual->value);
			free(actual);
		}
	}
	return (NULL);
}

void	free_elem(t_envp *elem)
{
	free(elem->key);
	free(elem->value);
	free(elem);
}

void	free_split(char **split)
{
	int	i;

	if (!split || !*split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

t_data	*free_first(t_data *data)
{
	t_data	*temp;

	temp = data;
	if (temp->next != NULL)
		temp->next->prev = NULL;
	data = temp->next;
	free (temp->in);
	free (temp->copy);
	free(temp);
	return (data);
}
