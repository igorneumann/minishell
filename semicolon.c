/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semicolon.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineumann <ineumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 18:24:59 by ineumann          #+#    #+#             */
/*   Updated: 2021/06/11 17:26:43 by ineumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_semicolon(t_cmd *cmd)
{
	int		i;
	int		j;

	i = ft_strlen(cmd->in);
	j = 1;
	while (i > 0)
	{
		if ((cmd->in[i] == '&' && cmd->in[i + j] == '&') || cmd->in[i] == ';')
		{
			cmd->in[i] = '\0';
			if (cmd->in[i + j] == '&')
				cmd->in[i + j++] = '\0';
			while (cmd->in[i + j] == ' ')
				j++;
			ft_lst_add_front(&cmd->nexcom, ft_new(&cmd->in[i + j]));
		}
		j = 1;
		i--;
	}
}
