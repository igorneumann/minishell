/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narroyo- <narroyo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 17:27:21 by ineumann          #+#    #+#             */
/*   Updated: 2021/09/19 13:27:24 by narroyo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redir(t_cmd *cmd, int i, int j, int k)
{
	while (k <= i && cmd->inpt[0] == '\r' && cmd->outp[0] == '\r')
	{
		if ((cmd->in[k] == '>')
			|| (cmd->in[k] == '<' && cmd->inpt[0] == '\r'))
		{
			while (cmd->in[k + j] == ' ' || cmd->in[k + j] == '>'
				|| cmd->in[k + j] == '<')
				j++;
			if (cmd->in[k] == '>')
				free(cmd->outp);
			if (cmd->in[k] == '<')
				free(cmd->inpt);
			if (cmd->in[k] == '>')
				cmd->outp = parse_file_name(cmd, &cmd->in[k + j], 32);
			if (cmd->in[k] == '<')
				cmd->inpt = parse_file_name(cmd, &cmd->in[k + j], 32);
			cleanspcback(cmd->in, k);
		}
		k++;
	}
	if (cmd->outp[0] != '\x0D' || cmd->inpt[0] != '\x0D')
		return (redirector(cmd, k, 1));
	return (0);
}

void	redirout_one(t_cmd *cmd, int	*in[2], int *out[2])
{
	if (cmd->outp[0] != '\x0D' && out[0] > 0 && out[1] > 0)
	{
		*out[0] = dup(STDOUT_FILENO);
		dup2(*out[1], STDOUT_FILENO);
		close(*out[1]);
	}
	if (cmd->inpt[0] != '\x0D' && in[0] > 0 && in[1] > 0)
	{
		*in[0] = dup(STDIN_FILENO);
		dup2(*in[1], STDIN_FILENO);
		close(*in[1]);
	}
}

void	redirout(t_cmd *cmd, int i)
{
	int	*in[2];
	int	*out[2];

	if (i == 0)
	{
		in[0] = &cmd->bkp_fdin;
		in[1] = &cmd->in_fd;
		out[0] = &cmd->bkp_fdout;
		out[1] = &cmd->out_fd;
	}
	else if (i == 1)
	{
		in[0] = &cmd->in_fd;
		in[1] = &cmd->bkp_fdin;
		out[0] = &cmd->out_fd;
		out[1] = &cmd->bkp_fdout;
	}
	redirout_one(cmd, in, out);
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

int	redirector(t_cmd *cmd, int i, int j)
{
	if (ft_strlen(cmd->inpt) < 1 && cmd->in[i - 1] == '<')
	{
		ft_putstr_fd("syntax error near unexpected token `newline'\r\n", 2);
		return (1);
	}
	else if (cmd->inpt[0] != '\x0D' && cmd->in[i - 1] == '<')
	{
		tempinput(cmd);
		free (cmd->inpt);
		cmd->inpt = ft_strdup(".tempAF.tmp");
	}
	if (cmd->inpt[0] != '\x0D' && cleanfds(cmd, 1, 1))
		cmd->in_fd = open(cmd->inpt, O_RDONLY);
	else if (cmd->outp[0] != '\x0D' && cleanfds(cmd, 2, 1))
		open_files(cmd, i, j);
	return (check_fds(cmd, i));
}
