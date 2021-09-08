/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narroyo- <narroyo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 16:11:11 by narroyo-          #+#    #+#             */
/*   Updated: 2021/09/08 19:37:08 by narroyo-         ###   ########.fr       */
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

t_envp	*copy_env(t_envp *envp)
{
	t_envp	*copy_last;
	t_envp	*copy;

	copy_last = NULL;
	while (envp->prev)
		envp = envp->prev;
	while (envp)
	{
		copy = (t_envp *)malloc(sizeof(t_envp));
		if (envp->next && copy_last)
			copy_last->next = copy;
		copy->key = ft_strdup(envp->key);
		if (envp->value != NULL)
			copy->value = ft_strdup(envp->value);
		else
			copy->value = NULL;
		copy->prev = copy_last;
		copy_last = copy;
		envp = envp->next;
	}
	copy->prev->next = copy_last;
	copy->next = NULL;
	while (copy->prev)
		copy = copy->prev;
	return (copy);
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
