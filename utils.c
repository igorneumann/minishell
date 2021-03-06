/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narroyo- <narroyo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 10:47:23 by narroyo-          #+#    #+#             */
/*   Updated: 2021/09/19 19:18:33 by narroyo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_printlist(t_data *x)
{
	t_data	*y;

	y = ft_lst_first(x);
	while (y)
	{
		printf("%s %p\r\n", y->in, x);
		y = y->next;
	}
	while (x)
	{
		printf("%s %p\r\n", x->in, x);
		x = x->next;
	}
	ft_putstr("\x1B[33m");
}

void	swap(t_envp *a, t_envp *b)
{
	char	*key;
	char	*value;

	key = a->key;
	value = a->value;
	a->key = b->key;
	a->value = b->value;
	b->key = key;
	b->value = value;
}

void	ft_sort_env(t_envp *list, t_envp *elem, t_envp *next_elem, int swapped)
{
	int	i;

	if (list == NULL)
		return ;
	list = copy_env(list);
	while (swapped)
	{
		swapped = 0;
		elem = list;
		while (elem->next != next_elem)
		{
			i = 0;
			while (((t_envp *)elem)->key[i] == ((t_envp *)elem->next)->key[i])
				i++;
			if (((t_envp *)elem)->key[i] > ((t_envp *)elem->next)->key[i])
			{
				swap(elem, elem->next);
				swapped = 1;
			}
			elem = elem->next;
		}
		next_elem = elem;
	}
	ft_print_export(elem);
	free_env(elem);
}

void	ft_print_export(t_envp *x)
{
	while (x->prev)
		x = x->prev;
	while (x)
	{
		if (x->value == NULL)
			printf("declare -x %s\r\n", x->key);
		else
			printf("declare -x %s=\"%s\"\r\n", x->key, x->value);
		x = x->next;
	}
}

int	quit_spaces(char *str, int i)
{
	while (str[i] == ' ')
		i++;
	return (i);
}
