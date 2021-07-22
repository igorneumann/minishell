/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narroyo- <narroyo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/22 19:05:47 by narroyo-          #+#    #+#             */
/*   Updated: 2021/07/22 20:40:34 by narroyo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_dollar(t_cmd *cmd, int i)
{
	int		ch;
	char	*var;
	int		j;

	j = 0;
	ch = 0;
//	if (!(cmd->quote_s % 2))
//		return ;
//	if (!(cmd->quote_d % 2) || cmd->quote_d == 0 || cmd->quote_s == 0)
//	{
		while (cmd->in[i] != 0 || cmd->in[i] != ' ')
		{
			if (cmd->in[i] == '\0')
				break ;
			ch++;
			i++;
			printf("%c\r\n", cmd->in[i]);
			printf("CACA\r\n");
		}
		i -= ch;
		var = (char *)malloc(sizeof(char) * ch + 1);
		while (cmd->in[i] != '\0' || cmd->in[i] != ' ')
		{
			var[j] = cmd->in[i];
			j++;
			i++;
			printf("CLOACA\r\n");
		}
		var[j] = '\0';
		printf("%s JeJe\r\n", var);
//	}

}

void	ft_quotes(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->in[i] != '\0')
	{
		/*if (cmd->in[i] == '\'')
			cmd->quote_s++;
		if (cmd->in[i] == '\"')
			cmd->quote_d++;*/
		if (cmd->in[i] == '$')
			ft_dollar(cmd, i);
		i++;
	}
}
