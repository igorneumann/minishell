/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineumann <ineumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 10:47:23 by narroyo-          #+#    #+#             */
/*   Updated: 2021/06/02 19:45:15 by ineumann         ###   ########.fr       */
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

void	ft_printlist(t_data *x, char *buff)
{
	t_data *y;

	y = ft_lst_first(x);
	while (y && y != x)
	{
		printf("%s %p\r\n", y->in, x);
		y = y->next;
	}
	ft_putstr("\x1B[33m");
	while (x)
	{
		printf("%s %p\r\n", x->in, x);
		x = x->next;
	}
	printf ("\x1B[34mBuffer is %s\r\n", buff);
}

void	ft_print_env(t_envp *x)
{
	while (x->prev)
		x = x->prev;
	while (x)
	{
		printf("%s=%s\r\n", x->key, x->value);
		x = x->next;
	}
}

void	ft_sort_env(t_cmd *cmd)
{
	ft_print_env(cmd->envp);
}
