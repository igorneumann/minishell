/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineumann <ineumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 18:38:34 by narroyo-          #+#    #+#             */
/*   Updated: 2021/06/23 20:04:15 by ineumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_include(t_cmd *cmd, char *aux)
{
	int	i;
	int	ok;

	i = 0;
	ok = 1;
	while (cmd->envp->next)
		cmd->envp = cmd->envp->next;
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
		free(aux);
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
		ft_sort_env(cmd);
	while (cmd->in[i] && bucle == 1)
		bucle = new_env_element(cmd, i);
}

void	ft_unset(t_cmd *cmd)
{
	int		i;
	int		j;
	char	*erase;

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
	cmd->envp = search_elem(cmd->envp, erase);
	cmd->envp = remove_elem(cmd->envp);
}
