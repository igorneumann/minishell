/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semicolon.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineumann <ineumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 18:24:59 by ineumann          #+#    #+#             */
/*   Updated: 2021/06/16 19:22:23 by ineumann         ###   ########.fr       */
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

/*int	delstrchar(char *str)
{
	while (str[1] != '\0')
	{
		str[0] = str[1];
		str++;
	}
	str[0] = '\0';
	return (1);
}*/

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
	int	pp;

	pp = 0;
	while (str[0] != '\0')
	{
		if ((str[0] == '|' || str[0] == '>'))
			pp++;
		str++;
	}
	return (pp);
}

/*int	prepstr(char *str, int pos, int qt)
{
	int	i;
	int	print;

	i = pos + 1;
	qt = i;
	print = 0;
	while (--i >= 0)
	{
		if ((str[i] == ' ' && print == 0) ||
			str[i] == '\"' || str[i] == '\'')
			delstrchar(&str[i]);
		else if (ft_isprint(str[i]))
			print++;
	}
	i = pos - 1;
	while (str[++i] != '\0')
		if (str[i] == '"')
			return (delstrchar(&str[i]));
	return (2);
}*/
