/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_rawmode.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineumann <ineumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 17:43:45 by ineumann          #+#    #+#             */
/*   Updated: 2021/07/06 18:38:28 by ineumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	die(const char *s, t_raw *raw)
{
	int	error;

	error = 0;
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw->orig);
	if (s[0] != 0)
		perror(s);
	else
	{
		if (s[1] < 0)
			error = (256 + s[1]);
		else
			error = s[1];
		write(STDERR, &s[1], 1);
	}
//	system("leaks minishell");
	exit(error);
}

void	RefreshScreen(void)
{
	write(STDOUT_FILENO, "\x1b[2J", 4);
	write(STDOUT_FILENO, "\x1b[H", 3);
}

void	enableRawMode(t_raw *raw)
{
	if (tcgetattr(STDIN_FILENO, &raw->orig) == -1)
		die("tcgetattr", raw);
	raw->raw = raw->orig;
	raw->raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
	raw->raw.c_oflag &= ~(OPOST);
	raw->raw.c_cflag |= (CS8);
	raw->raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
	raw->raw.c_cc[VMIN] = 0;
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw->raw) == -1)
		die("tcsetattr", raw);
}

char	f_raw(t_raw *raw)
{
	int		nread;
	char	c;

	nread = read(STDIN_FILENO, &c, 1);
	while (nread != 1)
	{
		if (nread == -1 && errno != EAGAIN)
			die("read", raw);
		nread = read(STDIN_FILENO, &c, 1);
	}
	return (c);
}
