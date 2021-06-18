/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_arguments.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineumann <ineumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 19:00:43 by narroyo-          #+#    #+#             */
/*   Updated: 2021/06/18 18:11:20 by ineumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	arguments(t_cmd *cmd, int i)
{
	ft_echo(cmd);
	ft_cd(cmd, i);
	ft_pwd(cmd);
	ft_env(cmd);
	ft_export(cmd);
	ft_unset(cmd);
}

void	ft_read_arguments(t_cmd *cmd)
{
	int		i;
	char	code[2];

	i = 0;
	code[0] = 0;
	code[1] = 0;
	cmd->not_found = 0;
	while (cmd->in[i] == ' ')
		i++;
	ft_lst_add_front(&cmd->list, ft_new(cmd->in));
	arguments(cmd, i);
	if (ft_strnstr(cmd->in, "exit", 4) != NULL)
	{
		cmd->not_found = 1;
		i += 4;
		while (cmd->in[i] == ' ')
			i++;
		if ((cmd->in[i] >= 0 && cmd->in[i] <= 9)
			|| cmd->in[i] == '-' || cmd->in[i] == '+')
			code[1] = ft_atoi(&cmd->in[i]);
		die(code, cmd->raw);
	}
	if (cmd->not_found == 0)
		executor(cmd);
}

void	ft_many_arguments(t_cmd *cmd)
{
	int		i;
	char	code[2];

	i = 0;
	code[0] = 0;
	code[1] = 0;
	cmd->not_found = 0;
	while (cmd->in[i] == ' ')
		i++;
	ft_lst_add_front(&cmd->list, ft_new(cmd->in));
	ft_lst_add_arguments(&cmd->param, cmd->in);
	arguments(cmd, i);
	if (ft_strnstr(cmd->in, "exit", 4) != NULL)
	{
		cmd->not_found = 1;
		i += 4;
		while (cmd->in[i] == ' ')
			i++;
		if ((cmd->in[i] >= 0 && cmd->in[i] <= 9)
			|| cmd->in[i] == '-' || cmd->in[i] == '+')
			code[1] = ft_atoi(&cmd->in[i]);
		die(code, cmd->raw);
	}
	if (cmd->not_found == 0)
		executor(cmd);
}

void	ft_lst_add_arguments(t_data **in, char *new)
{
	int		i;
	char	*temp;
	int		size;

	i = 0;
	while (new[i] == ' ')
		i++;
	temp = ft_strduptochar(&new[i], 32);
	ft_lst_add_front(in, ft_new(temp));
	size = ft_strlen(temp);
	while (new[i] && size--)
		i++;
	if (new[i] != '\0')
		ft_lst_add_arguments(in, &new[i]);
	//printf("%s\r\n", temp);
}
