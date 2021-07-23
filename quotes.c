/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narroyo- <narroyo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/22 19:05:47 by narroyo-          #+#    #+#             */
/*   Updated: 2021/07/23 17:03:20 by narroyo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*search_value(char *elem, t_cmd *cmd)
{
	while (ft_strcmp(elem, cmd->envp->key) != 0)
		cmd->envp = cmd->envp->next;
	if (cmd->envp->value != NULL && ft_strcmp(elem, cmd->envp->key) == 0)
		return (cmd->envp->value);
	return (NULL);
}

int	ft_dollar(t_cmd *cmd, int i, int k)
{
	int		ch;
	char	*var;

	ch = 0;
	cmd->dollar_value = (char **)malloc(sizeof(char *) * 5);
	if (cmd->quote_s % 2 != 0)
		return (0);
	if (cmd->quote_s % 2 == 0)
	{
		while (cmd->in[i] != '\0' || cmd->in[i] != ' ')
		{
			if (cmd->in[i] == '\0')
				break ;
			ch++;
			i++;
		}
		i -= ch;
		var = ft_strdup(cmd->in + i + 1);
		var[ch - 1] = '\0';
		cmd->dollar_value[k] = ft_strdup(search_value(var, cmd));
		free(var);
		k++;
	}
	return (k);
}

void	ft_quotes(t_cmd *cmd)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (cmd->in[i] != 0)
	{
		if (cmd->in[i] == '\'')
		{
			cmd->quote_s++;
			i++;
		}
		if (cmd->in[i] == '\"')
		{
			cmd->quote_d++;
			i++;
		}
		if (cmd->in[i] == '$')
			k++;
		i++;
	}
}
