/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narroyo- <narroyo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 17:50:10 by narroyo-          #+#    #+#             */
/*   Updated: 2021/10/04 18:38:06 by narroyo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_redirections(t_cmd *cmd, int k, int j)
{
	if (cmd->original[k] == '>')
	{
		cmd->redpip = countleft(cmd->original, k, '|', '\0') + 1;
		cmd->outp = filename(cmd->outp, cmd->original, (k + j));
	}
	if (cmd->original[k] == '<')
		cmd->inpt = filename(cmd->inpt, cmd->original, (k + j));
}

int	comillas(char *str, int position)
{
	while (str[position])
	{
		if (look_for_closure('\'', str[position], str, position) == 1
			|| look_for_closure('\"', str[position], str, position) == 1)
			return (1);
		position++;
	}
	return (0);
}
