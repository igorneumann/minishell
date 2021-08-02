/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narroyo- <narroyo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/22 19:05:47 by narroyo-          #+#    #+#             */
/*   Updated: 2021/08/02 12:40:00 by narroyo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	look_for_closure(char quote, char searching, char *line)
{
	int	i;

	i = 0;
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

int	quotes(t_cmd *cmd)
{
	int	i;

	i = 0;
	if (cmd->tmp_in[i] == '\'')
	{
		cmd->quote_s++;
		i++;
	}
	if (cmd->tmp_in[i] == '\"')
	{
		cmd->quote_d++;
		i++;
	}
	return (i);
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

void	check_replacement(t_cmd *cmd)
{
	int	k;
	int	i;

	k = 0;
	i = 0;
	if (ft_strchr(cmd->in, '$') != NULL)
	{
		cmd->tmp_in = ft_strdup(cmd->in);
		cmd->dollar_value = (char **)malloc(sizeof(char *)
			* count_char(cmd->tmp_in, '$'));
		free(cmd->in);
	}
	while (cmd->tmp_in[i])
	{
		if (quotes(cmd) != 0 && cmd->tmp_in[i] == '$')
		{
			if (look_for_closure('\"', '$', cmd->tmp_in) == 1)
			{
				if (look_for_closure('\'', '$', cmd->tmp_in) == 1)
					i++;
				else
					k = dollar(cmd, k);
			}
		}
		else if (quotes(cmd) == 0 && cmd->tmp_in[i] == '$')
			k = dollar(cmd, k);
		i++;
	}
	if (ft_strchr(cmd->in, '$') != NULL)
		cmd->in = ft_strdup(cmd->tmp_in);
	free(cmd->tmp_in);
}
