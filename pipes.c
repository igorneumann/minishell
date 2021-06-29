/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineumann <ineumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 19:10:34 by ineumann          #+#    #+#             */
/*   Updated: 2021/06/29 18:20:31 by ineumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pipes(t_cmd *cmd)
{
	int		i;
	int		j;

	i = ft_strlen(cmd->in);
	while (i > 0)
	{
		j = 1;
		if (cmd->in[i] == '|')
		{
			cmd->in[i] = '\0';
			while (cmd->in[i + j] == ' ')
				j++;
			ft_lst_add_front(&cmd->nexpip, ft_new(&cmd->in[i + j]));
		}
		else if (cmd->in[i] == '>')
		{
			cmd->in[i] = '\0';
			while (cmd->in[i + j] == ' ')
				j++;
			cmd->outp = ft_strdup(&cmd->in[i + j]);
		}
		i--;
	}
	return (0);
}

/*void	printpip(t_cmd *cmd) //YA NO LO NECESITO
{
	int	i;

	i = 0;
	if (cmd->nexpip != NULL)
	{
		while (cmd->nexpip->next != NULL)
		{
			i++;
			ft_putstr("Pipe ");
			ft_putstr(ft_itoa(i));
			ft_putstr(cmd->nexpip->in);
			ft_putstr("\r\n");
			cmd->nexpip = cmd->nexpip->next;
		}
		ft_putstr("Pipe ");
		ft_putstr(ft_itoa(++i));
		ft_putstr(cmd->nexpip->in);
		ft_putstr("\r\n");
	}
	if (cmd->outp != NULL)
	{
		ft_putstr("Output is ");
		ft_putstr(cmd->outp);
		ft_putstr("\r\n");
	}
}*/

void	runpip(t_cmd *cmd)
{
	int		fd[2];
	int		status;
	char	**parmList;
	int		pid;

	pipe(fd);
	ft_putstr("YAY, PIPES!\r\n");
	parmList = copyparam(cmd);
	pid = fork();
	if (pid == 0)
	{
		close(fd[READ_END]);
		dup2(fd[WRITE_END], STDOUT_FILENO);
		close(fd[WRITE_END]);
		if (!ft_arguments(cmd, 0))
			execve(cmd->in, parmList, cmd->envorg);
	}
	else
		close(fd[WRITE_END]);
	pid = fork();
	if (pid == 0)
	{
		cmd->buff = ft_strduptochar(cmd->nexpip->in, 32);
		ft_path(cmd);
		dup2(fd[READ_END], STDIN_FILENO);
		close(fd[READ_END]);
		if (!ft_arguments(cmd, 0))
			execve(cmd->in, parmList, cmd->envorg);
	}
	else
		close(fd[READ_END]);
	ft_putstr("\r\n");
	wait(&status);
	wait(&status);
}
