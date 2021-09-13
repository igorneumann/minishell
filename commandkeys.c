/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commandkeys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineumann <ineumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 17:26:29 by ineumann          #+#    #+#             */
/*   Updated: 2021/09/10 20:52:54 by ineumann         ###   ########.fr       */
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
		return (ft_jumpword(cmd, seq[0]));
	if ((seq[1] >= '0' && seq[1] <= '9') && read(STDIN_FILENO, &seq[2], 1) != 1)
		return ('\x1b');
	if (seq[2] == '~' && seq[1] == '3')
		ft_delete(cmd);
	if (seq[1] >= 'A' && seq[1] <= 'D')
		return (ft_arrows(cmd, seq));
	if (seq[2] == '~' || (seq[1] >= 'E' && seq[1] <= 'Z'))
		return (ft_homeend(cmd, seq));
	if (seq[2] == '~' && (seq[1] == '1' || seq[1] == '5'))
		ft_delete(cmd);
	if (seq[2] == ';' && seq[1] == '1')
		ft_altarrow(cmd);
	return (0);
}

int	ft_arrows(t_cmd *cmd, char *seq)
{
	int	j;

	j = strlen(cmd->in);
	if (seq[1] == 'D' && cmd->i > 0)
	{
		ft_putstr("\033[D");
		cmd->i--;
		return (1);
	}
	else if (seq[1] == 'C' && cmd->in[cmd->i] != '\0')
	{
		ft_putstr("\033[C");
		cmd->i++;
		return (1);
	}
	else if (seq[1] == 'A' || seq[1] == 'B')
	{
		while (cmd->in[cmd->i] != '\0')
		{
			ft_putstr("\033[C");
			cmd->i++;
		}
		return (ft_history(cmd, seq));
	}
	return (0);
}

int	ft_jumpword(t_cmd *cmd, char seq)
{
	if (seq == 'b' && cmd->i > 0)
	{
		while (--cmd->i > 0 && cmd->in[cmd->i] != ' ')
			ft_putstr("\033[D");
		ft_putstr("\033[D");
		return (1);
	}
	else if (seq == 'f' && cmd->in[cmd->i] != '\0')
	{
		cmd->i++;
		while (cmd->in[cmd->i] != '\0' && cmd->in[cmd->i] != ' ')
		{
			ft_putstr("\033[C");
			cmd->i++;
		}
		ft_putstr("\033[C");
		return (1);
	}
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
	if (cmd->in[cmd->i] != '\0')
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
	}
	return (1);
}
