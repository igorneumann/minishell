/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narroyo- <narroyo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 21:20:06 by narroyo-          #+#    #+#             */
/*   Updated: 2021/09/16 13:56:31 by narroyo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	while_echo(t_cmd *cmd, int i, int j)
{
	while (cmd->in[i + j])
	{
		if (cmd->in[i + j] == '-')
			j++;
		while (cmd->in[i + j] == 'n')
			j++;
		if (cmd->in[i + j] != ' ')
			cmd->echo_nl = 2;
		while (cmd->in[i + j] == ' ' && cmd->in[i + j + 1] == '-'
			&& cmd->in[i + j + 2] == 'n')
			j += 3;
		while (cmd->in[i + j] == 'n')
			j++;
		while (cmd->in[i + j] == ' ')
			j++;
		if (ft_strnstr(cmd->in + i + j, "-n", 2) == NULL)
			break ;
	}
	return (j);
}

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

int	print_echo_nl(t_cmd *cmd, int i, int j)
{
	if (ft_strnstr(cmd->in + i, "-n", 2) != NULL)
	{
		cmd->echo_nl = 1;
		if (cmd->in[i + j] == '-' && cmd->in[i + j + 1] == 'n')
		{
			j += 2;
			while (cmd->in[i + j] == 'n')
				j++;
			if (!cmd->in[i + j])
				return (j + 3);
		}
		j = while_echo(cmd, i, j);
		if (cmd->echo_nl == 1)
		{
			if (cmd->in[i + j - 1] != ' ' && cmd->in[i + j] != '\0')
				while (cmd->in[i + j] != '-')
					j--;
			print_without_excess_of_spaces(cmd, i, j);
		}
	}
	return (j);
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
}
