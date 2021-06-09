/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commandkeys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineumann <ineumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 17:26:29 by ineumann          #+#    #+#             */
/*   Updated: 2021/06/09 18:19:33 by ineumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	commandkeys(t_cmd *cmd)
{
	char	seq[4];

	seq[3] = '\0';
	if (read(STDIN_FILENO, &seq[0], 1) != 1)
		return ('\x1b');
	if (seq[0] && read(STDIN_FILENO, &seq[1], 1) != 1)
		return ('\x1b');
	if ((seq[1] >= '0' && seq[1] <= '9') && read(STDIN_FILENO, &seq[2], 1) != 1)
		return ('\x1b');
	if (seq[2] == '~' && seq[1] == '3')
		ft_delete(cmd);
	if (seq[1] >= 'A' && seq[1] <= 'D')
		return (ft_arrows(cmd, seq));
	if (seq[2] == '~' || (seq[1] >= 'E' && seq[1] <= 'Z'))
		return (ft_homeend(cmd, seq));
	else
		ft_putstr(seq);
	return (0);
}

int	ft_arrows(t_cmd *cmd, char *seq)
{
	if (seq[1] == 'D')
	{
		if (cmd->i > 0)
		{
			ft_putstr("\033[D");
			cmd->i--;
		}
		return (1);
	}
	else if (seq[1] == 'C')
	{
		if (cmd->in[cmd->i] != '\0')
		{
			ft_putstr("\033[C");
			cmd->i++;
		}
		return (1);
	}
	else if (seq[1] == 'A' || seq[1] == 'B')
		return (ft_history(cmd, seq));
	return (0);
}

int	ft_homeend(t_cmd *cmd, char *seq)
{
	if (seq[1] == 'H' && cmd->i > 0)
	{
		while (--cmd->i >= 0)
			ft_putstr("\033[D");
		cmd->i = 0;
		return (1);
	}
	else if (seq[1] == 'F' && cmd->in[cmd->i] != '\0')
	{
		while (cmd->in[cmd->i] != '\0')
		{
			ft_putstr("\033[C");
			cmd->i++;
		}
		return (1);
	}
	return (0);
}

int	ft_delete(t_cmd *cmd)
{
	if (cmd->in[cmd->i + 1] != '\0')
	{
		ft_putstr("\033[C");
		cmd->i++;
		ft_backspace(cmd);
	}
	else
	{
		ft_putstr(" \033[J\033[D");
		cmd->in[cmd->i] = '\0';
	}
	return (1);
}
