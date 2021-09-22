/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filename.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineumann <ineumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 17:27:21 by ineumann          #+#    #+#             */
/*   Updated: 2021/09/22 20:20:47 by ineumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*filename(char *str, int pos)
{
	int	sc;

	sc = countleft(str, pos, '\'', '\"');
	if (sc == 0 || sc % 2 == 0)
		return (ft_strduptochar(&str[pos], 32, '\0'));
	else
		return (parse_file_name(&str[pos], 32));
}
