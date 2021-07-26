/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moreprompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineumann <ineumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 18:01:37 by ineumann          #+#    #+#             */
/*   Updated: 2021/07/26 19:23:44 by ineumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_tab(t_cmd *cmd)
{
	char	c[6];
	int		i;

	i = 0;
	while (i < 5)
		c[i++] = ' ';
	c[i] = '\0';
	ft_putstr(c);
	cmd->in = ft_strjoin(cmd->in, c);
	cmd->i += 5;
}

void	promptin(int i)
{
	ft_putstr("\r\n\e[1;32m¿En qué puedo ayudarte?: \e[0m");
	i = 2;
}
