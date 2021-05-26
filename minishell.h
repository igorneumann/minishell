/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineumann <ineumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 20:20:24 by narroyo-          #+#    #+#             */
/*   Updated: 2021/05/26 17:21:45 by ineumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./includes/libft/libft.h"
# include "./includes/gnl/get_next_line.h"

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <sys/param.h>
# include <sys/mount.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/errno.h>
# include <termios.h>

# define STDIN	0
# define STDOUT 1
# define STDERR	2

typedef struct				s_cmd
{
	char					*in;
	int						i;
	int						pos;
}							t_cmd;

void	ft_init(t_cmd *cmd);
void	ft_presentation(void);
void	ft_read_arguments(t_cmd *cmd);
void	ft_cmd_line(t_cmd *cmd);
int		main();
void	enableRawMode(void);
char	f_raw(void);
void	processkeypress(t_cmd *cmd);
void	editorRefreshScreen(void);

#endif
