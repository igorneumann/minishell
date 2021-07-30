/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narroyo- <narroyo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/22 19:05:47 by narroyo-          #+#    #+#             */
/*   Updated: 2021/07/30 12:54:01 by narroyo-         ###   ########.fr       */
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

int	look_for_closure(char quote, char searching, char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == searching)
		{
			while (line[i])
			{
				if (line[i] == quote)
				{
					while (line[i])
					{
						if (line[i] == quote)
							return (1);
						i++;
					}
				}
				i--;
			}
		}
		i++;
	}
	return (0);
}

void	replace(t_cmd *cmd, int position, int old_len)
{
	int	counter;
	int	i;
	int	j;
	int	k;

	counter = 0;
	i = 0;
	j = 0;
	k = 0;
	position--;
	cmd->in = (char *)malloc(sizeof(char) * (ft_strlen(cmd->tmp_in)
		+ ft_strlen(cmd->dollar_value[position]) - (old_len + 1)) + 1);
	if (cmd->in == NULL)
		return ;
	while (cmd->tmp_in[k] && cmd->tmp_in[k] != '\0')
	{
		if (look_for_closure('\'', '$', cmd->tmp_in) == 0)
		{
			if (cmd->tmp_in[k] == '$')
			//	&& (look_for_closure('\"', '$', cmd->tmp_in) == 1)
			{
				if (counter == position)
				{
					while (cmd->dollar_value[position][j])
					{
						cmd->in[i] = cmd->dollar_value[position][j];
						j++;
						i++;
					}
					k += old_len + 1;
					counter++;
				}
			}

		}
		else if (cmd->tmp_in[k] && cmd->tmp_in[k] != '\0')
		{
			cmd->in[i] = cmd->tmp_in[k];
			k++;
			i++;
		}
	}
	cmd->in[i] = '\0';
}

int	dollar(t_cmd *cmd, int k)
{
	int		i;
	int		j;
	int		ch;
	char	*var;

	i = 0;
	j = 0;
	ch = 0;
	if (cmd->quote_s % 2 != 0)
		return (0);
	if (cmd->quote_s % 2 == 0)
	{
		while (cmd->tmp_in[i] != '$' && (cmd->tmp_in[i] != '\0' || cmd->tmp_in[i] != ' '))
		{
			if (cmd->tmp_in[i] == '\0')
				break ;
			i++;
		}
		i++;
		while (cmd->tmp_in[i + ch] != '\0' && cmd->tmp_in[i + ch] != ' ')
			ch++;
		var = (char *)malloc(sizeof(char) * ch + 1);
		while (cmd->tmp_in[i] && cmd->tmp_in[i] != ' ' && i < i + ch )
		{
			var[j] = cmd->tmp_in[i];
			i++;
			j++;
		}
		var[j] = '\0';
		cmd->dollar_value[k] = ft_strdup(search_value(var, cmd));
		free(var);
		k++;
	}
	replace(cmd, k, ch);
	return (k);
}

int	quotes(t_cmd *cmd)
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

int	count_char(char *line, char character)
{
	int	i;

	i = 0;
	while (*line)
	{
		if (*line == character)
			i++;
		line++;
	}
	return (i);
}

void	check_replacement(t_cmd *cmd)
{
	int	k;
	int	i;

	k = 0;
	i = 0;
	if (ft_strchr(cmd->in, '$') != NULL)
	{
		cmd->tmp_in = ft_strdup(cmd->in);
		cmd->dollar_value = (char **)malloc(sizeof(char *)
			* count_char(cmd->tmp_in, '$'));
		free(cmd->in);
	}
	while (cmd->tmp_in[i])
	{
		if (quotes(cmd) != 0 && cmd->tmp_in[i] == '$')
		{
			if (look_for_closure('\"', '$', cmd->tmp_in) == 1)
			{
				if (look_for_closure('\'', '$', cmd->tmp_in) == 1)
					i++;
				else
					k = dollar(cmd, k);
			}
		}
		else if (quotes(cmd) == 0 && cmd->tmp_in[i] == '$')
			k = dollar(cmd, k);
		i++;
	}
	if (ft_strchr(cmd->in, '$') != NULL)
		cmd->in = ft_strdup(cmd->tmp_in);
	free(cmd->tmp_in);
}
