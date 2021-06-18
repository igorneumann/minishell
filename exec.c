/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineumann <ineumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 18:22:39 by ineumann          #+#    #+#             */
/*   Updated: 2021/06/18 20:10:01 by ineumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	executor(t_cmd *cmd)
{
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &cmd->raw->orig) == -1)
		die("tcsetattr", cmd->raw);
	if (findpipes(cmd->in) == 0)
		exec(ft_strduptochar(cmd->in, 32), cmd);
	else
		pipes(cmd);
	wait (0);
	ft_putstr("\r\n");
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &cmd->raw->raw) == -1)
		die("tcsetattr", cmd->raw);
	return (0);
}

size_t	ft_strlentochar(const char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
	{
		i++;
	}
	return (i);
}

char	*ft_strduptochar(const char *s1, char c)
{
	char	*dest;
	int		i;

	dest = (char *)malloc(sizeof(char) * (ft_strlentochar((char *)s1, c) + 1));
	if (!dest)
		return (NULL);
	i = 0;
	while (s1[i] && s1[i] != c)
	{
		dest[i] = s1[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*copyparam(t_cmd *cmd)
{
	char	*temp;
	char	*temp2;
	char	*str;

	temp = NULL;
	if (cmd->param->in == NULL || cmd->param->next == NULL)
		return (" ");
	temp2 = ft_strjoin("\"", cmd->param->in);
	temp = ft_strjoin(temp2, "\", ");
	str = ft_strdup(temp);
	free(temp);
	free(temp2);
	while (cmd->param->next != NULL && cmd->param->next->in != NULL)
	{
		cmd->param = cmd->param->next;
		temp2 = ft_strdup(str);
		str = ft_strjoin(copyparam(cmd), temp2);
		free(temp2);
	}
	printf("ParmList is %s\r\n", str);
	return (str);
}

int	exec(char *str, t_cmd *cmd)
{
	pid_t	pid;
	char	*parmList;
	char	*envParms[2];

	parmList = NULL;
	if (cmd->param != NULL && cmd->param->next != NULL)
		parmList = ft_strdup(copyparam(cmd));
	envParms[0] = "STEPLIB=SASC.V6.LINKLIB";
	envParms[1] = NULL;
	cmd->param = freelist(cmd->param);
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
	}
	return (0);
}
