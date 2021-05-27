/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narroyo- <narroyo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 20:20:24 by narroyo-          #+#    #+#             */
/*   Updated: 2021/05/27 10:28:40 by narroyo-         ###   ########.fr       */
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

typedef struct s_command
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

typedef struct s_instruction
{
	char		**env;
}				t_inst;

/*
*** Main
*/

void	ft_init(t_cmd *cmd, char **envp);
void	ft_presentation(void);
void	ft_read_arguments(t_cmd *cmd);
void	ft_cmd_line(t_cmd *cmd);

/*
*** f_rawmode
*/

void	die(const char *s);
void	editorRefreshScreen(void);
void	enableRawMode(void);
char	f_raw(void);
void	processkeypress(t_cmd *cmd);
int		ft_commands(t_cmd *cmd);

/*
*** lists
*/

t_data	*ft_new(char *in);
void	ft_lst_add_front(t_data **in, t_data *new);
void	ft_lst_add_back(t_data **in, t_data *new);
t_data	*ft_lst_last(t_data *elem);
t_data	*ft_lst_first(t_data *elem);

/*
*** instructions.c
*/

void	ft_env(char **envp);

#endif
