/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineumann <ineumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 18:38:34 by narroyo-          #+#    #+#             */
/*   Updated: 2021/09/10 20:58:13 by ineumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_existence(t_cmd *cmd, char *aux, int i)
{
	int		n;
	char	*key;

	n = -1;
	key = (char *)malloc(sizeof(char) * i + 1);
	while (++n < i)
		key[n] = aux[n];
	key[n] = '\0';
	while (cmd->envp->prev)
		cmd->envp = cmd->envp->prev;
	while (cmd->envp)
	{
		if (ft_strcmp(cmd->envp->key, key) == 0)
		{
			cmd->envp = change_value(cmd->envp, &aux[i + 1]);
			free(key);
			return (0);
		}
		else if (cmd->envp->next)
			cmd->envp = cmd->envp->next;
		else
			break ;
	}
	free(key);
	return (1);
}

void	ft_include(t_cmd *cmd, char *aux)
{
	int		i;
	int		ok;

	i = 0;
	ok = 1;
	if (!ft_isalpha(aux[0]))
	{
		printf("bash: export: `%s': not a valid identifier\r\n", aux);
		ok = 0;
		return ;
	}
	while (aux[i] && aux[i] != '=')
	{
		if (!ft_isalnum(aux[i]))
		{
			printf("bash: export: `%c': not a valid identifier\r\n", aux[i]);
			ok = 0;
			return ;
		}
		i++;
	}
	ok = check_existence(cmd, aux, i);
	if (ok == 1)
		ft_lst_add_back((t_data **)&cmd->envp, (t_data *)ft_new_env(aux));
}

int	new_env_element(t_cmd *cmd, int i)
{
	char	**aux;
	int		j;

	j = 0;
	while (cmd->in[i] == ' ' || cmd->in[i] == '\'')
		i++;
	if (cmd->in[i] != ' ')
	{
		aux = ft_split(cmd->in + i, ' ');
		while (aux[j])
		{
			ft_include(cmd, aux[j]);
			j++;
		}
		free_split(aux);
		return (0);
	}
	return (1);
}

void	ft_export(t_cmd *cmd)
{
	int		i;
	int		bucle;

	i = 0;
	bucle = 1;
	cmd->not_found = 1;
	if (command_not_found("export", cmd))
		return ;
	i += 6;
	if (cmd->in[i] == '\0')
		ft_sort_env(cmd->envp, NULL, NULL, 1);
	while (cmd->in[i] != '\0' && bucle == 1)
		bucle = new_env_element(cmd, i);
	//envp_to_arr(cmd, 0);
}

void	ft_unset(t_cmd *cmd)
{
	int		i;
	int		j;
	char	*erase;
	t_envp	*env;

	i = 0;
	j = 0;
	cmd->not_found = 1;
	if (command_not_found("unset", cmd))
		return ;
	i += 6;
	erase = (char *)malloc(sizeof(char) * (ft_strlen(cmd->in) - i + 1));
	while (cmd->in[i] != '\0')
		erase[j++] = cmd->in[i++];
	erase[j] = '\0';
	env = search_elem(cmd->envp, erase);
	if (env)
		cmd->envp = env;
	else
	{
		free(erase);
		return ;
	}
	cmd->envp = remove_elem(cmd->envp);
	free(erase);
}
