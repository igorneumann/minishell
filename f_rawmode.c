/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_rawmode.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineumann <ineumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 17:43:45 by ineumann          #+#    #+#             */
/*   Updated: 2021/05/31 19:46:05 by ineumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

struct termios orig_termios;

void die(const char *s)
{
	int error;

	error = 0;
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
	editorRefreshScreen();
	if (s[0]!= 0)
		perror(s);
	else
	{
		if (s[1] < 0)
			error = (256 + s[1]);
		else
			error = s[1];
		write(STDERR , &s[1], 1);
		editorRefreshScreen();
	}
	exit(error);
}

void editorRefreshScreen(void)
{
	write(STDOUT_FILENO, "\x1b[2J", 4);
	write(STDOUT_FILENO, "\x1b[H", 3);
}

void enableRawMode(void)
{
	struct	termios raw;

	if (tcgetattr(STDIN_FILENO, &orig_termios) == -1)
		die("tcgetattr");
	raw = orig_termios;
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

