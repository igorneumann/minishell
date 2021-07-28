/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narroyo- <narroyo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/22 19:05:47 by narroyo-          #+#    #+#             */
/*   Updated: 2021/07/28 17:19:33 by narroyo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*search_value(char *elem, t_cmd *cmd)
{
	elem++;
	while (ft_strcmp(elem, cmd->envp->key) != 0)
		cmd->envp = cmd->envp->next;
	if (cmd->envp->value != NULL && ft_strcmp(elem, cmd->envp->key) == 0)
		return (cmd->envp->value);
	return (NULL);
}

int	look_for_closure(char quote, char searching, char *line)
{
	while (*line)
	{
		if (*line == searching)
		{
			while (*line)
			{
				if (*line == quote)
				{
					while (*line)
					{
						if (*line == quote)
							return (1);
						line++;
					}
				}
				line--;
			}
		}
		line++;
	}
	return (0);
}

void	replace(t_cmd *cmd, int position, int old_len)
{
	int	new_len;
	int	diff;
	int	counter;

	counter = 0;
	position--;
	new_len = ft_strlen(cmd->dollar_value[position]);
	printf("%s\n", cmd->tmp_in);
	printf("%lu\n", ft_strlen(cmd->tmp_in) + new_len - old_len + 1);
	diff = ft_strlen(cmd->tmp_in) + new_len - (old_len + 1);
	cmd->in = (char *)malloc(sizeof(char) * diff + 1);
	if (cmd->in == NULL)
		return ;
	while (cmd->tmp_in != '\0')
	{
		if (*cmd->tmp_in == '$')
		{
			if (counter == position)
			{
				while (*cmd->dollar_value[position])
				{
					*cmd->in = *cmd->dollar_value[position];
					cmd->dollar_value[position]++;
					cmd->in++;
				}
				cmd->tmp_in++;
				counter++;
			}
		}
		else
		{
			*cmd->in = *cmd->tmp_in;
			cmd->tmp_in++;
			cmd->in++;
		}
	}
	*cmd->in = '\0';
}

int	dollar(t_cmd *cmd, int k)
{
	int		i;
	int		ch;
	char	*var;

	i = 0;
	ch = 0;
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
		var = ft_strdup(cmd->tmp_in);
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
}
