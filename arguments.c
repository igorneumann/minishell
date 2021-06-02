/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narroyo- <narroyo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 12:54:06 by narroyo-          #+#    #+#             */
/*   Updated: 2021/06/01 16:19:25 by narroyo-         ###   ########.fr       */
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

void	ft_sort_env(t_cmd *cmd)
{
	ft_print_env(cmd->envp);
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
