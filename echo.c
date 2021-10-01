/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narroyo- <narroyo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 21:20:06 by narroyo-          #+#    #+#             */
/*   Updated: 2021/10/01 14:49:06 by narroyo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_without_excess_of_spaces(t_cmd *cmd, int i, int j)
{
	while (cmd->in[i + j] != '\0')
	{
		if (cmd->in[i + j] == ' '
			&& look_for_closure('\'', cmd->in[i + j], cmd->in, i + j) == 0
			&& look_for_closure('\"', cmd->in[i + j], cmd->in, i + j) == 0)
		{
			ft_putchar_fd(cmd->in[i + j], 1);
			j++;
			while (cmd->in[i + j] == ' ')
				j++;
		}
		else
		{
			ft_putchar_fd(cmd->in[i + j], 1);
			j++;
		}
	}
}

void	print_echo(t_cmd *cmd, int i, int j)
{
	j = print_echo_nl(cmd, i, j);
	if (cmd->echo_nl != 1)
	{
		if (cmd->echo_nl == 2)
		{
			while (cmd->in[i + j] != '-')
				j--;
		}
		print_without_excess_of_spaces(cmd, i, j);
		if (cmd->echo_nl == 2)
			j = 0;
		if (j == 0)
			ft_putstr("\r\n");
	}
}

void	ft_echo(t_cmd *cmd)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	cmd->not_found = 1;
	if (command_not_found("echo", cmd))
		return ;
	if (cmd->check_replacement == -1)
	{
		ft_putstr_fd("unexpected EOF while looking for matching\'\"\r\n", 2);
		return ;
	}
	i += 4;
	while (cmd->in[i] == ' ')
		i++;
	cmd->echo_nl = 0;
	print_echo(cmd, i, j);
	cmd->output_status = 0;
}
