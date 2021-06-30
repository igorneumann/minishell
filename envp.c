/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineumann <ineumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 18:52:33 by narroyo-          #+#    #+#             */
/*   Updated: 2021/06/29 17:52:10 by ineumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_envp	*ft_new_env_value(char *in, t_envp	*new, int i)
{
	int	j;

	j = 0;
	if (in[i] == '\0')
	{
		new->value = NULL;
		return (new);
	}
	if (in[i++] == '\0')
	{
		new->value = NULL;
		return (new);
	}
	new->value = (char *)malloc(sizeof(char) * (ft_strlen(in) - i + 1));
	while (in[i])
	{
		new->value[j] = in[i];
		i++;
		j++;
	}
	new->value[j] = '\0';
	new->next = NULL;
	return (new);
}

t_envp	*ft_new_env(char *in)
{
	t_envp	*new;
	int		i;

	i = 0;
	new = (t_envp *)calloc(1, sizeof(t_envp));
	if (ft_strchr(in, '='))
		new->key = (char *)malloc(sizeof(char) * (ft_strchr(in, '=') - in + 1));
	else
		new->key = (char *)malloc(sizeof(char) * (ft_strlen(in) + 1));
	if (!new)
		return (NULL);
	new->prev = NULL;
	while (in[i])
	{
		if (in[i] == '=')
			break ;
		new->key[i] = in[i];
		i++;
	}
	new->key[i] = '\0';
	new = ft_new_env_value(in, new, i);
	return (new);
}

void	ft_save_env(t_cmd *cmd, char **envp)
{
	int	i;

	i = 0;
	if (envp != NULL)
	{
		cmd->envorg = envp;
		while (envp[i])
			i++;
		i = 0;
		while (envp[i])
		{
			ft_lst_add_back((t_data **)&cmd->envp,
				(t_data *)ft_new_env(envp[i]));
			i++;
		}
	}
}
