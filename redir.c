/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineumann <ineumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 17:27:21 by ineumann          #+#    #+#             */
/*   Updated: 2021/07/06 20:21:32 by ineumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redir(t_cmd *cmd)
{
	int		i;
	int		j;

	i = ft_strlen(cmd->in);
	while (i > 0)
	{
		j = 1;
		if (cmd->in[i] == '>')
		{
			cmd->in[i] = '\0';
			while (cmd->in[i + j] == ' ' || cmd->in[i + j] == '>')
				j++;
			cmd->outp = ft_strduptochar(&cmd->in[i + j], 32);
		}
		else if (cmd->in[i] == '<')
		{
			cmd->in[i] = '\0';
			while (cmd->in[i + j] == ' ' || cmd->in[i + j] == '<')
				j++;
			cmd->inpt = ft_strduptochar(&cmd->in[i + j], 32);
		}
		i--;
	}
	redirector(cmd);
	return (0);
}

void	redirout(t_cmd *cmd)
{
	if (cmd->outp[0] != '\x0D')
	{
		dup2(cmd->out_fd, STDOUT_FILENO);
		close(cmd->out_fd);
	}
}

void	redirector(t_cmd *cmd)
{
	char	*str;
	char	c;
	int		*fPtr;

	c = 0;
	if (cmd->inpt[0] != '\x0D')
	{
		str = cmd->inpt;
		cmd->in_fd = open(str, O_RDONLY);
		fPtr = &cmd->in_fd;
	//	while (read(cmd->in_fd, &c, 1) != -1)
	//		cmd->inpt = ft_strjoin(cmd->inpt, &c);
	}
	else
	{
		str = cmd->outp;
		cmd->out_fd = open(str, O_WRONLY | O_CREAT | O_TRUNC | O_APPEND, 0644);
		fPtr = &cmd->out_fd;
	}
	if (fPtr[0] == -1)
		printf("error al abrir archivo");
	if (cmd->inpt[0] != '\x0D')
		printf("Input is %s\r\n, fd is %i\r\n", str, cmd->in_fd);
	else if (cmd->outp[0] != '\x0D')
		printf("Output is %s\r\n fd is %i\r\n", str, cmd->out_fd);
}
