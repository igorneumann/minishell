/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narroyo- <narroyo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 13:43:51 by narroyo-          #+#    #+#             */
/*   Updated: 2021/03/07 10:59:01 by narroyo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	unsigned long long	value;
	unsigned long long	i;
	long long			sign;

	value = 0;
	i = 0;
	sign = 1;
	if (!str[i])
		return (0);
	while ((str[i] == '\n' || str[i] == ' ' || str[i] == '\t' || str[i] == '\r')
		|| (str[i] == '\v' || str[i] == '\f'))
		i += 1;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			sign = -1;
	while (str[i] >= '0' && str[i] <= '9')
		value = (value * 10) + (str[i++] - '0');
	if (((value * sign) - 1 < 9223372036854775807) && sign == -1)
		return (0);
	if (((value * sign) > 9223372036854775807) && sign == 1)
		return (-1);
	return (value * sign);
}
