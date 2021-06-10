/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narroyo- <narroyo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 10:47:23 by narroyo-          #+#    #+#             */
/*   Updated: 2021/06/10 20:35:09 by narroyo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	command_not_found(char *str, t_cmd *cmd)
{
	int	i;

	i = ft_strlen(str);
	if (ft_strnstr(cmd->in, str, ft_strlen(str)))
	{
		if (cmd->in[i] != ' ' && cmd->in[i] != '\0')
		{
			printf("%s : command not found\r\n", cmd->in);
			return (1);
		}
	}
	return (0);
}

void	ft_printlist(t_data *x, char *buff)
{
	t_data	*y;

	(void)buff;
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
		if (x->value == NULL)
			x = x->next;
		else
		{
			printf("%s=%s\r\n", x->key, x->value);
			x = x->next;
		}
	}
}

void	ft_sort_env(t_cmd *cmd)
{
	int		i;
	int		j;
	t_envp	*tmp;
	t_envp	*lst;

	i = 0;
	lst = cmd->envp;
	while (lst->prev)
		lst = lst->prev;
	while (i < lst_size(lst) - 1)
	{
		j = 0;
		while (j < lst_size(lst) - i - 1)
		{
			printf("%s\n", lst->key);
			printf("%d\n", j);
			if (lst->key[0] > lst->next->key[0])
			{
		/*		printf("%c\n", lst->key[0]);
				printf("%c\n", lst->next->key[0]);
				temp = lst;
				lst->next->prev = lst->prev;
				lst->next->next = temp;
				lst->next->next->prev = temp;
				temp->next = lst->next->next;
				temp->prev = lst->next;*/
	// ESTO ES UNA MIERDA COMO UNA CASA
			}
			j++;
				printf("%d\n", j);
			lst = lst->next;
		}
		lst = lst->next;
		printf("%d\n", i);
		i++;
	}
	ft_print_export(lst);
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
