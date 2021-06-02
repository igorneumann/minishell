/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narroyo- <narroyo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 10:28:08 by narroyo-          #+#    #+#             */
/*   Updated: 2021/06/02 10:45:19 by narroyo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_envp	*ft_new_env(char *in)
{
	t_envp	*new;
	int		i;
	int		j;

	i = 0;
	new = (t_envp *)calloc(1, sizeof(t_envp));
	new->key = (char *)malloc(sizeof(char) * (ft_strchr(in, '=') - in + 1));
	if (!new)
		return (NULL);
	new->prev = NULL;
	while (in[i] != '=')
	{
		new->key[i] = in[i];
		i++;
	}
	new->key[i] = '\0';
	i++;
	new->value = (char *)malloc(sizeof(char) * (ft_strlen(in) - i + 1));
	j = 0;
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

void	ft_save_env(t_cmd *cmd, char **envp)
{
	int	i;

	i = 0;
	if (envp != NULL)
	{
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

void	ft_env(t_cmd *cmd)
{
	int		i;
	int		j;
	char	*fod;

	i = 3;
	j = 0;
	fod = (char *)malloc(sizeof(char) * (ft_strlen(cmd->in) - i + 1));
	if (ft_strnstr(cmd->in, "env", 3))
	{
		while (cmd->in[i] == ' ')
			i++;
		if (cmd->in[i] == 'e')
			i += 3;	
		if (cmd->in[i] == '-')
		{
			if (cmd->in[++i] == 'i' && cmd->in[++i] == 'v')
				ft_putstr("#env clearing environ\r\n");
			else
			{
				printf("env: illegal option -- %c\r\n", cmd->in[++i]);
				ft_putstr("usage: env [-iv] [-P utilpath] [-S string] [-u name]\r\n");
				ft_putstr("           [name=value ...] [utility [argument ...]]\r\n");
			}
		}
		if (cmd->in[i] != '-' && cmd->in[i] != '\0')
		{
			while (cmd->in[i] != '\0')
			{
				fod[j] = cmd->in[i];
				i++;
				j++;
			}
			printf("env: %s: No such file or directory\r\n", fod);
		}
		else
			ft_print_env(cmd->envp);
	}
}
