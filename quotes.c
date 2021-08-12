/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narroyo- <narroyo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/22 19:05:47 by narroyo-          #+#    #+#             */
/*   Updated: 2021/08/12 20:04:11 by narroyo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	look_for_closure(char quote, char searching, char *line, int i)
{
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
			if (simple == -1)
			{
				simple = 0;
				doubl = 0;
			}
			else
				simple = -1;
		}
		if (cmd->in[i] == '\"')
		{
			if (doubl == -1)
			{
				doubl = 0;
				simple = 0;
			}
			else
				doubl = -1;
		}
		i++;
	}
	if (simple == -1 || doubl == -1)
		return (-1);
	return (0);
}

int	check_replacement(t_cmd *cmd)
{
	int	k;
	int	i;

	k = 0;
	i = 0;
	if (check_quotes_error(cmd) == -1)
	{
		printf("unexpected EOF while looking for matching \'\"\r\n");
		return (0);
	}
	if (ft_strchr(cmd->in, '$') != NULL)
	{
		cmd->tmp_in = ft_strdup(cmd->in);
		cmd->dollar_value = (char **)malloc(sizeof(char *)
			* count_char(cmd->tmp_in, '$'));
		free(cmd->in);
	}
	while (cmd->tmp_in[i])
	{
		if (cmd->tmp_in[i] == '$' && quotes(cmd) != 0)
		{
			if (look_for_closure('\'', '$', cmd->tmp_in, i) == 1)
			{
				if (look_for_closure('\"', '\'', cmd->tmp_in, i) == 1)
					k = dollar(cmd, k);
			}
		}
	//	if (quotes(cmd) != 0 && cmd->tmp_in[i] == '$')
	//	{
	//		if (look_for_closure('\"', '$', cmd->tmp_in, i) == 1)
	//		{
	//			if (look_for_closure('\'', '$', cmd->tmp_in, i) == 1)
	//				i++;
	//			else
	//				k = dollar(cmd, k);
	//		}
	//	}
		else if (quotes(cmd) == 0 && cmd->tmp_in[i] == '$')
			k = dollar(cmd, k);
		i++;
	}
	if (k != 0)
		cmd->in = ft_strdup(cmd->tmp_in);
	free(cmd->tmp_in);
	return (1);
}
