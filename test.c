/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineumann <ineumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 18:10:44 by ineumann          #+#    #+#             */
/*   Updated: 2021/06/18 20:15:06 by ineumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	main(int argc, char **argv)
{
	int	i;

	i = 0;
	printf ("Hello World\r\n\r\nARGC IS %i\r\n", argc);
	while (i < argc)
	{
		printf("ARGV[%i] is %s\r\n", i, argv[i]);
		i++;
	}
	return (0);
}
