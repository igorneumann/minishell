/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narroyo- <narroyo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 12:06:27 by narroyo-          #+#    #+#             */
/*   Updated: 2021/08/05 19:05:14 by narroyo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*search_value(char *elem, t_cmd *cmd)
{
	char	*question_mark;

	question_mark = ft_itoa(cmd->output_status >> 8);
	if (ft_strnstr(elem, "?", 1))
		return (question_mark);
	while (cmd->envp && ft_strcmp(elem, cmd->envp->key) != 0)
		cmd->envp = cmd->envp->next;
	if (cmd->envp->value != NULL && ft_strcmp(elem, cmd->envp->key) == 0)
		return (cmd->envp->value);
	return (NULL);
}

void	replace(t_cmd *cmd, int position, int old_len)
{
	int	counter;
	int	i;
	int	j;
	int	k;

	counter = 0;
	i = 0;
	j = 0;
	k = 0;
	position--;
	cmd->in = (char *)malloc(sizeof(char) * (ft_strlen(cmd->tmp_in)
				+ ft_strlen(cmd->dollar_value[position]) - (old_len + 1)) + 1);
	if (cmd->in == NULL)
		return ;
	while (cmd->tmp_in[k] && cmd->tmp_in[k] != '\0')
	{
		if (cmd->tmp_in[k] == '$')
		{
			if (counter == position)
			{
				j = 0;
				while (cmd->dollar_value[position][j])
				{
					cmd->in[i] = cmd->dollar_value[position][j];
					j++;
					i++;
				}
				k += old_len + 1;
				position++;
				counter++;
			}
		}
		else if (cmd->tmp_in[k] && cmd->tmp_in[k] != '\0')
		{
			if (cmd->tmp_in[k] == '\'' && quotes(cmd) % 2)
					k++;
			cmd->in[i] = cmd->tmp_in[k];
			k++;
			i++;
		}
	}
	cmd->in[i] = '\0';
}

int	cpy_global_var(t_cmd *cmd, int ch, int i, int k)
{
	char	*var;
	int		j;

	j = 0;
	while (cmd->tmp_in[i + ch] != '\'' && cmd->tmp_in[i + ch] != '\0'
		&& cmd->tmp_in[i + ch] != ' ')
		ch++;
	var = (char *)malloc(sizeof(char) * ch + 1);
	while (cmd->tmp_in[i] && cmd->tmp_in[i] != ' ' && cmd->tmp_in[i] != '\''
		&& i < i + ch)
	{
		var[j] = cmd->tmp_in[i];
		i++;
		j++;
	}
	var[j] = '\0';
	if (search_value(var, cmd) == NULL)
		printf("%s : command not found\r\n", var);
	else if (look_for_closure('\'', '$', cmd->tmp_in, i) == 1)
		cmd->dollar_value[k] = ft_strjoin("$", var);
	else
		cmd->dollar_value[k] = ft_strdup(search_value(var, cmd));
	free(var);
	return (ch);
}

int	dollar(t_cmd *cmd, int k)
{
	int		i;
	int		ch;

	ch = 0;
	i = 0;
	if (cmd->quote_s % 2 != 0)
	{
		printf("%s : command not found\r\n", cmd->tmp_in);
		return (0);
	}
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
	replace(cmd, k, ch);
	return (k);
}
