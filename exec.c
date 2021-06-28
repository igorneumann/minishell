/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narroyo- <narroyo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 18:22:39 by ineumann          #+#    #+#             */
/*   Updated: 2021/06/28 17:39:52 by narroyo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	executor(t_cmd *cmd)
{
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &cmd->raw->orig) == -1)
		die("tcsetattr", cmd->raw);
	if (open(cmd->in, O_RDONLY) == -1 && cmd->not_found == 0)
	{
		cmd->other_cmd = ft_strduptochar(cmd->in, 32);
		ft_path(cmd);
	}
	if (findpipes(cmd->in) == 0)
		exec(ft_strduptochar(cmd->in, 32), cmd);
	else
		pipes(cmd);
	wait (0);
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
	int		size;

	size = ft_strlentochar((char *)s1, c);
	dest = (char *)malloc(sizeof(char) * (size + 1));
	ft_bzero(dest, size);
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

char	**copyparam(t_cmd *cmd)
{
	char	**arg;
	int		i;

	if (cmd->param != NULL)
		i = (lst_size ((struct s_envp *) &cmd->param));
	else
		i = 1;
	if (i < 1)
		i = 1;
	arg = malloc (sizeof(char **) * i);
	if (cmd->param != NULL && cmd->param->in != NULL)
		arg[--i] = cmd->param->in;
	while (cmd->param != NULL && cmd->param->next != NULL && i > 0)
	{
		cmd->param = cmd->param->next;
		arg[--i] = cmd->param->in;
	}
	return (arg);
}

int	exec(char *str, t_cmd *cmd)
{
	pid_t	pid;
	char	**parmList;

	pid = fork();
	parmList = copyparam(cmd);
	if (pid == -1)
	{
		perror("fork error");
		return (1);
	}
	else if (pid == 0)
	{
		if (cmd->not_found == 0)
			execve(str, parmList, cmd->env);
		if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &cmd->raw->raw) == -1)
			die("tcsetattr", cmd->raw);
		if (cmd->not_found == 0)
			printf("%s: command not found\r\n", cmd->in);
		exit(0);
	}
	cmd->param = freelist(cmd->param);
	return (0);
}
