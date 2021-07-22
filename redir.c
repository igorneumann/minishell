/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineumann <ineumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 17:27:21 by ineumann          #+#    #+#             */
/*   Updated: 2021/07/22 19:14:13 by ineumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redir(t_cmd *cmd, int i)
{
	int		j;

	while (i > 0)
	{
		j = 1;
		if (cmd->in[i] == '>')
		{
			cmd->in[i] = '\0';
			while (cmd->in[i + j] == ' ' || cmd->in[i + j] == '>')
				j++;
			cmd->outp = ft_strduptochar(&cmd->in[i + j], 32);
			return (redirector(cmd, i));
		}
		else if (cmd->in[i] == '<')
		{
			cmd->in[i] = '\0';
			while (cmd->in[i + j] == ' ' || cmd->in[i + j] == '<')
				j++;
			cmd->inpt = ft_strduptochar(&cmd->in[i + j], 32);
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

int	redirinfo(t_cmd *cmd, int *fPtr, char *str)
{
	if (fPtr[0] == -1)
		printf("error al abrir archivo");
	return (0);
}

int	tempinput(t_cmd *cmd)
{
	int		size;
	int		j;
	char	*buff;
	char	*c;

	cmd->in_fd = open(".tempAF.tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	buff = ft_strdup("\x0D");
	size = ft_strlen(cmd->inpt);
	j = 0;
	c = NULL;
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &cmd->raw->orig) == -1)
		die("tcsetattr", cmd->raw);
	while (get_next_line(0, &c) > 0 && ft_strcmp(c, cmd->inpt) != 0)
	{
		buff = ft_strjoin(buff, c);
		free(c);
		c = NULL;
	}
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &cmd->raw->raw) == -1)
		die("tcsetattr", cmd->raw);
	size = (ft_strlen(buff) - size);
	j = 0;
	while (j < size)
		write(cmd->in_fd, &buff[j++], 1);
	return (close(cmd->in_fd));
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
		cmd->inpt = ft_strdup(".tempAF.tmp");
	}
	else if (cmd->inpt[0] != '\x0D')
		cmd->in_fd = open(cmd->inpt, O_RDONLY);
	if (cmd->inpt[0] != '\x0D' && cmd->in[i - 1] == '<')
		cmd->in_fd = open(cmd->inpt, O_RDONLY);
	else if (cmd->outp[0] != '\x0D')
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
