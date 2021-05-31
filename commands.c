/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineumann <ineumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 17:26:29 by ineumann          #+#    #+#             */
/*   Updated: 2021/05/31 21:06:06 by ineumann         ###   ########.fr       */
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
		if (seq[1] == 'D' && cmd->i > 0) //FLECHA IZQUIERDA
		{
			ft_putstr("\033[D");
			cmd->i--;
			return (1);
		}
		else if (seq[1] == 'C' && cmd->in[cmd->i] != '\0') //FLECHA DERECHA
		{
			ft_putstr("\033[C");
			cmd->i++;
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
			while (cmd->i)
				ft_backspace(cmd);
//			if (seq[1] == 'A' && ft_strlen(cmd->in) > 0) //ARRIBA CON ALGO EN LINEA DE COMANDO
//			{
//				cmd->list = ft_lst_first(cmd->list);
//				ft_lst_add_front(&cmd->list, ft_new(cmd->in));
//			}
			if (seq[1] == 'B' && cmd->list->prev != NULL) //ABAJO
				cmd->list = cmd->list->prev;
			cmd->i = ft_strlen(cmd->list->in);
            ft_putstr(cmd->list->in);
//			cmd->in = cmd->list->in;
			if (seq[1] == 'A' && cmd->list->next != NULL) //ARRIBA SI HAY SIGUIENTE
				cmd->list = cmd->list->next;
			return (1);
}