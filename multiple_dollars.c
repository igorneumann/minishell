/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_dollars.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narroyo- <narroyo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 08:41:15 by narroyo-          #+#    #+#             */
/*   Updated: 2021/09/01 09:47:14 by narroyo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	change_dollar_value(t_cmd *cmd)
{
	char	*values;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	while (cmd->without_quotes[i])
	{

		i++;
	}
	values =
}

void	dollar_division(t_cmd *cmd)
{
	char	**dollars;
	char	**dollar;
	int		i;
	int		j;
	int		k;
	int		l;

	i = 0;
	dollars = ft_split(cmd->original, ' ');
	dollar = (char *)malloc(sizeof(char) * count_char(cmd->original, '$') + 1);
	while (dollars[i])
	{
		j = 0;
		while (dollars[i][j])
		{
			k = 0;
			if (dollars[i][j] == '$')
			{
				l = 0;
				while(dollars[i][j] && dollars[i][j] != ' '
					&& dollars[i][j] != '\'' && dollars[i][j] != '\"')
					dollar[k][l] = dollars[i][j++];
				dollar[k][l] = '\0';
				k++;
			}
			j++;
		}
		i++;
	}
}
