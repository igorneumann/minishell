/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ltoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narroyo- <narroyo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 13:04:49 by narroyo-          #+#    #+#             */
/*   Updated: 2021/03/15 09:55:59 by narroyo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

static char	*ft_convert(long nbr, char *str, int len)
{
	while (nbr > 0)
	{
		*(str + len--) = nbr % 10 + '0';
		nbr /= 10;
	}
	if (len == 0 && str[1] == '\0')
		*(str + len) = '0';
	if (len == 0 && str[1] != '\0')
		*(str + len) = '-';
	return (str);
}

char	*ft_ltoa(long int n)
{
	long	nbr;
	int		len;
	char	*str;

	nbr = n;
	if (nbr > 0)
		len = 0;
	else
	{
		len = 1;
		nbr = -nbr;
	}
	while (n)
	{
		if (n == len++)
			n /= 10;
		else
			n /= 10;
	}
	str = (char *)malloc(sizeof(char) * len + 1);
	if (!str)
		return (NULL);
	*(str + len--) = '\0';
	ft_convert(nbr, str, len);
	return (str);
}
