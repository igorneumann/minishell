/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narroyo- <narroyo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 12:06:27 by narroyo-          #+#    #+#             */
/*   Updated: 2021/09/06 18:06:19 by narroyo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	replace(t_cmd *cmd)
{
	int	i;

	cmd->d_counter = 0;
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
				cmd->c2_replace += cmd->old_len[cmd->d_counter];
				cmd->d_counter++;
			}
		}
		else if (cmd->tmp_in[cmd->c2_replace])
			cmd->in[cmd->c_replace++] = cmd->tmp_in[cmd->c2_replace++];
	}
	cmd->in[cmd->c_replace] = '\0';
}

int	new_lenght_amount(t_cmd *cmd)
{
	int	i;
	int	j;
	int	len;

	i = -1;
	j = 0;
	len = 0;
	while (++i < cmd->d_counter)
		len += ft_strlen(cmd->dollar_value[i]) - cmd->old_len[i];
	return (len);
}

void	replace_allocation(t_cmd *cmd)
{
	char	*aux;

	aux = ft_strdup(cmd->in);
	free(cmd->in);
	cmd->in = (char *)malloc(sizeof(char) * (ft_strlen(aux)
				+ new_lenght_amount(cmd) + 1));
	free(aux);
	if (cmd->in == NULL)
		return ;
	replace(cmd);
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
			while (cmd->tmp_in[cmd->c_d] != '$'
				&& (cmd->tmp_in[cmd->c_d] != '\0'
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
