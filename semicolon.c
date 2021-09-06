/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semicolon.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineumann <ineumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 18:24:59 by ineumann          #+#    #+#             */
/*   Updated: 2021/09/06 17:37:27 by ineumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_semicolon(t_cmd *cmd)
{
	int		i;
	int		j;

	i = ft_strlen(cmd->original);
	while (i > 0)
	{
		j = 1;
		if ((cmd->original[i] == '&' && cmd->original[i + j] == '&')
			|| cmd->original[i] == ';')
		{
			if (countleft(cmd->original, i, '\'', '\"') % 2 == 0)
			{
				cmd->original[i] = '\0';
				if (cmd->original[i + j] == '&')
					cmd->original[i + j++] = '\0';
				while (cmd->original[i + j] == ' ')
					j++;
				ft_lst_add_front(&cmd->nexcom, ft_new(&cmd->original[i + j]));
				free (cmd->in);
				cmd->in = cmd->original;
				cmd->original = ft_strdup("\x0D");
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
