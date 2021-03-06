/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narroyo- <narroyo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 10:28:08 by narroyo-          #+#    #+#             */
/*   Updated: 2021/08/31 10:48:09 by narroyo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_options(t_cmd *cmd, int i)
{
	i++;
	if (cmd->in[i] == 'i' && cmd->in[i + 1] && cmd->in[i + 1] == 'v')
		ft_putstr("#env clearing environ\r\n");
	else
	{
		if (cmd->in[i] == 'i' && cmd->in[i + 1] == '\0')
			cmd->in[i] = '\0';
		else
		{
			if (cmd->in[i] == 'i')
				i++;
			printf("env: illegal option -- %c\r\n", cmd->in[i]);
			ft_putstr("usage: env [-iv] [-P utilpath] [-S string]");
			ft_putstr(" [-u name]\r\n           [name=value ...]");
			ft_putstr(" [utility [argument ...]]\r\n");
		}
	}
}

void	error_file_or_directory(t_cmd *cmd, int i)
{
	char	*fod;
	char	*error;
	int		j;

	j = 0;
	fod = (char *)malloc(sizeof(char) * (ft_strlen(cmd->in) - i + 1));
	while (cmd->in[i] != '\0')
		fod[j++] = cmd->in[i++];
	error = ft_strjoin("env: ", fod);
	free(fod);
	fod = ft_strjoin(error, ": No such file or directory\r\n");
	if (fod)
	{
		ft_putstr_fd(fod, 2);
		free(fod);
	}
}

void	ft_env(t_cmd *cmd)
{
	int		i;

	i = 3;
	cmd->not_found = 1;
	if (command_not_found("env", cmd))
		return ;
	while (cmd->in[i] == ' ')
		i++;
	if (cmd->in[i] == 'e')
		i += 3;
	if (cmd->in[i] == '\0')
		ft_print_env(cmd->envp);
	if (cmd->in[i] == '-')
		ft_options(cmd, i);
	else if (cmd->in[i] != '-' && cmd->in[i] != '\0')
		error_file_or_directory(cmd, i);
	free(cmd->in);
	cmd->in = ft_strdup("\x0D");
}
