/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narroyo- <narroyo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/22 19:05:47 by narroyo-          #+#    #+#             */
/*   Updated: 2021/09/04 21:02:45 by narroyo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_pairs(t_cmd *cmd, int i)
{
	if (cmd->in[i] == '\'')
	{
		cmd->quote_s++;
		if ((cmd->doubl == -1 && look_for_closure('\"', '\'', cmd->in, i) == 1)
			|| cmd->simple == -1)
			cmd->simple = 0;
		else
			cmd->simple = -1;
	}
	if (cmd->in[i] == '\"')
	{
		cmd->quote_d++;
		if ((cmd->simple == -1 && look_for_closure('\'', '\"', cmd->in, i) == 1)
			|| cmd->doubl == -1)
			cmd->doubl = 0;
		else
			cmd->doubl = -1;
	}
}

int	check_quotes_error(t_cmd *cmd)
{
	int	i;

	i = 0;
	cmd->simple = 0;
	cmd->doubl = 0;
	while (cmd->in[i])
	{
		check_pairs(cmd, i);
		i++;
	}
	if (cmd->simple == -1 || cmd->doubl == -1)
		return (-1);
	cmd->quotes = cmd->quote_s + cmd->quote_d;
	return (0);
}

void	omit_quotes(t_cmd *cmd, char q1, char q2)
{
	if (cmd->tmp_in[cmd->c1] == q1
		&& look_for_open(q1, q2, cmd->tmp_in, cmd->c1) == 1)
		cmd->in[cmd->c2++] = cmd->tmp_in[cmd->c1];
	cmd->c1++;
	if (cmd->tmp_in[cmd->c1] != '\0'
		&& look_for_closure(q2, cmd->tmp_in[cmd->c1 + 1],
			cmd->tmp_in, cmd->c1 + 1) == 1)
	{
		while (cmd->tmp_in[cmd->c1] != q2)
			cmd->in[cmd->c2++] = cmd->tmp_in[cmd->c1++];
		if (look_for_open(q1, q2, cmd->tmp_in, cmd->c1) == 1)
			cmd->in[cmd->c2++] = cmd->tmp_in[cmd->c1];
		cmd->c1++;
	}
}

char	*replace_quotes(t_cmd *cmd)
{
	cmd->c1 = 0;
	cmd->c2 = 0;
	free(cmd->in);
	cmd->in = (char *)malloc(sizeof(char) * ft_strlen(cmd->tmp_in) + 1);
	while (cmd->tmp_in[cmd->c1] != '\0')
	{
		if (cmd->tmp_in[cmd->c1] == '\"')
			omit_quotes(cmd, '\'', '\"');
		if (cmd->tmp_in[cmd->c1] == '\'')
			omit_quotes(cmd, '\"', '\'');
		if (cmd->tmp_in[cmd->c1] != '\0')
			cmd->in[cmd->c2++] = cmd->tmp_in[cmd->c1++];
	}
	cmd->in[cmd->c2] = '\0';
	return (cmd->in);
}

int	check_replacement(t_cmd *cmd)
{
	init_counters(cmd);
	if (check_quotes_error(cmd) == -1)
		return (-1);
	if (ft_strchr(cmd->in, '$') != NULL)
	{
		cmd->dollar_value = (char **)malloc(sizeof(char *)
				* (count_char(cmd->original, '$') + 1));
		cmd->dollar_value[count_char(cmd->original, '$')] = NULL;
	}
	cmd->without_quotes = ft_strdup(replace_quotes(cmd));
	free(cmd->tmp_in);
	cmd->tmp_in = ft_strdup(cmd->without_quotes);
	while (cmd->tmp_in[++cmd->c_d])
	{
		if (cmd->tmp_in[cmd->c_d] == '$')
			dollar(cmd);
	}
	// HACER LO QUE PONE EN EL CUADERNO
	replace_allocation(cmd, ch);
	cmd->tmp_in = ft_strdup(cmd->without_quotes);
	free(cmd->tmp_in);
	free_split(cmd->dollar_value);
	cmd->dollar_value = NULL;
	cmd->tmp_in = NULL;
	return (1);
}
