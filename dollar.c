/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narroyo- <narroyo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 12:06:27 by narroyo-          #+#    #+#             */
/*   Updated: 2021/09/01 20:49:41 by narroyo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	replace(t_cmd *cmd, int old_len, int counter)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	k = 0;
	while (cmd->tmp_in[k])
	{
		if (cmd->tmp_in[k] == '$')
		{
			k++;
			if (counter == cmd->d_counter)
			{
				j = 0;
				while (cmd->dollar_value[cmd->d_counter][j])
					cmd->in[i++] = cmd->dollar_value[cmd->d_counter][j++];
				k += old_len;
				cmd->d_counter++;
				counter++;
			}
		}
		else if (cmd->tmp_in[k])
			cmd->in[i++] = cmd->tmp_in[k++];
	}
	cmd->in[i] = '\0';
}

void	replace_allocation(t_cmd *cmd, int old_len)
{
	int	counter;

	counter = 0;
	cmd->d_counter--;
	free(cmd->in);
	cmd->in = (char *)malloc(sizeof(char) * (ft_strlen(cmd->tmp_in)
				+ (ft_strlen(cmd->dollar_value[cmd->d_counter]) - (old_len)))
			+ 1);
	if (cmd->in == NULL)
		return ;
	replace(cmd, old_len, counter);
}

void	replace_global_var(t_cmd *cmd, char *var)
{
	if ((cmd->quote_s == 0 && (cmd->quote_d == 0 || cmd->quote_d % 2 == 0))
		|| (look_for_closure('\"', '$', cmd->original, cmd->c_d) == 1
			&& look_for_open('\'', '\"', cmd->original, cmd->c_d) == 1))
		cmd->dollar_value[cmd->d_counter] = search_value(var, cmd);
	else
		cmd->dollar_value[cmd->d_counter] = ft_strjoin("$", var);
	cmd->d_counter++;
}

int	cpy_global_var(t_cmd *cmd, int ch, int i)
{
	char	*var;
	char	*question_mark;
	int		j;

	j = 0;
	while (cmd->tmp_in[cmd->c_d + ch] != '\''
		&& cmd->tmp_in[cmd->c_d + ch] != '\0'
		&& cmd->tmp_in[cmd->c_d + ch] != ' '
		&& cmd->tmp_in[cmd->c_d + ch] != '\"')
		ch++;
	var = (char *)malloc(sizeof(char) * ch + 1);
	while (cmd->tmp_in[i] && cmd->tmp_in[i] != ' '
		&& cmd->tmp_in[i] != '\'' && cmd->tmp_in[i] != '\"'
		&& i < i + ch)
		var[j++] = cmd->tmp_in[i++];
	var[j] = '\0';
	question_mark = search_value(var, cmd);
	if (question_mark == NULL)
		printf("%s : command not found\r\n", var);
	replace_global_var(cmd, var);
	if (question_mark)
		free(question_mark);
	free(var);
	return (ch);
}

void	dollar(t_cmd *cmd)
{
	int	ch;

	ch = 0;
	while (cmd->tmp_in[cmd->c_d] != '$' && (cmd->tmp_in[cmd->c_d] != '\0'
			|| cmd->tmp_in[cmd->c_d] != ' '))
	{
		if (cmd->tmp_in[cmd->c_d] == '\0')
			break ;
		cmd->c_d++;
	}
	cmd->c_d++;
	ch = cpy_global_var(cmd, ch, cmd->c_d);
	replace_allocation(cmd, ch);
}
