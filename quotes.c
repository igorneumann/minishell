/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narroyo- <narroyo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/22 19:05:47 by narroyo-          #+#    #+#             */
/*   Updated: 2021/08/12 19:34:13 by narroyo-         ###   ########.fr       */
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

int	check_quotes_error(t_cmd *cmd, int i)
{
	int	ok;

//	ok = 0;
	if (cmd->in[i] == '\'')
	{
		if (cmd->quote_s)
		{
			cmd->quote_s = 0;
			cmd->quote_d = 0;
		}
		else
			cmd->quote_s++;
		return (0);
	}
	if (cmd->in[i] == '\"')
	{
		if (cmd->quote_d)
		{
			cmd->quote_s = 0;
			cmd->quote_d = 0;
		}
		else
			cmd->quote_d++;
		return (0);
	}
	if (cmd->in[i] == '\0' && (cmd->quote_s != 0 || cmd->quote_d != 0 ))
		return (-1);
	ok = check_quotes_error(cmd, ++i);
	if (ok != -1)
		ok = check_quotes_error(cmd, ++i);
	return (ok);
}

int	check_replacement(t_cmd *cmd)
{
	int	k;
	int	i;

	k = 0;
	i = 0;
	if (check_quotes_error(cmd, 0) == -1)
	{
		printf("%s : command not found\r\n", cmd->in);
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
		if (cmd->tmp_in[i] == '$')
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
	//	else if (quotes(cmd) == 0 && cmd->tmp_in[i] == '$')
	//		k = dollar(cmd, k);
		i++;
	}
	if (k != 0)
		cmd->in = ft_strdup(cmd->tmp_in);
	free(cmd->tmp_in);
	return (1);
}
