/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narroyo- <narroyo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 12:54:06 by narroyo-          #+#    #+#             */
/*   Updated: 2021/09/16 09:14:03 by narroyo-         ###   ########.fr       */
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
