/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_rawmode.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineumann <ineumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 17:43:45 by ineumann          #+#    #+#             */
/*   Updated: 2021/05/26 20:35:33 by ineumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

struct termios orig_termios;

void die(const char *s)
{
	editorRefreshScreen();
	perror(s);
	exit(1);
}

void editorRefreshScreen(void)
{
	write(STDOUT_FILENO, "\x1b[2J", 4);
	write(STDOUT_FILENO, "\x1b[H", 3);
}

void disableRawMode(void)
{
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios) == -1)
		die("tcsetattr");
}

void enableRawMode(void)
{
	struct	termios raw;

	if (tcgetattr(STDIN_FILENO, &orig_termios) == -1)
		die("tcgetattr");
	raw = orig_termios;
	atexit(disableRawMode);
	raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
	raw.c_oflag &= ~(OPOST);
	raw.c_cflag |= (CS8);
	raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
	raw.c_cc[VMIN] = 0;
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1)
		die("tcsetattr");
}

char f_raw(void)
{
	int		nread;
	char	c;

	enableRawMode();
	while ((nread = read(STDIN_FILENO, &c, 1)) != 1)
	{
		if (nread == -1 && errno != EAGAIN)
			die("read");
	}
	return (c);
}

void processkeypress(t_cmd *cmd)
{
	char c;

	c = f_raw();
	while (!iscntrl(c))
	{
	write(STDOUT_FILENO, &c, 1);
	cmd->in[cmd->i] = c;
	cmd->i++;
	c = '\0';
	}
	if (c == 4) // CTRL-D
	{
		if (cmd->i == 0)
		{
			write(STDOUT_FILENO, "\x1b[2J", 4);
			write(STDOUT_FILENO, "\x1b[H", 3);
			disableRawMode();
			exit(0);
		}
		else
			c = 13;
	}
	if (c == 13) // ENTER
	{
		printf("\r\n");
		ft_read_arguments(cmd);
		cmd->in[0] = 13;
		cmd->in[1] = '\0';
		cmd->i = 0;
	}
	else if (c == 127) //BACKSPACE
	{
		if (cmd->i > 0)
		{
			ft_putstr("\033[D \033[D");
			cmd->i--;
			cmd->in[cmd->i] = '\0';
		}
	}
	else if (c == '\x1b')
		ft_commands(cmd);
	else if (c != 0) //OTROS IMPRIME CODIGO EN PANTALLA
		printf("%d\r\n", c);
}

int ft_commands(t_cmd *cmd)
{
	char seq[3];

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
		//else //OTROS IMPRIME CODIGO EN PANTALLA
		//	printf("%s\r\n", seq);
	}
	return (0);
}
