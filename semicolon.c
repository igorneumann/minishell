/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semicolon.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineumann <ineumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 18:24:59 by ineumann          #+#    #+#             */
/*   Updated: 2021/07/06 17:22:04 by ineumann         ###   ########.fr       */
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
			if (countleft(cmd->in, i, '\'', '\"') % 2 == 0)
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

int	countleft(char *str, int pos, char c, char d)
{
	int	i;
	int	qt;

	qt = 0;
	i = pos + 1;
	while (--i >= 0)
		if ((str[i] == c || str[i] == d))
			qt++;
	return (qt);
}

int	countright(char *str, int pos, char c, char d)
{
	int	i;
	int	qt;

	qt = 0;
	i = pos;
	while (str[i])
	{
		if ((str[i] == c || str[i] == d))
			qt++;
		i++;
	}
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
		if (st[0] == '|')
			pp++;
		st++;
	}
	return (pp);
}

int	findredir(char *str)
{
	int		rd;
	char	*st;

	st = str;
	rd = 0;
	while (st[0] != '\0')
	{
		if ((st[0] == '<' || st[0] == '>'))
			rd++;
		st++;
	}
	return (rd);
}
