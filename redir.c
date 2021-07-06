/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineumann <ineumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 17:27:21 by ineumann          #+#    #+#             */
/*   Updated: 2021/07/06 17:47:47 by ineumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redir(t_cmd *cmd)
{
	int		i;
	int		j;

	i = ft_strlen(cmd->in);
	while (i > 0)
	{
		j = 1;
		if (cmd->in[i] == '>')
		{
			cmd->in[i] = '\0';
			while (cmd->in[i + j] == ' ' || cmd->in[i + j] == '>')
				j++;
			cmd->outp = ft_strduptochar(&cmd->in[i + j], 32);
		}
		else if (cmd->in[i] == '<')
		{
			cmd->in[i] = '\0';
			while (cmd->in[i + j] == ' ' || cmd->in[i + j] == '<')
				j++;
			cmd->inpt = ft_strduptochar(&cmd->in[i + j], 32);
		}
		i--;
	}
	redirector(cmd);
	return (0);
}

void	redirector(t_cmd *cmd)
{
	if (cmd->inpt[0] != '\x0D')
		printf("Input is %s\r\n", cmd->inpt);
	if (cmd->outp[0] != '\x0D')
		printf("Output is %s\r\n", cmd->outp);
}
