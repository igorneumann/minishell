/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineumann <ineumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 12:54:06 by narroyo-          #+#    #+#             */
/*   Updated: 2021/09/13 19:00:19 by ineumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(t_cmd *cmd)
{
	char	*pwd;

	cmd->not_found = 1;
	if (command_not_found("pwd", cmd))
		return ;
	pwd = getcwd(NULL, -1);
	ft_putstr(pwd);
	free(pwd);
	ft_putstr("\r\n");
}

void	previous_folder(char *path, char *old_path, int j)
{
	if (ft_strnstr(path, "..", 2) != NULL)
	{
		j = ft_strlen(old_path);
		if (old_path[j] == '/')
			old_path[j--] = '\0';
		while (old_path[j] != '/')
			old_path[j--] = '\0';
		ft_memcpy(path, old_path, 2048);
	}
}

void	ft_cd(t_cmd *cmd, int i)
{
	char	old_path[2048];
	char	path[2048];
	int		j;

	j = 0;
	if (ft_strnstr(cmd->in, "cd", 2) != NULL)
	{
		cmd->not_found = 1;
		if (command_not_found("cd", cmd))
			return ;
		getcwd(old_path, 2048);
		i += 2;
		if (cmd->in[i] == '\0')
			return ;
		else
			i++;
		while (cmd->in[i] != '\0')
			path[j++] = cmd->in[i++];
		path[j] = '\0';
		previous_folder(path, old_path, j);
		if (chdir(path) != 0)
			printf("%s\r\n", strerror(errno));
		else
			getcwd(path, 2048);
	}
}

void	ft_exit(t_cmd *cmd, int i)
{
	int		j;
	char	code[2];

	j = i;
	code[0] = 0;
	code[1] = 0;
	j += 4;
	cmd->not_found = 1;
	if (command_not_found("exit", cmd))
		return ;
	while (cmd->in[j] == ' ')
		j++;
	if ((cmd->in[j] >= 0 && cmd->in[j] <= 9)
		|| cmd->in[j] == '-' || cmd->in[j] == '+')
		code[1] = ft_atoi(&cmd->in[j]);
	free_env(cmd->envp);
	die(code, cmd->raw);
}
