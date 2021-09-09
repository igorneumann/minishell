/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narroyo- <narroyo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 12:54:06 by narroyo-          #+#    #+#             */
/*   Updated: 2021/09/09 19:19:21 by narroyo-         ###   ########.fr       */
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
	ft_putstr("¿Ya te has perdido? Estás en \033[1m");
	ft_putstr(pwd);
	free(pwd);
	ft_putstr("\033[0m\r\n");
}

void	print_echo(t_cmd *cmd, int i, int j)
{
	if (ft_strnstr(cmd->in + i, "-n ", 3) != NULL)
	{
		cmd->echo_nl = 1;
		while (cmd->in[i + j])
		{
			if (cmd->in[i + j] == '-')
				j++;
			while (cmd->in[i + j] == 'n')
				j++;
			while (cmd->in[i + j] == ' ' && cmd->in[i + j + 1] == '-' && cmd->in[i + j + 2] == 'n')
				j += 3;
			if (cmd->in[i + j] != ' ')
				cmd->echo_nl = 2;
			while (cmd->in[i + j] == ' ')
				j++;
			if (ft_strnstr(cmd->in + i + j, "-n", 2) == NULL)
				break ;
		}
		if (cmd->echo_nl == 1)
			ft_putstr(&cmd->in[i + j]);
	}
	if (cmd->echo_nl == 0 || cmd->echo_nl == 2)
	{
		if(cmd->echo_nl == 2)
			j -= 3;
		ft_putstr(&cmd->in[i + j]);
		if (j == 0)
			ft_putstr("\r\n");
	}
}

void	ft_echo(t_cmd *cmd)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	cmd->not_found = 1;
	if (command_not_found("echo", cmd))
		return ;
	if (cmd->check_replacement == -1)
	{
		ft_putstr_fd("unexpected EOF while looking for matching\'\"\r\n", 2);
		return ;
	}
	i += 4;
	while (cmd->in[i] == ' ')
		i++;
	cmd->echo_nl = 0;
	print_echo(cmd, i, j);
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
