/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_rawmode.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narroyo- <narroyo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 17:43:45 by ineumann          #+#    #+#             */
/*   Updated: 2021/09/13 11:20:51 by narroyo-         ###   ########.fr       */
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
	exit(error);
}

void	refresh_screen(void)
{
	write(STDOUT_FILENO, "\x1b[2J", 4);
	write(STDOUT_FILENO, "\x1b[H", 3);
}

void	enable_raw_mode(t_raw *raw)
{
	if (tcgetattr(STDIN_FILENO, &raw->orig) == -1)
		die("tcgetattr", raw);
	raw->raw = raw->orig;
	raw->raw.c_iflag &= ~(BRKINT | ICRNL);
	raw->raw.c_lflag &= ~(ECHO | ICANON);
	raw->raw.c_cc[VMIN] = 0;
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw->raw) == -1)
		die("tcsetattr", raw);
}

char	f_raw(t_raw *raw)
{
	int		nread;
	char	c;

	nread = read(STDIN_FILENO, &c, 1);
	while (nread != 1 && g_reset != 2)
	{
		if (nread == -1 && errno != EAGAIN)
			die("read", raw);
		nread = read(STDIN_FILENO, &c, 1);
	}
	return (c);
}
