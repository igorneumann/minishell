/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_arguments.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineumann <ineumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 19:00:43 by narroyo-          #+#    #+#             */
/*   Updated: 2021/09/22 19:35:38 by ineumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_read_arguments(t_cmd *cmd)
{
	int		pip;
	int		red;
	int		noinp;

	pip = findpipes(cmd->original);
	red = findredir(cmd->original);
	noinp = 0;
	cmd->not_found = 0;
	noinp = redir(cmd, ft_strlen(cmd->in), 0, 1);
	if (noinp > 0 && cmd->inpt[0] == '\0')
		ft_putstr_fd("syntax error near unexpected token `newline'\r\n", 2);
	ft_lst_add_arguments(&cmd->param, cmd->original);
	if (pip > 0)
	{
		pipes(cmd);
		prep_exec(cmd);
		pipenator(cmd, 0);
	}
	else if (noinp == 0 && !ft_arguments(cmd))
		executor(cmd);
	cleanfds(cmd, 3, red);
}

void	builtins(t_cmd *cmd, int i)
{
	int	j;

	j = 0;
	redirout(cmd, 0);
	if (ft_strnstr(cmd->in, "echo", 4))
		ft_echo(cmd);
	else if (ft_strnstr(cmd->in, "cd", 2))
	{
		home_cd(cmd);
		ft_cd(cmd, i);
	}
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
	redirout(cmd, 1);
}

void	init_arguments(t_cmd *cmd)
{
	cmd->quote_s = 0;
	cmd->quote_d = 0;
	cmd->quotes = 0;
}

int	ft_arguments(t_cmd *cmd)
{
	int	i;

	i = 0;
	init_arguments(cmd);
	if (ft_strnstr(cmd->in, "echo", 4) || ft_strnstr(cmd->in, "cd", 2)
		|| ft_strnstr(cmd->in, "pwd", 3) || ft_strnstr(cmd->in, "export", 6)
		|| ft_strnstr(cmd->in, "unset", 5) || ft_strnstr(cmd->in, "exit", 4)
		|| ft_strnstr(cmd->in, "env", 3))
		builtins(cmd, i);
	else if (ft_strnstr(cmd->in, "$?", 2))
	{
		ft_putstr_fd(ft_itoa(cmd->output_status), 2);
		ft_putstr_fd(": command not found\r\n", 2);
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
	size = 0;
	i = quit_spaces(new, i);
	if (new[i] == '|' || new[i] == '<' || new[i] == '>' || new[i] == ';'
		|| (new[i] == '&' && new[i + 1] == '&'))
		return ;
	if (new[i] == '\"' || new[i] == '\'')
	{
		temp = parse_file_name(&new[i], 32);
		size = 2;
	}
	else
		temp = ft_strduptochar(&new[i], 32, '\0');
	ft_lst_add_front(in, ft_new(temp));
	size += ft_strlen(temp);
	while (new[i] && size--)
		i++;
	i = quit_spaces(new, i);
	if (new[i] != '\0')
		ft_lst_add_arguments(in, &new[i]);
	free(temp);
}
