/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narroyo- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 11:18:57 by narroyo-          #+#    #+#             */
/*   Updated: 2019/11/13 10:28:30 by narroyo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	unsigned int	i;

	i = 0;
	if (dest != '\0' || src != '\0')
	{
		if (((unsigned char *)src) < ((unsigned char *)dest))
			while (len-- > 0)
				((unsigned char *)dest)[len] = ((unsigned char *)src)[len];
		else
			while (i < len)
			{
				((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
				i++;
			}
		return ((unsigned char *)dest);
	}
	else
		return (NULL);
}
