/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filename.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineumann <ineumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 17:27:21 by ineumann          #+#    #+#             */
/*   Updated: 2021/10/01 20:35:18 by ineumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*filename(char *oldstr, char *str, int pos)
{
	int	sc;
	int	sc2;

	while (str[pos] == '\"' || str[pos] == '\'')
		pos++;
	free(oldstr);
	sc = countleft(str, pos, '\'', '\0');
	sc2 = countleft(str, pos, '\0', '\"');
	if (sc % 2 == 0 && sc2 % 2 == 0)
		return (ft_strduptochar(&str[pos], 32, '\0'));
	else
		return (parse_file_name(&str[pos], str[pos - 1]));
}
