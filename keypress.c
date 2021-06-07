/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narroyo- <narroyo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 17:21:07 by ineumann          #+#    #+#             */
/*   Updated: 2021/06/07 18:47:19 by narroyo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void processkeypress(t_cmd *cmd)
{
	char	c;
	//char	*tmp;

	c = f_raw(cmd->raw);
	while (!iscntrl(c))
	{
	write(STDOUT_FILENO, &c, 1);
	if (cmd->in[cmd->i] == '\0')
		cmd->in[cmd->i + 1] = '\0';
	cmd->in[cmd->i++] = c;
	c = '\0';
	}
	/*while (!iscntrl(c))
	{
	write(STDOUT_FILENO, &c, 1);
	tmp = cmd->in;
	cmd->in = ft_strjoin(cmd->in, &c);
	c = '\0';
	free(tmp);
	}*/
	if (c == '\x1b')
		ft_commands(cmd);
//	else if (c == 4) // CTRL-D
//	{
//		if (cmd->i == 0)
//		{
//			write(STDOUT_FILENO, "\x1b[2J", 4);
//			write(STDOUT_FILENO, "\x1b[H", 3);
//			die(0, cmd->raw);
//		}
//	}
	else if (c == 13) // ENTER
	{
		printf("\r\n");
		if (ft_strlen(cmd->in) > 0)
			ft_read_arguments(cmd);
		cmd->in[0] = 13;
		cmd->buff[0] = 13;
		cmd->in[1] = '\0';
		cmd->buff[1] = '\0';
		cmd->i = 0;
	//	ft_printlist(cmd->list, cmd->buff);
	}
	else if (c == 127) //BACKSPACE
		ft_backspace(cmd);
	else if (c != 0) //OTROS IMPRIME CODIGO EN PANTALLA
		printf("%d\r\n", c);
}

void	ft_backspace(t_cmd *cmd)
{
	int i;

	i = 0;
	if (cmd->i > 0)
	{
		ft_putstr("\033[D \033[D");
		cmd->i--;
		while (cmd->in[cmd->i + i + 1] != '\0')
		{
			cmd->in[cmd->i + i] = cmd->in[cmd->i + i + 1];
			i++;
		}
		cmd->in[cmd->i + i] = '\0';
		ft_putstr(&cmd->in[cmd->i]);
		ft_putstr(" \033[D");
		while (i-- > 0)
			ft_putstr("\033[D");
	}
}
