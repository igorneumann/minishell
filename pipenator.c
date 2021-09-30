/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipenator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineumann <ineumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 17:50:59 by ineumann          #+#    #+#             */
/*   Updated: 2021/09/30 17:20:38 by ineumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pipewhiler(t_cmd *cmd, int i)
{
	cmd->param = free_list(cmd->param);
	free(cmd->in);
	cmd->in = ft_strdup(cmd->nexpip->in);
	redir(cmd, ft_strlen(cmd->in), 0, 1);
	ft_lst_add_arguments(&cmd->param, cmd->nexpip->in);
	free(cmd->buff);
	cmd->buff = ft_strduptochar(cmd->in, 32, '\0');
	cleanspcback(cmd->in, ft_strlen(cmd->in));
	cleanspcback(cmd->buff, ft_strlen(cmd->buff));
	ft_path(cmd, 0);
	middlepiper(cmd->in, cmd, ++i);
	cmd->nexpip = free_first(cmd->nexpip);
	cmd->redpip += returnoutput(cmd);
	return (i);
}

void	prep_exec(t_cmd *cmd, int red)
{
	int	i;

	envp_to_arr(cmd, 0);
	i = open(cmd->in, O_RDONLY);
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &cmd->raw->orig) == -1)
		die("tcsetattr", cmd->raw);
	if (i == -1 && cmd->not_found == 0)
	{
		free(cmd->buff);
		if (red > 0)
			cmd->buff = ft_strduptochar(cmd->in, '>', '<');
		else
			cmd->buff = ft_strduptochar(cmd->in, 32, '\0');
		cleanspcback(cmd->in, ft_strlen(cmd->in));
		cleanspcback(cmd->buff, ft_strlen(cmd->buff));
		ft_path(cmd, 0);
	}
	close(i);
}

void	pipenator(t_cmd *cmd, int i)
{
	if (cmd->nexpip != NULL)
	{
		i = ft_startpipe(cmd->in, cmd);
		cmd->redpip += returnoutput(cmd);
		while (cmd->nexpip->next && i >= 0)
			i = pipewhiler(cmd, i);
		cmd->param = free_list(cmd->param);
		free(cmd->in);
		cmd->in = ft_strdup(cmd->nexpip->in);
		redir(cmd, ft_strlen(cmd->in), 0, 1);
		ft_lst_add_arguments(&cmd->param, cmd->nexpip->in);
		free(cmd->buff);
		cmd->buff = ft_strduptochar(cmd->in, 32, '\0');
		cleanspcback(cmd->in, ft_strlen(cmd->in));
		cleanspcback(cmd->buff, ft_strlen(cmd->buff));
		ft_path(cmd, 0);
		ft_endpipe(cmd->in, cmd, i);
		cmd->param = free_list(cmd->param);
		cmd->nexpip = free_list(cmd->nexpip);
	}
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &cmd->raw->raw) == -1)
		die("tcsetattr", cmd->raw);
}
