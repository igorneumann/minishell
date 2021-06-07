/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narroyo- <narroyo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 10:47:23 by narroyo-          #+#    #+#             */
/*   Updated: 2021/06/07 16:31:19 by narroyo-         ###   ########.fr       */
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
	t_data *y;

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
		printf("%s=%s\r\n", x->key, x->value);
		x = x->next;
	}
}

void	ft_sort_env(t_cmd *cmd)
{
	ft_print_env(cmd->envp);
}
