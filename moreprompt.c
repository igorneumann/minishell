/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moreprompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narroyo- <narroyo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 18:01:37 by ineumann          #+#    #+#             */
/*   Updated: 2021/09/19 17:01:03 by narroyo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_replacestr(char *in, char *new)
{
	char	*temp;

	temp = in;
	in = new;
	free(temp);
	return (in);
}

void	ft_tab(t_cmd *cmd)
{
	char	c[6];
	char	*temp;
	int		i;

	i = 0;
	while (i < 5)
		c[i++] = ' ';
	c[i] = '\0';
	ft_putstr(c);
	temp = cmd->in;
	cmd->in = ft_strjoin(cmd->in, c);
	free (temp);
	cmd->i += 5;
}

void	promptin(int i)
{
	g_reset = i;
	ft_putstr("\n\r");
}

void	do_nothing(int i)
{
	int	j;

	j = i;
}
