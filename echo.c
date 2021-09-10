/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narroyo- <narroyo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 21:20:06 by narroyo-          #+#    #+#             */
/*   Updated: 2021/09/09 21:24:03 by narroyo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_echo_nl(t_cmd *cmd, int i, int j)
{
	if (ft_strnstr(cmd->in + i, "-n ", 3) != NULL)
	{
		cmd->echo_nl = 1;
		while (cmd->in[i + j])
		{
			if (cmd->in[i + j] == '-')
				j++;
			while (cmd->in[i + j] == 'n')
				j++;
			while (cmd->in[i + j] == ' ' && cmd->in[i + j + 1] == '-'
				&& cmd->in[i + j + 2] == 'n')
				j += 3;
			if (cmd->in[i + j] != ' ')
				cmd->echo_nl = 2;
			while (cmd->in[i + j] == ' ')
				j++;
			if (ft_strnstr(cmd->in + i + j, "-n", 2) == NULL)
				break ;
		}
		if (cmd->echo_nl == 1)
			ft_putstr(&cmd->in[i + j]);
	}
	return (j);
}

void	print_echo(t_cmd *cmd, int i, int j)
{
	j = print_echo_nl(cmd, i, j);
	if (cmd->echo_nl == 0 || cmd->echo_nl == 2)
	{
		if (cmd->echo_nl == 2)
			j -= 3;
		ft_putstr(&cmd->in[i + j]);
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
