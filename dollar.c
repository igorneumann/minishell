/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narroyo- <narroyo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 12:06:27 by narroyo-          #+#    #+#             */
/*   Updated: 2021/08/31 17:52:29 by narroyo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	replace(t_cmd *cmd, int position, int old_len, int counter)
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
			if (counter == position)
			{
				j = 0;
				while (cmd->dollar_value[position][j])
					cmd->in[i++] = cmd->dollar_value[position][j++];
				k += old_len;
				position++;
				counter++;
			}
		}
		else if (cmd->tmp_in[k])
			cmd->in[i++] = cmd->tmp_in[k++];
	}
	cmd->in[i] = '\0';
}

void	replace_allocation(t_cmd *cmd, int position, int old_len)
{
	int	counter;

	counter = 0;
	position--;
	free(cmd->in);
	cmd->in = (char *)malloc(sizeof(char) * (ft_strlen(cmd->tmp_in)
				+ ft_strlen(cmd->dollar_value[position]) - (old_len)) + 1);
	if (cmd->in == NULL)
		return ;
	replace(cmd, position, old_len, counter);
}

void	replace_global_var(t_cmd *cmd, char *var, int k)
{
	if ((cmd->quote_s == 0 && cmd->quote_d == 0)
		|| (look_for_closure('\'', '$', cmd->original,
				ft_strchr(cmd->original, '$') - (cmd->original + 1)) == 0
			&& look_for_closure('\"', '$', cmd->original,
				ft_strchr(cmd->original, '$') - (cmd->original + 1)) == 1)
		|| (look_for_closure('\'', '$', cmd->original,
				ft_strchr(cmd->original, '$') - (cmd->original + 1)) == 1
			&& look_for_open('\"', cmd->original,
				ft_strchr(cmd->original, '$') - (cmd->original + 1)) == 1))
		cmd->dollar_value[k] = search_value(var, cmd);
	else
		cmd->dollar_value[k++] = ft_strjoin("$", var);
}

int	cpy_global_var(t_cmd *cmd, int ch, int i, int k)
{
	char	*var;
	char	*question_mark;
	int		j;

	j = 0;
	while (cmd->tmp_in[i + ch] != '\'' && cmd->tmp_in[i + ch] != '\0'
		&& cmd->tmp_in[i + ch] != ' ' && cmd->tmp_in[i + ch] != '\"')
		ch++;
	var = (char *)malloc(sizeof(char) * ch + 1);
	while (cmd->tmp_in[i] && cmd->tmp_in[i] != ' ' && cmd->tmp_in[i] != '\''
		&& cmd->tmp_in[i] != '\"' && i < i + ch)
		var[j++] = cmd->tmp_in[i++];
	var[j] = '\0';
	question_mark = search_value(var, cmd);
	if (question_mark == NULL)
		printf("%s : command not found\r\n", var);
	replace_global_var(cmd, var, k);
	///PROBABLEMENTE SEA AQUÍ DONDE FALLAN LOS DOLLARES MÚLTIPLES,
	///K DEBE SER GLOBAL
	if (question_mark)
		free(question_mark);
	free(var);
	return (ch);
}

int	dollar(t_cmd *cmd, int k)
{
	int		i;
	int		ch;

	ch = 0;
	i = 0;
	while (cmd->tmp_in[i] != '$' && (cmd->tmp_in[i] != '\0'
			|| cmd->tmp_in[i] != ' '))
	{
		if (cmd->tmp_in[i] == '\0')
			break ;
		i++;
	}
	i++;
	ch = cpy_global_var(cmd, ch, i, k);
	k++;
	replace_allocation(cmd, k, ch);
	return (k);
}
