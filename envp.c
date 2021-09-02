/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narroyo- <narroyo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 18:52:33 by narroyo-          #+#    #+#             */
/*   Updated: 2021/09/02 13:52:23 by narroyo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_env(t_envp *x)
{
	while (x->prev)
		x = x->prev;
	while (x)
	{
		if (x->value == NULL || x->value[0] == '\0')
			x = x->next;
		else
		{
			printf("%s=%s\r\n", x->key, x->value);
			x = x->next;
		}
	}
}

char	*search_value(char *elem, t_cmd *cmd)
{
	if (ft_strnstr(elem, "?", 1))
		return (ft_itoa(cmd->output_status >> 8));
	while (cmd->envp->prev)
		cmd->envp = cmd->envp->prev;
	while (cmd->envp && ft_strcmp(elem, cmd->envp->key) != 0)
		cmd->envp = cmd->envp->next;
	if (cmd->envp && cmd->envp->value != NULL
		&& ft_strcmp(elem, cmd->envp->key) == 0)
		return (ft_strdup(cmd->envp->value));
	return (NULL);
}

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
