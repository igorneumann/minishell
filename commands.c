/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineumann <ineumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 17:26:29 by ineumann          #+#    #+#             */
/*   Updated: 2021/06/03 19:16:16 by ineumann         ###   ########.fr       */
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
	t_data *first;

	if (cmd->list == NULL && seq)
		return(0);
	if (seq[1] == 'B' && cmd->buff[0] == 13)
		return(0);
	if (ft_strcmp(cmd->buff, cmd->list->in) != 0 && cmd->buff[0] != 13)
		ft_lst_edit(&cmd->list, ft_new(cmd->in)); //ACTUALIZA ITEM
	first = ft_lst_first(cmd->list); //APUNTA AL PRIMER ELEMENTO
	if (seq[1] == 'A' && (cmd->in[0] == '\0' || (ft_strcmp(cmd->in, cmd->list->in) != 0 && ft_strcmp(cmd->in, cmd->buff) != 0))) //ARRIBA Y DISTINTO DEL ULTIMO
		ft_dupin(cmd, 2);
	else if (seq[1] == 'A' && cmd->list->next != NULL) //ARRIBA SI HAY SIGUIENTE
		cmd->list = cmd->list->next;
	else if (seq[1] == 'B' && cmd->list->prev != NULL) //ABAJO
		cmd->list = cmd->list->prev;
	if (seq[1] == 'B' && cmd->list->prev == NULL && ft_strcmp(cmd->in, first->in) == 0)
	{
		while (cmd->i)
			ft_backspace(cmd);
		ft_dupin(cmd, 0);
	}
	else
	{
		while (cmd->i)
			ft_backspace(cmd);
		ft_dupin(cmd, 1);
	}
	cmd->i = ft_strlen(cmd->in);
	ft_putstr(cmd->in);
	return (1);
}

void		ft_dupin(t_cmd *cmd, int src) //0 buffer, 1 historial, 2 guarda en buffer
{
	int	i;

	i = 0;
	if (src == 2)
	{
		while (cmd->in[i])
		{
			cmd->buff[i] = cmd->in[i];
			i++;
		}
		cmd->buff[i] = '\0';
	}
	if (src == 1)
	{
		while (cmd->list->in[i])
		{
			cmd->in[i] = cmd->list->in[i];
			i++;
		}
		cmd->in[i] = '\0';
	}
	else if (src == 0)
	{
		while (cmd->list->in[i])
		{
			cmd->in[i] = cmd->buff[i];
			i++;
		}
		cmd->in[i] = '\0';
		cmd->buff[0] = 13;
	}
}
