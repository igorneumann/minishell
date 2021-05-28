/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narroyo- <narroyo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 13:44:06 by narroyo-          #+#    #+#             */
/*   Updated: 2020/12/18 10:03:45 by narroyo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	ft_whiles(char *str, char const *s1, char const *s2)
{
	int	i;
	int	l;

	i = 0;
	l = 0;
	while (s1[l])
	{
		str[l] = s1[l];
		l++;
	}
	while (s2[i])
	{
		str[l] = s2[i];
		i++;
		l++;
	}
	str[l] = '\0';
	return (*str);
}

char		*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;

	if (!s1 || !s2)
		return (NULL);
	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (str != '\0')
	{
		ft_whiles(str, s1, s2);
	}
	else
		return (0);
	return (str);
}
