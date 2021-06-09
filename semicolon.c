/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semicolon.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineumann <ineumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 18:24:59 by ineumann          #+#    #+#             */
/*   Updated: 2021/06/09 19:53:37 by ineumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_semicolon(t_cmd *cmd)
{
	int		i;

	i = ft_strlen(cmd->in);
	while (i > 0)
	{
		if (cmd->in[i] == ';')
		{
			ft_lst_add_front(&cmd->nexcom, ft_new(&cmd->in[i + 1]));
			cmd->in[i] = '\0';
		}
		i--;
	}
}
