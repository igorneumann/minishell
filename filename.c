/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filename.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineumann <ineumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 17:27:21 by ineumann          #+#    #+#             */
/*   Updated: 2021/09/28 17:45:03 by ineumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*filename(char *oldstr, char *str, int pos)
{
	int	sc;

	free(oldstr);
	sc = countleft(str, pos, '\'', '\"');
	if (sc == 0 || sc % 2 == 0)
		return (ft_strduptochar(&str[pos], 32, '\0'));
	else
		return (parse_file_name(&str[pos - 1], 32));
}
