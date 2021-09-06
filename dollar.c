/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narroyo- <narroyo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 12:06:27 by narroyo-          #+#    #+#             */
/*   Updated: 2021/09/06 09:28:56 by narroyo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	replace(t_cmd *cmd, int old_len)
{
	int	i;

	while (cmd->tmp_in[cmd->c2_replace])
	{
		if (cmd->tmp_in[cmd->c2_replace] == '$')
		{
			cmd->c2_replace++;
			if (cmd->counter++ == cmd->d_counter
				&& cmd->dollar_value[cmd->d_counter])
			{
				i = 0;
				while (cmd->dollar_value[cmd->d_counter][i])
					cmd->in[cmd->c_replace++]
						= cmd->dollar_value[cmd->d_counter][i++];
				cmd->c2_replace += old_len;
				cmd->d_counter++;
			}
		}
		else if (cmd->tmp_in[cmd->c2_replace])
			cmd->in[cmd->c_replace++] = cmd->tmp_in[cmd->c2_replace++];
	}
	cmd->in[cmd->c_replace] = '\0';
}

void	replace_allocation(t_cmd *cmd)
{
	char	*aux;

	cmd->d_counter--;
	aux = ft_strdup(cmd->in);
	free(cmd->in);
	cmd->in = (char *)malloc(sizeof(char) * (ft_strlen(aux)
				+ (ft_strlen(cmd->dollar_value[cmd->d_read])
					- (cmd->old_len[cmd->d_read])) + 1));
	if (cmd->in == NULL)
		return ;
	ft_memset(cmd->in, ' ', ft_strlen(aux)
		+ (ft_strlen(cmd->dollar_value[cmd->d_read])
			- (cmd->old_len[cmd->d_read])));
	cmd->in[ft_strlen(aux) + (ft_strlen(cmd->dollar_value[cmd->d_read])
			- (cmd->old_len[cmd->d_read]))] = '\0';
	cmd->in = ft_strjoin(aux, cmd->in);
	replace(cmd, cmd->old_len[cmd->d_read]);
	free(aux);
	cmd->d_read++;
}

void	replace_global_var(t_cmd *cmd, char *var)
{
	///ESTO TIENE QUE SER SOBRE CMD->IN, NO SOBRE CMD->ORIGINAL; EL PROBLEMA ES
	///EL CONTADOR CONTADOR GLOBAL, HABRÍA QUE CALCULARLO EN CADA VUELTA
	if ((cmd->quote_s == 0 && (cmd->quote_d == 0 || cmd->quote_d % 2 == 0))
		|| (look_for_closure('\"', '$', cmd->original, cmd->c_d) == 1
			&& look_for_open('\'', '\"', cmd->original, cmd->c_d) == 1)
		|| (look_for_closure('\"', '$', cmd->original, cmd->c_d) == 0
			&& look_for_closure('\'', '$', cmd->original, cmd->c_d) == 0))
		cmd->dollar_value[cmd->d_counter++] = search_value(var, cmd);
	else
		cmd->dollar_value[cmd->d_counter++] = ft_strjoin("$", var);
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
	int	i;

	i = 0;
	cmd->old_len = malloc(sizeof(int) * count_char(cmd->original, '$'));
	while (cmd->tmp_in[++cmd->c_d])
	{
		if (cmd->tmp_in[cmd->c_d] == '$')
		{
			while (cmd->tmp_in[cmd->c_d] != '$' && (cmd->tmp_in[cmd->c_d] != '\0'
					|| cmd->tmp_in[cmd->c_d] != ' '))
			{
				if (cmd->tmp_in[cmd->c_d] == '\0')
					break ;
				cmd->c_d++;
			}
			cmd->c_d++;
			cmd->old_len[i] = cpy_global_var(cmd, 0, cmd->c_d);
			i++;
		}
	}
}
