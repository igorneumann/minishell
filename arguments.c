/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narroyo- <narroyo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 12:54:06 by narroyo-          #+#    #+#             */
/*   Updated: 2021/06/03 16:22:22 by narroyo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(t_cmd *cmd)
{
	if (ft_strnstr(cmd->in, "pwd", 3))
	{
		ft_putstr("¿Ya te has perdido? Estás en \033[1m");
		ft_putstr(getcwd(NULL, -1));
		ft_putstr("\033[0m\r\n");
	}
}

void	ft_include(t_cmd *cmd, char *aux)
{
	while (cmd->envp->next)
		cmd->envp = cmd->envp->next;
	ft_lst_add_back((t_data **)&cmd->envp, (t_data *)ft_new_env(aux));
}

void	ft_export(t_cmd *cmd)
{
	char	**aux;
	int		i;

	i = 0;
	if (ft_strnstr(cmd->in, "export", 6))
	{
		while (cmd->in[i])
		{
			if (cmd->in[i] != ' ')
				i++;
			if (cmd->in[i] == '\0')
				ft_sort_env(cmd);
			if (cmd->in[i] == ' ')
			{
				aux = ft_split(cmd->in, ' ');
				ft_include(cmd, aux[1]);
				free(aux);
				break ;
			}
		}
	}
}

void	ft_echo(t_cmd *cmd)
{
	int	i;

	i = 0;
	if (ft_strnstr(cmd->in, "echo", 4) != NULL)
	{
		i += 4;
		while (cmd->in[i] == ' ' || cmd->in[i] == '\'')
			i++;
		if (ft_strnstr(cmd->in + i, "-n", 2) != NULL)
		{
			i += 2;
			while (cmd->in[i] == ' ' || cmd->in[i] == '\'')
				i++;
			if (cmd->in[i] != 0)
				ft_putstr(&cmd->in[i]);
		}
		else
		{
			ft_putstr(&cmd->in[i]);
			ft_putstr("\r\n");
		}
	}
}

void	ft_cd(t_cmd *cmd, int i)
{
	char	old_path[2048];
	char	path[2048];
	int		j;
	int		ok;

	j = 0;
	if (ft_strnstr(cmd->in, "cd", 2) != NULL)
	{
		getcwd(old_path, 2048);
		i += 3;
		while (cmd->in[i] != '\0')
			path[j++] = cmd->in[i++];
		ok = chdir(path);
		if (ok != 0)
			ft_putstr("Lagrimita\r\n");
		else
			getcwd(path, 2048);
	}
}
