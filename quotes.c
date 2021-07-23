/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narroyo- <narroyo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/22 19:05:47 by narroyo-          #+#    #+#             */
/*   Updated: 2021/07/23 19:14:31 by narroyo-         ###   ########.fr       */
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
		while (cmd->tmp_in[i] != '\0' || cmd->tmp_in[i] != ' ')
		{
			if (cmd->tmp_in[i] == '\0')
				break ;
			ch++;
			i++;
		}
		i -= ch;
		var = ft_strdup(cmd->tmp_in + i + 1);
		var[ch - 1] = '\0';
		cmd->dollar_value[k] = ft_strdup(search_value(var, cmd));
		free(var);
		k++;
	}
	return (k);
}

int	ft_quotes(t_cmd *cmd)
{
	int	i;

	i = 0;
	if (cmd->tmp_in[i] == '\'')
	{
		cmd->quote_s++;
		i++;
	}
	if (cmd->tmp_in[i] == '\"')
	{
		cmd->quote_d++;
		i++;
	}
	return (i);
}

void	ft_replace(t_cmd *cmd)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	k = 0;
	cmd->tmp_in = ft_strdup(cmd->in);
	free(cmd->in);
	while (cmd->tmp_in[i] != 0)
	{
		j = 1;
		if (cmd->tmp_in[i] == ' ')
			i++;
		ft_quotes(cmd);
		if (cmd->tmp_in[i] == '$')
		{
			k = ft_dollar(cmd, i, k);
			if (cmd->quote_s % 2 == 0 && cmd->quote_s != 0)
			{
				while (cmd->tmp_in[i] != '\0' || cmd->tmp_in[i] != ' ')
					j++;

			}

		}
	}
	cmd->in = ft_strdup(cmd->tmp_in);
}
