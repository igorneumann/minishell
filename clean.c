/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineumann <ineumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 18:13:10 by narroyo-          #+#    #+#             */
/*   Updated: 2021/09/23 19:48:49 by ineumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cleanfds(t_cmd *cmd, int i, int red)
{
	if (red)
	{
		if ((i == 1 || i == 3) && cmd->in_fd > 0)
			close(cmd->in_fd);
		if ((i == 2 || i == 3) && cmd->out_fd > 0)
			close(cmd->out_fd);
	}
	return (1);
}

void	cleanspcback(char *str, int k)
{
	int	i;

	i = 1;
	while (str[k - i] == 32)
	{
		str[k - i] = '\0';
		i++;
	}
}

int	check_fds(t_cmd *cmd)
{
	if (cmd->out_fd != -2 && open(cmd->outp, O_RDONLY) == -1)
	{
		if (cmd->outp[0] == '\0')
			ft_putstr_fd("syntax error near unexpected token `newline'\r\n", 2);
		else if (open(cmd->outp, O_RDONLY) == -1)
		{
			ft_putstr(cmd->outp);
			ft_putstr_fd(": Permission denied\r\n", 2);
		}
		if (cmd->inpt[0] == '\0' && cmd->outp[0] == '\r')
			return (2);
		close(cmd->in_fd);
		return (1);
	}
	else if (cmd->in_fd != -2 && open(cmd->inpt, O_RDONLY) == -1)
	{
		ft_putstr(cmd->inpt);
		if (cmd->inpt[0] != '\0')
			ft_putstr_fd(": No such file or directory\r\n", 2);
		else if (cmd->inpt[0] == '\r' && cmd->outp[0] == '\0')
			return (2);
		close(cmd->out_fd);
		return (1);
	}
	return (0);
}
