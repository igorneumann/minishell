/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narroyo- <narroyo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 15:47:33 by narroyo-          #+#    #+#             */
/*   Updated: 2021/09/06 17:01:26 by narroyo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_counters(t_cmd *cmd)
{
	cmd->d_counter = 0;
	cmd->c_replace = 0;
	cmd->c2_replace = 0;
	cmd->counter = 0;
	cmd->c_d = -1;
}

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
	printf("\r\n%c -- %d\r\n", line[i], i);
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

int	look_for_open(char quote, char quote_2, char *str, int i)
{
	int	look;

	look = 0;
	printf("\r\n%c -- %d\r\n", str[i], i);
	while (str[i])
	{
		if (str[i] == quote_2)
			break ;
		if (str[i] == quote)
			look++;
		i--;
	}
	if (look % 2 != 0)
		return (1);
	return (0);
}

void	replace_global_var(t_cmd *cmd, char *var)
{
	//printf("\r\n(%d)\r\n", cmd->c_d);
//	printf("\r\n(%d && %d)\r\n(%d && %d) %d\r\n", look_for_closure('\"', '$', cmd->original, cmd->c_d),
//		look_for_open('\'', '\"', cmd->original, cmd->c_d), look_for_closure('\"', '$', cmd->original, cmd->c_d),
//		look_for_closure('\'', '$', cmd->original, cmd->c_d), cmd->c_d);
//	fflush(stdout);
	if ((cmd->quote_s == 0 && (cmd->quote_d == 0 || cmd->quote_d % 2 == 0))
		|| (look_for_closure('\"', '$', cmd->original, cmd->c_d) == 1
			&& look_for_open('\'', '\"', cmd->original, cmd->c_d) == 1)
		|| (look_for_closure('\"', '$', cmd->original, cmd->c_d) == 0
			&& look_for_open('\'', '\"', cmd->original, cmd->c_d) == 0))
		cmd->dollar_value[cmd->d_counter++] = search_value(var, cmd);
	else
		cmd->dollar_value[cmd->d_counter++] = ft_strjoin("$", var);
}
