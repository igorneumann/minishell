/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineumann <ineumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 17:21:07 by ineumann          #+#    #+#             */
/*   Updated: 2021/09/29 17:36:40 by ineumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	processkeypress(t_cmd *cmd)
{
	char	c[2];
	char	*temp;

	c[0] = f_raw(cmd->raw);
	c[1] = '\0';
	if (!iscntrl(c[0]) && g_reset != 2)
	{
		if (cmd->i == (int)ft_strlen(cmd->in) && ft_isprint(c[0]))
		{
			temp = cmd->in;
			cmd->in = ft_strjoin(cmd->in, &c[0]);
			free(temp);
			ft_putchar_fd(c[0], STDOUT);
			cmd->i++;
		}
		else if (g_reset != 2 && ft_isprint(c[0]))
			ft_editstring(cmd, c[0]);
		c[0] = '\0';
	}
	if (g_reset != 2 && !ft_isprint(c[0]))
		noprintable(cmd, c[0]);
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
	free (cmd->in);
	cmd->in = ft_strjoin(res, rest);
	free (rest);
	free (res);
	ft_putstr(&cmd->in[cmd->i]);
	while (sizerest-- > 0)
		ft_putstr("\033[D");
	cmd->i++;
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
	ft_lst_add_front(&cmd->list, ft_new(cmd->in));
	reinitialize_variables(cmd);
	ft_semicolon(cmd);
	printf("\r\n");
	cmd->cmd_error = command_error(cmd);
	free(cmd->tmp_in);
	cmd->tmp_in = ft_strtrim(cmd->in, " ");
	free(cmd->in);
	cmd->in = ft_strdup(cmd->tmp_in);
	if (ft_strlen(cmd->in) > 0 && cmd->cmd_error == 0
		&& cmd->check_replacement != -1)
		ft_read_arguments(cmd);
	ft_reset(cmd);
	while (cmd->nexcom != NULL && cmd->cmd_error == 0
		&& cmd->check_replacement != -1)
	{
		free(cmd->in);
		cmd->in = ft_strdup(cmd->nexcom->in);
		cmd->nexcom = free_first(cmd->nexcom);
		if (ft_strlen(cmd->in) > 0)
			ft_read_arguments(cmd);
		ft_reset(cmd);
	}
	free_all(cmd);
}

void	noprintable(t_cmd *cmd, char c)
{
	if (c == '\x1b')
		commandkeys(cmd);
	if (c == 4 && cmd->i == 0)
	{
		ft_putstr("exit\n\r");
		die("\0", cmd->raw);
	}
	else if (c == 13)
		char_enter(cmd);
	else if (c == 127)
		ft_backspace(cmd);
	else if (c == 9)
		ft_tab(cmd);
}
