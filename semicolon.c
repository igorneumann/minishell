/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semicolon.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narroyo- <narroyo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 18:24:59 by ineumann          #+#    #+#             */
/*   Updated: 2021/10/01 15:17:03 by narroyo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_semicolon(t_cmd *cmd)
{
	int		i;
	int		j;

	i = ft_strlen(cmd->in);
	while (i > 0)
	{
		j = 1;
		if ((cmd->original[i] == '&' && cmd->original[i + j] == '&')
			|| cmd->original[i] == ';')
		{
			if (countleft(cmd->original, i, '\'', '\"') % 2 == 0)
			{
				cmd->in[i] = '\0';
				if (cmd->in[i + j] == '&')
					cmd->in[i + j++] = '\0';
				while (cmd->original[i + j] == ' ')
					j++;
				ft_lst_add_front(&cmd->nexcom, ft_new(&cmd->in[i + j]));
			}
		}
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
	int		i;
	char	*st;

	i = 0;
	st = str;
	pp = 0;
	while (st[i] != '\0')
	{
		if (st[i] == '|'
			&& look_for_closure('\'', st[i], st, i) == 0
			&& look_for_closure('\"', st[i], st, i) == 0)
			pp++;
		i++;
	}
	return (pp);
}

int	findredir(char *str)
{
	int		rd;
	int		i;
	char	*st;

	i = 0;
	st = str;
	rd = 0;
	while (st[i] != '\0')
	{
		if ((st[i] == '<' || st[i] == '>')
			&& look_for_closure('\'', st[i], st, i) == 0
			&& look_for_closure('\"', st[i], st, i) == 0
			&& ((countleft(st, i, '\'', '\"') == 0)
				|| (countleft(st, i, '\'', '\"') % 2 != 0)))
			rd++;
		i++;
	}
	return (rd);
}
