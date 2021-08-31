/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narroyo- <narroyo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 15:47:33 by narroyo-          #+#    #+#             */
/*   Updated: 2021/08/31 17:31:12 by narroyo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_char(char *line, char character)
{
	int	i;

	i = 0;
	while (*line)
	{
		if (*line == character)
			i++;
		line++;
	}
	return (i);
}

int	look_for_closure(char quote, char searching, char *line, int i)
{
	if (!ft_strchr(line, quote))
		return (0);
	while (line[i])
	{
		if (line[i] == searching)
		{
			while (line[i])
			{
				if (line[i] == quote)
				{
					while (line[i])
					{
						if (line[i] == quote)
							return (1);
						i++;
					}
				}
				i--;
			}
		}
		i++;
	}
	return (0);
}

int	look_for_open(char quote, char *str, int i)
{
	int	look;

	look = 0;
	while (str[i])
	{
		if (str[i] == quote)
			look++;
		i++;
	}
	if (look % 2 != 0)
		return (1);
	return (0);
}
