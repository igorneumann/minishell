/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_rawmode.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineumann <ineumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 17:43:45 by ineumann          #+#    #+#             */
/*   Updated: 2021/05/26 17:28:43 by ineumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

struct termios orig_termios;

void die(const char *s) {
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
	cmd->in[cmd->i] = '\0';
	c = '\0';
	}
	if (c == 26) // CTRL-Z
	{
		write(STDOUT_FILENO, "\x1b[2J", 4);
		write(STDOUT_FILENO, "\x1b[H", 3);
		disableRawMode();
		exit(0);
	}
	if (c == 13) // ENTER
	{
		printf("\r\n");
		ft_read_arguments(cmd);
		cmd->i = 0;
	}
	else if (c == 127) //BACKSPACE
	{
		printf("\033[1D ");
		cmd->i--;
		cmd->in[cmd->i] = '\0';
	}
	else if (c != 0) //OTROS IMPRIME CODIGO EN PANTALLA
		printf("%d\r\n", c);
}
