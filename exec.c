/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineumann <ineumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 18:22:39 by ineumann          #+#    #+#             */
/*   Updated: 2021/06/16 19:43:17 by ineumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	executor(t_cmd *cmd)
{
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &cmd->raw->orig) == -1)
		die("tcsetattr", cmd->raw);
	if (findpipes(cmd->in) == 0)
		exec(ft_strdup(cmd->in), cmd);
	else
		pipes(cmd);
	wait (0);
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &cmd->raw->raw) == -1)
		die("tcsetattr", cmd->raw);
	ft_putstr("\r\n");
	return (0);
}

void	copyparam(t_cmd *cmd, char *to, int param)
{
	to = malloc(sizeof(char*) * (lst_size((t_envp *)cmd->list) + 1));
	if (cmd->list->in != NULL)
		to[param] = *ft_strdup(cmd->list->in);
	if (cmd->list->next != NULL)
	{
		cmd->list = cmd->list->next;
		copyparam(cmd, to, (param + 1));
	}
}

int	exec(char *str, t_cmd *cmd)
{
	pid_t	pid;
	char	*parmList;
	char	*envParms[2];

	parmList = NULL;
	if (cmd->list != NULL)
		copyparam(cmd, parmList, 0);
	envParms[0] = "STEPLIB=SASC.V6.LINKLIB";
	envParms[1] = NULL;
	pid = fork();
	if (pid == -1)
	{
		perror("fork error");
		return (1);
	}
	else if (pid == 0)
	{
		execve(str, &parmList, envParms);
		if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &cmd->raw->raw) == -1)
			die("tcsetattr", cmd->raw);
		printf("%s : command not found\r\n", cmd->in);
		exit(0);
		return (1);
	}
	return (0);
}
