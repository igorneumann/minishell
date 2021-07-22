/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narroyo- <narroyo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/22 19:05:47 by narroyo-          #+#    #+#             */
/*   Updated: 2021/07/22 19:45:52 by narroyo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_dollar(t_cmd *cmd, char *in, int i)
{
	int		ch;
	char	*var;
	int		j;

	j = 0;
	if (!(cmd->quote_s % 2))
		return ;
	if (!(cmd->quote_d % 2))
	{
		while (*in != '\0' || *in != ' ')
		{
			ch++;
			in++;
		}
		var = (char *)malloc(sizeof(char) * ch + 1);
		while (in[i] != '\0' || in[i] != ' ')
			var[j++] = in[i++];
		printf("%s\r\n", var);
	}

}

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
		if (cmd->in[i] == '$')
			ft_dollar(cmd, &cmd->in, i);
		i++;
	}
}
