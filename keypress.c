/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineumann <ineumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 17:21:07 by ineumann          #+#    #+#             */
/*   Updated: 2021/06/23 19:55:36 by ineumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	processkeypress(t_cmd *cmd)
{
	char	c;
	char	*tmp;

	c = f_raw(cmd->raw);
	while (!iscntrl(c))
	{
		tmp = cmd->in;
		if (cmd->i == (int)ft_strlen(cmd->in))
		{
			cmd->in = ft_strjoin(cmd->in, &c);
			ft_putstr(&cmd->in[cmd->i]);
			cmd->i++;
		}
		else
			ft_editstring(cmd, c);
		free(tmp);
		c = '\0';
	}
	noprintable(cmd, c);
}

void	ft_editstring(t_cmd *cmd, char c)
{
	char	*rest;
	char	*res;
	char	ch[2];
	int		sizerest;

	ch[0] = c;
	ch[1] = '\0';
	rest = ft_strdup(&cmd->in[cmd->i]);
	sizerest = (int)ft_strlen(rest);
	cmd->in[cmd->i] = '\0';
	res = ft_strjoin(cmd->in, ch);
	cmd->in = ft_strjoin(res, rest);
	ft_putstr(&cmd->in[cmd->i]);
	while (sizerest-- > 0)
		ft_putstr("\033[D");
	cmd->i++;
	free (res);
	free (rest);
}

void	ft_backspace(t_cmd *cmd)
{
	int	i;

	i = 0;
	if (cmd->i > 0)
	{
		ft_putstr("\033[D \033[D");
		cmd->i--;
		while (cmd->in[cmd->i + i + 1] != '\0')
		{
			cmd->in[cmd->i + i] = cmd->in[cmd->i + i + 1];
			i++;
		}
		cmd->in[cmd->i + i] = '\0';
		ft_putstr(&cmd->in[cmd->i]);
		ft_putstr(" \033[D");
		while (i-- > 0)
			ft_putstr("\033[D");
	}
}

void	ft_enter(t_cmd *cmd)
{
	cmd->buff = ft_strdup(cmd->in);
	ft_semicolon(cmd);
	printf("\r\n");
	if (ft_strlen(cmd->in) > 0)
		ft_read_arguments(cmd);
	while (cmd->nexcom != NULL)
	{
		cmd->in = ft_strdup(cmd->nexcom->in);
		cmd->nexcom = cmd->nexcom->next;
		ft_read_arguments(cmd);
		cmd->list->in = ft_strdup(cmd->buff);
	}
	free(cmd->in);
	cmd->in = ft_strdup("\x0D");
	free(cmd->buff);
	cmd->buff = ft_strdup("\x0D");
	cmd->i = 0;
}

void	noprintable(t_cmd *cmd, char c)
{
	if (c == '\x1b')
		commandkeys(cmd);
	if (c == 4 && cmd->i == 0)
		die("\0", cmd->raw);
	else if (c == 13)
		ft_enter(cmd);
	else if (c == 127)
		ft_backspace(cmd);
	else if (c == 9)
		ft_tab(cmd);
//	else if (c != 0 && c != 4)
//		printf("%d\r\n", c);
}
