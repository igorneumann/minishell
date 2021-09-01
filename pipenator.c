/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipenator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineumann <ineumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 17:50:59 by ineumann          #+#    #+#             */
/*   Updated: 2021/09/01 18:44:25 by ineumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pipewhiler(t_cmd *cmd, int i)
{
	cmd->param = free_list(cmd->param);
	free(cmd->in);
	cmd->in = ft_strdup(cmd->nexpip->in);
	ft_lst_add_arguments(&cmd->param, cmd->nexpip->in);
	free(cmd->buff);
	cmd->buff = ft_strduptochar(cmd->in, 32);
	ft_path(cmd);
	middlepiper(cmd->in, cmd, ++i);
	cmd->nexpip = free_first(cmd->nexpip);
	return (i);
}

void	pipenator(t_cmd *cmd)
{
	int	i;

	i = 0;
	ft_startpipe(cmd->in, cmd);
	while (cmd->nexpip->next)
		i = pipewhiler(cmd, i);
	cmd->param = free_list(cmd->param);
	free(cmd->in);
	cmd->in = ft_strdup(cmd->nexpip->in);
	ft_lst_add_arguments(&cmd->param, cmd->nexpip->in);
	free(cmd->buff);
	cmd->buff = ft_strduptochar(cmd->in, 32);
	ft_path(cmd);
	ft_endpipe(cmd->in, cmd, i);
	cmd->param = free_list(cmd->param);
	cmd->nexpip = free_list(cmd->nexpip);
}
