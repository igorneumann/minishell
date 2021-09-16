/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narroyo- <narroyo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 21:12:53 by narroyo-          #+#    #+#             */
/*   Updated: 2021/09/16 09:37:42 by narroyo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_counters(t_cmd *cmd)
{
	cmd->d_counter = 0;
	cmd->c_replace = 0;
	cmd->c2_replace = 0;
	cmd->counter = 0;
	cmd->dc = -1;
	cmd->without_quotes = NULL;
	cmd->old_len = NULL;
}

int	question_mark(t_cmd *cmd, char	*var)
{
	char	*question_mark;

	question_mark = search_value(var, cmd);
	if (question_mark == NULL)
	{
		cmd->dollar_value[cmd->d_counter++] = ft_strdup("\0");
		free(var);
		return (0);
	}
	if (question_mark)
		free(question_mark);
	return (1);
}

void	free_all(t_cmd *cmd)
{
	if (cmd->original)
		free(cmd->original);
	if (cmd->without_quotes)
		free(cmd->without_quotes);
	if (cmd->tmp_in)
		free(cmd->tmp_in);
	if (cmd->old_len)
		free(cmd->old_len);
}

int	ctrl_d_c(t_cmd *cmd, char *seq)
{
	if (seq[1] == 'D')
	{
		if (cmd->i > 0)
		{
			ft_putstr("\033[D");
			cmd->i--;
		}
		return (1);
	}
	else if (seq[1] == 'C')
	{
		if (cmd->in[cmd->i] != '\0')
		{
			ft_putstr("\033[C");
			cmd->i++;
		}
		return (1);
	}
	return (0);
}

void	open_files(t_cmd *cmd, int i, int j)
{
	if (cmd->in[i - j] == ' ')
		j++;
	if (cmd->in[i - j] == '>')
	{
		cmd->in[i - 1] = '\0';
		cmd->out_fd = open(cmd->outp, O_WRONLY | O_CREAT | O_APPEND, 0644);
	}
	else
		cmd->out_fd = open(cmd->outp, O_WRONLY | O_CREAT | O_TRUNC, 0644);
}
