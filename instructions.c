/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineumann <ineumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 10:28:08 by narroyo-          #+#    #+#             */
/*   Updated: 2021/05/27 18:26:24 by ineumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(char **envp)
{
	t_inst	inst;
	int		i;

	i = 0;
	if (envp != NULL)
	{
		while (envp[i])
		{
			inst.env[i] = ft_strdup(envp[i]);
			i++;
		}
	}
}
