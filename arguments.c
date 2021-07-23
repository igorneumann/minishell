/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narroyo- <narroyo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 12:54:06 by narroyo-          #+#    #+#             */
/*   Updated: 2021/07/23 11:32:10 by narroyo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(t_cmd *cmd)
{
	cmd->not_found = 1;
	if (command_not_found("pwd", cmd))
		return ;
	ft_putstr("¿Ya te has perdido? Estás en \033[1m");
	ft_putstr(getcwd(NULL, -1));
	ft_putstr("\033[0m\r\n");
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
	i += 4;
	while (cmd->in[i] == ' ' || cmd->in[i] == '\'')
		i++;
	if (ft_strnstr(cmd->in + i, "-n", 2) != NULL)
	{
		i += 2;
		while (cmd->in[i] == ' ' || cmd->in[i] == '\'')
			i++;
		if (cmd->in[i] != 0 && cmd->in[i] == '$'
			&& cmd->dollar_value[j] != NULL)
		{
			while (cmd->in[i] != ' ' && cmd->in[i] != 0)
				i++;
			ft_putstr(cmd->dollar_value[j]);
			j++;
		}
		if (cmd->in[i] != 0 && cmd->in[i] != '\'')
			ft_putstr(&cmd->in[i]);
		if (cmd->in[i] == '\'')
			i++;
	}
	else
	{
		while (cmd->in[i] != 0)
		{
			if (cmd->in[i] == '$' && cmd->dollar_value[j] != NULL)
			{
				while (cmd->in[i] != ' ' && cmd->in[i] != 0)
					i++;
				ft_putstr(cmd->dollar_value[j]);
				j++;
			}
			else
				ft_putchar_fd(cmd->in[i++], 1);
		}
		ft_putstr("\r\n");
	}
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
