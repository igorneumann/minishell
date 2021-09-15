/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineumann <ineumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 18:13:10 by narroyo-          #+#    #+#             */
/*   Updated: 2021/09/15 16:46:15 by ineumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cleanfds(t_cmd *cmd, int i, int red)
{
	unlink(".tempAF.tmp");
	if (red)
	{
		if ((i == 1 || i == 3) && cmd->in_fd > 0)
			close(cmd->in_fd);
		if ((i == 2 || i == 3) && cmd->out_fd > 0)
			close(cmd->out_fd);
	}
	return (1);
}

void	cleanspcback(char *str, int k)
{
	int	i;

	i = 1;
	while (str[k - i] == 32)
	{
		str[k - i] = '\0';
		i++;
	}
}
