/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narroyo- <narroyo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 17:50:10 by narroyo-          #+#    #+#             */
/*   Updated: 2021/10/04 19:22:52 by narroyo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_redirections(t_cmd *cmd, int k, int j)
{
	if (cmd->original[k] == '>')
	{
		cmd->redpip = countleft(cmd->original, k, '|', '\0') + 1;
		cmd->outp = filename(cmd->outp, cmd->original, (k + j));
	}
	if (cmd->original[k] == '<')
		cmd->inpt = filename(cmd->inpt, cmd->original, (k + j));
}

int	comillas(char *str, int position)
{
	while (str[position])
	{
		if (look_for_closure('\'', str[position], str, position) == 1
			|| look_for_closure('\"', str[position], str, position) == 1)
			return (1);
		position++;
	}
	return (0);
}

char	*create_array(char *str, int position)
{
	char	*dest;
	int		size;

	size = 0;
	while (str[position + size]
		&& countleft(str, position + size, '\'', '\"') % 2 != 0)
		size++;
	dest = (char *)malloc(sizeof(char) * (size + 1));
	if (!dest)
		return (NULL);
	ft_bzero(dest, size);
	return (dest);
}

char	*parse_file_name(char *s1, char c)
{
	char	*dest;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (s1[i] != '\'' && s1[i] != '\"')
		i++;
	i++;
	dest = create_array(s1, i);
	while (s1[i] && (((look_for_closure('\"', s1[i], (char *)s1, i) == 0
					&& s1[i] != c) || (look_for_closure('\'', s1[i],
						(char *)s1, i) == 0 && s1[i] != c)) || s1[i] != '\0'))
	{
		if (s1[i] != '\"' && s1[i] != '\'')
			dest[j++] = s1[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
