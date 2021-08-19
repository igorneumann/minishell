/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipenator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineumann <ineumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 17:50:59 by ineumann          #+#    #+#             */
/*   Updated: 2021/08/19 18:21:43 by ineumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pipenator(t_cmd *cmd)
{
	int	i;

	i = 0;
	ft_startpipe(ft_strduptochar(cmd->in, 32), cmd);
	while (cmd->nexpip->next)
	{
		cmd->param = freelist(cmd->param);
		cmd->in = ft_strdup(cmd->nexpip->in);
		ft_lst_add_arguments(&cmd->param, cmd->nexpip->in);
		cmd->buff = ft_strduptochar(cmd->in, 32);
		ft_path(cmd);
		middlepiper(ft_strduptochar(cmd->in, 32), cmd, ++i);
		cmd->nexpip = cmd->nexpip->next;
	}
	cmd->param = freelist(cmd->param);
	cmd->in = ft_strdup(cmd->nexpip->in);
	ft_lst_add_arguments(&cmd->param, cmd->nexpip->in);
	cmd->buff = ft_strduptochar(cmd->in, 32);
	ft_path(cmd);
	ft_endpipe(ft_strduptochar(cmd->in, 32), cmd, i);
	cmd->param = freelist(cmd->param);
	cmd->nexpip = freelist(cmd->nexpip);
}

/*void	replacec(char *str, char *newstr)
{
	if (str)
		free(str);makew
	str = newstr;
}

int	pipewhiler(t_cmd *cmd, int j)
{
	int		i;

	i = j;
	cmd->param = freelist(cmd->param);
	replacec(cmd->in, ft_strdup(cmd->nexpip->in));
	ft_lst_add_arguments(&cmd->param, cmd->nexpip->in);
	replacec(cmd->buff, ft_strduptochar(cmd->in, 32));
	ft_path(cmd);
	middlepiper(ft_strduptochar(cmd->in, 32), cmd, ++i);
	cmd->nexpip = cmd->nexpip->next;
	return (i);
}

void	pipenator(t_cmd *cmd)
{
	int	i;

	i = 0;
	ft_startpipe(ft_strduptochar(cmd->in, 32), cmd);
	while (cmd->nexpip->next)
		i = pipewhiler(cmd, i);
	cmd->param = freelist(cmd->param);
	replacec(cmd->in, ft_strdup(cmd->nexpip->in));
	ft_lst_add_arguments(&cmd->param, cmd->nexpip->in);
	replacec(cmd->buff, ft_strduptochar(cmd->in, 32));
	ft_path(cmd);
	ft_endpipe(ft_strduptochar(cmd->in, 32), cmd, i);
	cmd->param = freelist(cmd->param);
	cmd->nexpip = freelist(cmd->nexpip);
}*/
