/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_nl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narroyo- <narroyo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 17:29:35 by narroyo-          #+#    #+#             */
/*   Updated: 2021/09/20 17:34:34 by narroyo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	while_echo(t_cmd *cmd, int i, int j)
{
	while (cmd->in[i + j])
	{
		if (cmd->in[i + j] == '-' && cmd->in[i + j + 1] == 'n')
			j += 2;
		while (cmd->in[i + j] == 'n')
			j++;
		if (cmd->in[i + j] != ' ')
			cmd->echo_nl = 2;
		while (cmd->in[i + j] == ' ')
			j++;
		if (ft_strnstr(cmd->in + i + j, "-n ", 3) == NULL)
			break ;
	}
	return (j);
}

int	echo_nl(t_cmd *cmd, int i, int j)
{
	if (cmd->echo_nl == 1)
	{
		if (cmd->in[i + j - 1] != ' ' && cmd->in[i + j] != '\0')
			while (cmd->in[i + j] != '-')
				j--;
		print_without_excess_of_spaces(cmd, i, j);
	}
	return (j);
}

int	print_echo_nl(t_cmd *cmd, int i, int j)
{
	if (ft_strnstr(cmd->in + i, "-n", 2) != NULL)
	{
		cmd->echo_nl = 1;
		if (cmd->in[i + j] == '-' && cmd->in[i + j + 1] == 'n')
		{
			j += 2;
			if (cmd->in[i + j] == '\0')
				return (j);
			if (cmd->in[i + j] != ' ')
			{
				cmd->echo_nl = 0;
				return (0);
			}
			while (cmd->in[i + j] == 'n')
				j++;
			if (!cmd->in[i + j])
				return (j + 3);
		}
		j = while_echo(cmd, i, j);
		j = echo_nl(cmd, i, j);
	}
	return (j);
}
