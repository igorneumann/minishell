/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_arguments.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narroyo- <narroyo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 19:00:43 by narroyo-          #+#    #+#             */
/*   Updated: 2021/09/13 09:58:36 by narroyo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_read_arguments(t_cmd *cmd)
{
	int		pip;
	int		red;
	int		noinp;

	pip = findpipes(cmd->in);
	red = findredir(cmd->in);
	noinp = 0;
	cmd->not_found = 0;
	if (red > 0 && redir(cmd, ft_strlen(cmd->in)) > 0)
		noinp = 1;
	ft_lst_add_arguments(&cmd->param, cmd->in);
	if (pip > 0)
	{
		pipes(cmd);
		pipenator(cmd);
	}
	else if (!ft_arguments(cmd) && noinp == 0)
		executor(cmd);
	unlink(".tempAF.tmp");
	if (red)
		cleanfds(cmd, 3);
}

void	builtins(t_cmd *cmd, int i)
{
	int	j;

	j = 0;
	if (ft_strnstr(cmd->in, "echo", 4))
		ft_echo(cmd);
	else if (ft_strnstr(cmd->in, "cd", 2))
		ft_cd(cmd, i);
	else if (ft_strnstr(cmd->in, "pwd", 3))
		ft_pwd(cmd);
	else if (ft_strnstr(cmd->in, "export", 6))
		ft_export(cmd);
	else if (ft_strnstr(cmd->in, "unset", 5))
		ft_unset(cmd);
	else if (ft_strnstr(cmd->in, "exit", 4))
		ft_exit(cmd, i);
	else if (ft_strnstr(cmd->in, "env", 3))
		ft_env(cmd);
}

int	ft_arguments(t_cmd *cmd)
{
	int	i;

	i = 0;
	cmd->quote_s = 0;
	cmd->quote_d = 0;
	cmd->quotes = 0;
	cmd->output_status = 0;
	while (cmd->in[i] == ' ')
		i++;
	if (ft_strnstr(cmd->in, "echo", 4) || ft_strnstr(cmd->in, "cd", 2)
		|| ft_strnstr(cmd->in, "pwd", 3) || ft_strnstr(cmd->in, "export", 6)
		|| ft_strnstr(cmd->in, "unset", 5) || ft_strnstr(cmd->in, "exit", 4)
		|| ft_strnstr(cmd->in, "env", 3))
		builtins(cmd, i);
	else if (ft_strnstr(cmd->in, "$?", 2))
	{
		i = cmd->output_status >> 8;
		ft_putstr_fd(ft_itoa(i), 2);
		ft_putstr_fd(": command not found\r\n", 2);
		cmd->output_status = 127;
	}
	else
		return (0);
	return (1);
}

void	ft_lst_add_arguments(t_data **in, char *new)
{
	int		i;
	char	*temp;
	int		size;

	i = 0;
	while (new[i] == ' ')
		i++;
	if (new[i] != '|' && new[i] != '<' && new[i] != '>')
	{
		temp = ft_strduptochar(&new[i], 32);
		ft_lst_add_front(in, ft_new(temp));
		size = ft_strlen(temp);
		while (new[i] && size--)
			i++;
		while (new[i] == ' ')
			i++;
		if (new[i] != '\0')
			ft_lst_add_arguments(in, &new[i]);
		free(temp);
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
