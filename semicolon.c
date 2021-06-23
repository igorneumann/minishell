/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semicolon.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineumann <ineumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 18:24:59 by ineumann          #+#    #+#             */
/*   Updated: 2021/06/23 17:46:50 by ineumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_semicolon(t_cmd *cmd)
{
	int		i;
	int		j;

	i = ft_strlen(cmd->in);
	j = 1;
	while (i > 0)
	{
		if ((cmd->in[i] == '&' && cmd->in[i + j] == '&') || cmd->in[i] == ';')
		{
			if (countquotes(cmd->in, i) % 2 == 0)
			{
				cmd->in[i] = '\0';
				if (cmd->in[i + j] == '&')
					cmd->in[i + j++] = '\0';
				while (cmd->in[i + j] == ' ')
					j++;
				ft_lst_add_front(&cmd->nexcom, ft_new(&cmd->in[i + j]));
			}
		}
		j = 1;
		i--;
	}
}

int	countquotes(char *str, int pos)
{
	int	i;
	int	qt;

	qt = 0;
	i = pos + 1;
	while (--i >= 0)
		if ((str[i] == '\"' || str[i] == '\''))
			qt++;
	return (qt);
}

int	findpipes(char *str)
{
	int		pp;
	char	*st;

	st = str;
	pp = 0;
	while (st[0] != '\0')
	{
		if ((st[0] == '|' || st[0] == '>'))
			pp++;
		st++;
	}
	return (pp);
}
