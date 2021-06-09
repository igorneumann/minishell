/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narroyo- <narroyo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 09:56:29 by narroyo-          #+#    #+#             */
/*   Updated: 2021/03/04 11:56:40 by narroyo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_errors(char *str, unsigned int i, int base_int)
{
	if (!str[i] || (base_int < 2 || base_int > 16))
		return (0);
	while (str[i] == '\n' || str[i] == ' ' || str[i] == '\t')
		i += 1;
	while (str[i] == '\r' || str[i] == '\v' || str[i] == '\f')
		i += 1;
	return (i);
}

static int	verify_base_nbr(char c, int base_int)
{
	if (base_int <= 10)
		return (c >= '0' && c <= '9');
	return ((c >= '0' && c <= '9') || (c >= 'A' && c <= ('A' + base_int - 10))
		|| (c >= 'a' && c <= ('a' + base_int - 10)));
}

int	ft_atoi_base(char *str, char *base)
{
	unsigned int	value;
	unsigned int	sign;
	unsigned int	i;
	int				base_int;

	value = 0;
	i = 0;
	sign = 1;
	base_int = ft_atoi(base);
	ft_errors(str, i, base_int);
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			sign *= -1;
	while (str[i] && verify_base_nbr(str[i], base_int))
	{
		if (str[i] >= 'A' && 'F' >= str[i])
			value = (value * base_int) + (str[i] - 'A' + 10);
		else if (str[i] >= 'a' && 'f' >= str[i])
			value = (value * base_int) + (str[i] - 'a' + 10);
		else
			value = (value * base_int) + (str[i] - '0');
		i += 1;
	}
	return (value * sign);
}
