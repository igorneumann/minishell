/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narroyo- <narroyo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 20:20:24 by narroyo-          #+#    #+#             */
/*   Updated: 2021/05/26 21:20:33 by narroyo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../Libft/libft.h"

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

# define STDIN 0
# define STDOUT 1
# define STDERR 2

typedef struct s_cm
{
	char		*in;
	int			i;
	char		*pos;
}				t_cmd;

typedef struct s_data
{
	struct s_data	*prev;
	char			*in;
	char			*copy;
	struct s_data	*next;
}					t_data;

typedef struct s_data
{
	char	**env;
}				t_data;

void	ft_init(t_cmd *cmd);
void	ft_presentation(void);
void	ft_read_arguments(t_cmd *cmd);
void	ft_cmd_line(t_cmd *cmd);
void	enableRawMode(void);
char	f_raw(void);
void	processkeypress(t_cmd *cmd);
void	editorRefreshScreen(void);

#endif
