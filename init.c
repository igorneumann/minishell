/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narroyo- <narroyo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/19 18:22:06 by narroyo-          #+#    #+#             */
/*   Updated: 2021/09/19 20:15:07 by narroyo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reinitialize_variables(t_cmd *cmd)
{
	cmd->tmp_in = ft_strdup(cmd->in);
	free(cmd->buff);
	cmd->buff = ft_strdup(cmd->tmp_in);
	cmd->original = ft_strdup(cmd->in);
	cmd->check_replacement = check_replacement(cmd);
	if (cmd->check_replacement == -1)
		ft_putstr_fd("\r\nunexpected EOF while looking for matching\'\"", 2);
}

int	command_error(t_cmd *cmd)
{
	int		i;
	char	*error;

	i = 0;
	error = NULL;
	if (cmd->original[i] == '\'' || cmd->original[i] == '\"')
	{
		i++;
		while (cmd->original[i] && cmd->original[i] != '\''
			&& cmd->original[i] != '\"')
		{
			if (cmd->original[i] == ' ')
			{
				error = ft_strjoin(cmd->original, ": command not found\r\n");
				cmd->output_status = 127;
				ft_putstr_fd(error, 2);
				free(error);
				return (1);
			}
			i++;
		}
	}
	return (0);
}
