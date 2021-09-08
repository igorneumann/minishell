/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineumann <ineumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 17:27:21 by ineumann          #+#    #+#             */
/*   Updated: 2021/09/08 17:18:58 by ineumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redir(t_cmd *cmd, int i)
{
	int		j;

	while (i > 0)
	{
		j = 1;
		if (cmd->in[i] == '>' || cmd->in[i] == '<')
		{
			while (cmd->in[i + j] == ' ' || cmd->in[i + j] == '>'
				|| cmd->in[i + j] == '<')
				j++;
			if (cmd->in[i] == '>')
				free(cmd->outp);
			if (cmd->in[i] == '<')
				free(cmd->inpt);
			if (cmd->in[i] == '>')
				cmd->outp = ft_strduptochar(&cmd->in[i + j], 32);
			if (cmd->in[i] == '<')
				cmd->inpt = ft_strduptochar(&cmd->in[i + j], 32);
			cmd->in[i] = '\0';
			return (redirector(cmd, i));
		}
		i--;
	}
	return (0);
}

void	redirout(t_cmd *cmd)
{
	if (cmd->outp[0] != '\x0D')
	{
		dup2(cmd->out_fd, STDOUT_FILENO);
		close(cmd->out_fd);
	}
	if (cmd->inpt[0] != '\x0D')
	{
		dup2(cmd->in_fd, STDIN_FILENO);
		close(cmd->in_fd);
	}
}

int	tempinput(t_cmd *cmd)
{
	char	*buff;
	char	*tmp;
	char	*c;

	if (cmd->in_fd)
		close(cmd->in_fd);
	cmd->in_fd = open(".tempAF.tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	buff = ft_strdup("\x0D");
	c = NULL;
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &cmd->raw->orig) == -1)
		die("tcsetattr", cmd->raw);
	while (get_next_line(0, &c) > 0 && ft_strcmp(c, cmd->inpt) != 0)
	{
		tmp = buff;
		buff = ft_strjoin(buff, c);
		free(c);
		free(tmp);
		c = NULL;
	}
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &cmd->raw->raw) == -1)
		die("tcsetattr", cmd->raw);
	ft_putstr_fd(buff, cmd->in_fd);
	return (close(cmd->in_fd));
}

int	cleanfds(t_cmd *cmd, int i)
{
	if ((i == 1 || i == 3) && cmd->in_fd)
		close(cmd->in_fd);
	if ((i == 2 || i == 3) && cmd->out_fd)
		close(cmd->out_fd);
	return (1);
}

int	redirector(t_cmd *cmd, int i)
{
	if (ft_strlen(cmd->inpt) < 1 && cmd->in[i - 1] == '<')
	{
		ft_putstr("error: tio, hay que escribir algo despues de <<\r\n");
		return (1);
	}
	else if (cmd->inpt[0] != '\x0D' && cmd->in[i - 1] == '<')
	{
		tempinput(cmd);
		free (cmd->inpt);
		cmd->inpt = ft_strdup(".tempAF.tmp");
	}
	if (cmd->inpt[0] != '\x0D' && cleanfds(cmd, 1))
		cmd->in_fd = open(cmd->inpt, O_RDONLY);
	else if (cmd->outp[0] != '\x0D' && cleanfds(cmd, 2))
	{
		if (cmd->in[i - 1] == '>')
		{
			cmd->in[i - 1] = '\0';
			cmd->out_fd = open(cmd->outp, O_WRONLY | O_CREAT | O_APPEND, 0644);
		}
		else
			cmd->out_fd = open(cmd->outp, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	return (0);
}
