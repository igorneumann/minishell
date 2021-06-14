/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narroyo- <narroyo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 11:18:57 by narroyo-          #+#    #+#             */
/*   Updated: 2021/03/05 09:51:24 by narroyo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	unsigned int	i;

	i = 0;
	if (dest != (void *)0 || src != (void *)0)
	{
		if (((unsigned char *)src) < ((unsigned char *)dest))
			while (len-- > 0)
				((unsigned char *)dest)[len] = ((unsigned char *)src)[len];
		else
		{
			while (i < len)
			{
				((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
				i++;
			}
		}
		return ((unsigned char *)dest);
	}
	else
		return (NULL);
}
