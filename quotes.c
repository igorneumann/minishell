/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narroyo- <narroyo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/22 19:05:47 by narroyo-          #+#    #+#             */
/*   Updated: 2021/07/22 19:15:23 by narroyo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_quotes(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->in[i] != '\0')
	{
		if (cmd->in[i] == '\'')
			cmd->quote_s++;
		if (cmd->in[i] == '\"')
			cmd->quote_d++;
		i++;
	}
	i = 0;
	if (cmd->quote_s % 2)
		cmd->quotes = 0;
}
