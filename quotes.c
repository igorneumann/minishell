/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narroyo- <narroyo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/22 19:05:47 by narroyo-          #+#    #+#             */
/*   Updated: 2021/08/30 15:35:47 by narroyo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	check_quotes_error(t_cmd *cmd)
{
	int	i;
	int	simple;
	int	doubl;

	i = 0;
	simple = 0;
	doubl = 0;
	while (cmd->in[i])
	{
		if (cmd->in[i] == '\'')
		{
			cmd->quote_s++;
			if ((doubl == -1 && look_for_closure('\"', '\'', cmd->in, i) == 1)
				|| simple == -1)
				simple = 0;
			else
				simple = -1;
		}
		if (cmd->in[i] == '\"')
		{
			cmd->quote_d++;
			if ((simple == -1 && look_for_closure('\'', '\"', cmd->in, i) == 1)
				|| doubl == -1)
				doubl = 0;
			else
				doubl = -1;
		}
		i++;
	}
	if (simple == -1 || doubl == -1)
		return (-1);
	cmd->quotes = cmd->quote_s + cmd->quote_d;
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

void	replace_quotes(t_cmd *cmd)
{
	cmd->c1 = 0;
	cmd->c2 = 0;
	free(cmd->in);
	cmd->in = (char *)malloc(sizeof(char) * ft_strlen(cmd->tmp_in) + 1);
	while (cmd->tmp_in[cmd->c1] != '\0')
	{
		if (cmd->tmp_in[cmd->c1] == '\"')
		{
			if (look_for_open('\'', cmd->tmp_in, cmd->c1) == 1)
				cmd->in[cmd->c2++] = cmd->tmp_in[cmd->c1];
			cmd->c1++;
			if (cmd->tmp_in[cmd->c1] != '\0'
				&& look_for_closure('\"', cmd->tmp_in[cmd->c1 + 1],
					cmd->tmp_in, cmd->c1 + 1) == 1)
			{
				while (cmd->tmp_in[cmd->c1] != '\"')
					cmd->in[cmd->c2++] = cmd->tmp_in[cmd->c1++];
				if (look_for_open('\'', cmd->tmp_in, cmd->c1) == 1)
					cmd->in[cmd->c2++] = cmd->tmp_in[cmd->c1];
				cmd->c1++;
			}
		}
		if (cmd->tmp_in[cmd->c1] == '\'')
		{
			if (look_for_open('\"', cmd->tmp_in, cmd->c1) == 1)
				cmd->in[cmd->c2++] = cmd->tmp_in[cmd->c1];
			cmd->c1++;
			if (cmd->tmp_in[cmd->c1] != '\0'
				&& look_for_closure('\'', cmd->tmp_in[cmd->c1 + 1],
					cmd->tmp_in, cmd->c1 + 1) == 1)
			{
				while (cmd->tmp_in[cmd->c1] != '\'')
					cmd->in[cmd->c2++] = cmd->tmp_in[cmd->c1++];
				if (look_for_open('\"', cmd->tmp_in, cmd->c1) == 1)
					cmd->in[cmd->c2++] = cmd->tmp_in[cmd->c1];
				cmd->c1++;
			}
		}
		if (cmd->tmp_in[cmd->c1] != '\0')
			cmd->in[cmd->c2++] = cmd->tmp_in[cmd->c1++];
	}
	cmd->in[cmd->c2] = '\0';
}

int	check_replacement(t_cmd *cmd)
{
	int	k;
	int	i;

	k = 0;
	i = 0;
	cmd->original = ft_strdup(cmd->in);
	if (check_quotes_error(cmd) == -1)
		return (-1);
	if (ft_strchr(cmd->in, '$') != NULL)
		cmd->dollar_value = (char **)malloc(sizeof(char *)
				* count_char(cmd->tmp_in, '$') + 1);
	replace_quotes(cmd);
	free(cmd->tmp_in);
	cmd->tmp_in = ft_strdup(cmd->in);
	while (cmd->tmp_in[i])
	{
		if (cmd->tmp_in[i] == '$')
			k = dollar(cmd, k);
		i++;
	}
	free(cmd->tmp_in);
	return (1);
}
