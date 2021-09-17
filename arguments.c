/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narroyo- <narroyo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 12:54:06 by narroyo-          #+#    #+#             */
/*   Updated: 2021/09/17 10:17:21 by narroyo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	quotes_command_error(t_cmd *cmd, char *str)
{
	int		i;
	char	*error;

	i = ft_strlen(str);
	error = NULL;
	if ((look_for_closure('\'', cmd->original[i], cmd->original,
				cmd->original - ft_strnstr(cmd->original, str, i)) == 1
			&& cmd->original[(ft_strnstr(cmd->original, str, i)
					- cmd->original) + 1] != '\'')
		|| (look_for_closure('\"', cmd->original[i], cmd->original,
				cmd->original - ft_strnstr(cmd->original, str, i) == 1
				&& cmd->original[(ft_strnstr(cmd->original, str, i)
						- cmd->original) + 1] != '\"')))
	{
		error = ft_strjoin(cmd->in, " : command not found\r\n");
		cmd->output_status = 127;
		ft_putstr_fd(error, 2);
		free(error);
		return (1);
	}
	return (0);
}

int	command_not_found(char *str, t_cmd *cmd)
{
	int		i;
	int		ret;
	char	*error;

	i = ft_strlen(str);
	ret = 0;
	error = NULL;
	if (ft_strnstr(cmd->in, str, ft_strlen(str)))
	{
		if (cmd->in[i] != ' ' && cmd->in[i] != '\0')
		{
			error = ft_strjoin(cmd->in, " : command not found\r\n");
			cmd->output_status = 127;
			ft_putstr_fd(error, 2);
			free(error);
			ret = 1;
		}
		if (ret == 0)
			ret = quotes_command_error(cmd, str);
	}
	return (ret);
}

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
