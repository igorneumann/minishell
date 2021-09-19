/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narroyo- <narroyo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 09:13:20 by narroyo-          #+#    #+#             */
/*   Updated: 2021/09/19 17:03:02 by narroyo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	home_cd(t_cmd *cmd)
{
	char	*in;
	char	*home;

	if (ft_strlen(cmd->in) == 2)
	{
		home = search_value("HOME", cmd);
		in = ft_strjoin("cd ", home);
		cmd->in = ft_replacestr(cmd->in, in);
		free(home);
	}
}

void	save_path(t_cmd *cmd, int i)
{
	int	j;
	int	k;

	j = 0;
	k = i;
	while (cmd->in[k] != '\0' && cmd->in[k] != ' ')
		k++;
	cmd->relative_path = (char *)malloc(sizeof(char) * 2048 + 1);
	while (cmd->in[i] != '\0' && cmd->in[i] != ' ')
		cmd->relative_path[j++] = cmd->in[i++];
	cmd->relative_path[j] = '\0';
}

void	previous_folder(t_cmd *cmd)
{
	int	j;

	j = ft_strlen(cmd->old_path);
	if (ft_strnstr(cmd->relative_path, "..", 2) != NULL)
	{
		if (cmd->old_path[j] == '/')
			cmd->old_path[j--] = '\0';
		while (cmd->old_path[j] != '/')
			cmd->old_path[j--] = '\0';
	}
}

void	ft_cd(t_cmd *cmd, int i)
{
	cmd->old_path = (char *)malloc(sizeof(char) * 2048 + 1);
	if (ft_strnstr(cmd->in, "cd", 2) != NULL)
	{
		cmd->not_found = 1;
		if (command_not_found("cd", cmd))
			return ;
		getcwd(cmd->old_path, 2048);
		i += 2;
		if (cmd->in[i] == '\0')
			return ;
		else
			i++;
		save_path(cmd, i);
		previous_folder(cmd);
		if (chdir(cmd->relative_path) != 0)
			printf("%s\r\n", strerror(errno));
		else
			getcwd(cmd->relative_path, 2048);
	}
	if (cmd->relative_path)
		free(cmd->relative_path);
	if (cmd->old_path)
		free(cmd->old_path);
}
