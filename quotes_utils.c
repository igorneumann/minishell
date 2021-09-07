/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narroyo- <narroyo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 15:47:33 by narroyo-          #+#    #+#             */
/*   Updated: 2021/09/07 10:57:51 by narroyo-         ###   ########.fr       */
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
	if (!line)
		return (0);
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
					i++;
					while (line[i])
					{
						if (line[i] == quote)
							return (1);
						i++;
					}
					return (0);
				}
				i--;
			}
			if (!line[i])
				break ;
		}
		i++;
	}
	return (0);
}

int	look_for_open(char quote, char quote_2, char *str, int i)
{
	int	look;

	look = 0;
	while (str[i])
	{
		if (!str[i])
			break ;
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
	int	open_simple;
	int	close_simple;
	int	open_double;
	int	double_close;

	open_simple = look_for_open('\'', '\"', cmd->original, cmd->c_d);
	open_double = look_for_open('\"', '\'', cmd->original, cmd->c_d);
	close_simple = look_for_closure('\'', '$', cmd->original, cmd->c_d);
	double_close = look_for_closure('\"', '$', cmd->original, cmd->c_d);
	if (open_simple == 0 && close_simple == 0 && double_close == 1 && open_double == 1)
		cmd->dollar_value[cmd->d_counter++] = search_value(var, cmd);
	else if (close_simple == 1 && open_simple == 1 && double_close  == 0)
		cmd->dollar_value[cmd->d_counter++] = ft_strjoin("$", var);
	else if ((close_simple == 1 && open_simple == 1) || (close_simple == 0 && open_simple == 0))
		cmd->dollar_value[cmd->d_counter++] = search_value(var, cmd);
	else
		cmd->dollar_value[cmd->d_counter++] = ft_strjoin("$", var);
}
