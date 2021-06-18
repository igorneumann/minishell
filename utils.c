/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineumann <ineumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 10:47:23 by narroyo-          #+#    #+#             */
/*   Updated: 2021/06/17 18:09:41 by ineumann         ###   ########.fr       */
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
	t_envp	*lst;
	t_envp	*tmp;
	char	*key;
	char	*value;

	i = 0;
	lst = copy_env(cmd->envp);
	while (lst->prev)
		lst = lst->prev;
	while (i < lst_size(lst) - 1)
	{
		j = 0;
		tmp = lst;
		while (j < lst_size(lst) - i - 1)
		{
			if (lst->key[0] > lst->next->key[0])
			{
				key = lst->key;
				value = lst->value;
				lst->key = lst->next->key;
				lst->value = lst->next->value;
				lst->next->key = key;
				lst->next->value = value;
			}
			lst = lst->next;
			j++;
		}
		lst = tmp->next;
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
