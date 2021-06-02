/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineumann <ineumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 17:26:29 by ineumann          #+#    #+#             */
/*   Updated: 2021/06/02 17:23:27 by ineumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_commands(t_cmd *cmd)
{
	char seq[4];

	seq[3] = '\0';
	if (read(STDIN_FILENO, &seq[0], 1) != 1)
		return '\x1b';
	if (seq[0] && read(STDIN_FILENO, &seq[1], 1) != 1)
		return '\x1b';
	if ((seq[1] >= '0' && seq[1] <= '9') && read(STDIN_FILENO, &seq[2], 1) != 1)
		return '\x1b';
	if (seq[2] == '~' || (seq[1] >= 'A' && seq[1] <= 'Z') )
	{
		if (seq[1] == 'D') //FLECHA IZQUIERDA
		{
			if (cmd->i > 0)
			{
				ft_putstr("\033[D");
				cmd->i--;
			}
			return (1);
		}
		else if (seq[1] == 'C') //FLECHA DERECHA
		{
			if (cmd->in[cmd->i] != '\0')
			{
				ft_putstr("\033[C");
				cmd->i++;
			}
			return (1);
		}
		else if (seq[1] == 'A' || seq[1] == 'B') //FLECHAS ABAJO / ARRIBA
			return(ft_history(cmd, seq));
		else if (seq[1] == '3') //DELETE
		{
			ft_putstr(" \033[J\033[D");
			cmd->in[cmd->i] = '\0';
			return (1);
		}
		else if (seq[1] == 'H' && cmd->i > 0) //HOME
		{
			while (--cmd->i >= 0)
				ft_putstr("\033[D");
			cmd->i = 0;
			return (1);
		}
		else if (seq[1] == 'F' && cmd->in[cmd->i] != '\0') //END
		{
			while (cmd->in[cmd->i] != '\0')
			{
				ft_putstr("\033[C");
				cmd->i++;
			}
			return (1);
		}
		else //OTROS IMPRIME CODIGO EN PANTALLA
			ft_putstr(seq);
	}
	return (0);
}

int		ft_history(t_cmd *cmd, char *seq)
{
	t_data	*first;

	if (cmd->list == NULL && seq)
		return(0);
	first = ft_lst_first(cmd->list); //APUNTA AL PRIMER ELEMENTO
	if (seq[1] == 'A' && ft_strcmp(cmd->in, first->in) != 0 && ft_strcmp(cmd->in, cmd->list->in) != 0) //ARRIBA Y DISTINTO DEL ULTIMO
		ft_lst_add_front(&cmd->list, ft_new(cmd->in));
	if (seq[1] == 'A' && cmd->list->next != NULL) //ARRIBA SI HAY SIGUIENTE
		cmd->list = cmd->list->next;
	else if (seq[1] == 'B' && cmd->list->prev != NULL) //ABAJO
		cmd->list = cmd->list->prev;
	while (cmd->i)
		ft_backspace(cmd);
	ft_dupin(cmd);
	cmd->i = ft_strlen(cmd->in);
	ft_putstr(cmd->in);
	return (1);
}

void		ft_dupin(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->list->in[i])
	{
		cmd->in[i] = cmd->list->in[i];
		i++;
	}
	cmd->in[i] = '\0';
}
