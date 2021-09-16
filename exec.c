/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narroyo- <narroyo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 18:22:39 by ineumann          #+#    #+#             */
/*   Updated: 2021/09/16 20:46:12 by narroyo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	executor(t_cmd *cmd)
{
	prep_exec(cmd);
	if (cmd->nexpip == NULL)
	{
		free(cmd->buff);
		cmd->buff = ft_strduptochar(cmd->in, 32);
		exec(cmd->buff, cmd);
	}
	wait (0);
	redirout(cmd, 1);
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &cmd->raw->raw) == -1)
		die("tcsetattr", cmd->raw);
	return (0);
}

size_t	ft_strlentochar(const char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
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
	while (s1[i]
		&& ((look_for_closure('\"', s1[i], (char *)s1, i) == 0 && s1[i] != c)
			|| (look_for_closure('\'', s1[i], (char *)s1, i) == 0 && s1[i] != c)
			|| s1[i] != '\0'))
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

	i = 1;
	if (cmd->param != NULL)
		i = (lst_size ((struct s_envp *) &cmd->param));
	arg = malloc (sizeof(char *) * (i + 1));
	arg[i] = NULL;
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
	char	**parm_list;
	char	*error;

	pid = fork();
	parm_list = copyparam(cmd);
	error = NULL;
	if (pid == -1)
	{
		perror("fork error");
		return (1);
	}
	else if (pid == 0)
	{
		redirout(cmd, 0);
		execve(str, parm_list, cmd->env);
		error = ft_strjoin(cmd->in, ": command not found\r\n");
		ft_putstr_fd(error, 2);
		free(error);
		exit(127);
	}
	else
		wait(&cmd->output_status);
	free(parm_list);
	return (0);
}
