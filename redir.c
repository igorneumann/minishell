/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineumann <ineumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 17:27:21 by ineumann          #+#    #+#             */
/*   Updated: 2021/07/20 19:47:34 by ineumann         ###   ########.fr       */
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
	if (cmd->inpt[0] != '\x0D')
		printf("Input is %s\r\n, fd is %i\r\n", str, cmd->in_fd);
	else if (cmd->outp[0] != '\x0D')
		printf("Output is %s\r\n fd is %i\r\n", str, cmd->out_fd);
	return (0);
}

void	tempinput(t_cmd *cmd)
{
	int		*fPtr;
	int		size;
	int		j;
	char	*buff;
	char	c;

	fPtr = &cmd->in_fd;
	*fPtr = open("tempAF.tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	buff = ft_strdup("\x0D");
	while (!ft_strnstr(buff, cmd->inpt, ft_strlen(buff)))
	{
		c = f_raw(cmd->raw);
		buff = ft_strjoin(cmd->in, &c);
		size = ft_strlen(buff);
	}
	size = (size - ft_strlen(cmd->inpt));
	j = 0;
	while (j <= size)
	{
		write (1, &buff[j], 1);
		write (cmd->in_fd, &buff[j], 1);
		j++;
	}
	write (cmd->in_fd, "\0", 1);
	printf("tempAF.tmp creado");
}

int	redirector(t_cmd *cmd, int i)
{
	char	*str;
	int		*fPtr;

	if (cmd->inpt[0] != '\x0D' && cmd->in[i - 1] != '<')
	{
		str = cmd->inpt;
		cmd->in_fd = open(str, O_RDONLY);
		fPtr = &cmd->in_fd;
		redirinfo(cmd, fPtr, str);
	}
	else if (cmd->inpt[0] != '\x0D')
		tempinput(cmd);
	else if (cmd->outp[0] != '\x0D')
	{
		str = cmd->outp;
		fPtr = &cmd->out_fd;
		if (cmd->in[i - 1] == '>')
		{
			cmd->in[i - 1] = '\0';
			*fPtr = open(str, O_WRONLY | O_CREAT | O_APPEND, 0644);
		}
		else
			*fPtr = open(str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	return (0);
}
