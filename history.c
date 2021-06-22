/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineumann <ineumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 17:19:56 by ineumann          #+#    #+#             */
/*   Updated: 2021/06/17 18:21:09 by ineumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_history(t_cmd *cmd, char *seq)
{
	t_data	*first;

	if (cmd->list == NULL && seq)
		return (0);
	if (seq[1] == 'B' && cmd->buff[0] == 13)
		return (0);
	if (ft_strcmp(cmd->buff, cmd->list->in) != 0 && cmd->buff[0] != 13)
		ft_lst_edit(&cmd->list, ft_new(cmd->in));
	first = ft_lst_first(cmd->list);
	if (seq[1] == 'A' && (cmd->in[0] == '\0'
			|| (ft_strcmp(cmd->in, cmd->list->in) != 0
				&& ft_strcmp(cmd->in, cmd->buff) != 0)))
		ft_dupin(cmd, 2);
	else if (seq[1] == 'A' && cmd->list->next != NULL)
		cmd->list = cmd->list->next;
	else if (seq[1] == 'B' && cmd->list->prev != NULL)
		cmd->list = cmd->list->prev;
	if (seq[1] == 'B' && cmd->list->prev == NULL
		&& ft_strcmp(cmd->in, first->in) == 0)
		ft_dupin(cmd, 0);
	else
		ft_dupin(cmd, 1);
	cmd->i = ft_strlen(cmd->in);
	ft_putstr(cmd->in);
	return (1);
}

void	ft_dupin(t_cmd *cmd, int src)
{
	int	i;

	if (src == 2)
	{
		free (cmd->buff);
		cmd->buff = ft_strdup(cmd->in);
	}
	else
	{
		i = ft_strlen(cmd->in);
		while (i-- > 0)
			ft_putstr("\033[D \033[D");
		free (cmd->in);
		if (src == 1)
			cmd->in = ft_strdup(cmd->list->in);
		else if (src == 0)
		{
			cmd->in = ft_strdup(cmd->buff);
			free(cmd->buff);
			cmd->buff = ft_strdup("\x0D");
		}
	}
}

int	ft_altarrow(t_cmd *cmd)
{
	int		i;
	int		j;
	char	seq[2];

	i = cmd->i;
	if (read(STDIN_FILENO, &seq[0], 1) != 1)
		return ('\x1b');
	if (read(STDIN_FILENO, &seq[1], 1) != 1)
		return ('\x1b');
	if (seq[0] == '5')
		ft_arrows(cmd, seq);
	j = strlen(cmd->in);
	if (i < j)
		seq[1] = 'D';
	while (i < j--)
		ft_arrows(cmd, seq);
	return (1);
}
