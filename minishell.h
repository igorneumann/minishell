/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narroyo- <narroyo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 20:20:24 by narroyo-          #+#    #+#             */
/*   Updated: 2021/06/02 10:28:34 by narroyo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./includes/libft/libft.h"

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
# include <term.h>

# define STDIN 0
# define STDOUT 1
# define STDERR 2

typedef struct s_data
{
	struct s_data	*prev;
	char			*in;
	char			*copy;
	struct s_data	*next;
}					t_data;

typedef struct s_envp
{
	struct s_envp	*prev;
	char			*key;
	char			*value;
	struct s_envp	*next;
}					t_envp;

typedef struct s_raw
{
	struct termios	raw;
	struct termios	orig;
}					t_raw;

typedef struct s_command
{
	char		*in;
	int			i;
	char		*pos;
	char		**env;
	t_data		*list;
	t_envp		*envp;
	t_raw		*raw;
}				t_cmd;

/*
*** Main
*/

void	ft_init(t_cmd *cmd, char **envp, t_raw *raw);
void	ft_presentation(void);
void	ft_read_arguments(t_cmd *cmd);
void	ft_cmd_line(t_cmd *cmd);

/*
*** f_rawmode
*/

void	die(const char *s, t_raw *raw);
void	editorRefreshScreen(void);
void	enableRawMode(t_raw *raw);
char	f_raw(t_raw *raw);

/*
*** lists
*/

t_data	*ft_new(char *in);
void	ft_lst_add_front(t_data **in, t_data *new);
void	ft_lst_remove_front(t_data *in);
void	ft_lst_add_back(t_data **in, t_data *new);

/*
*** instructions.c
*/

t_envp	*ft_new_env(char *in);
void	ft_save_env(t_cmd *cmd, char **envp);

/*
*** keypress.c
*/

void	processkeypress(t_cmd *cmd);
void	ft_backspace(t_cmd *cmd);

/*
*** commands.c
*/

int		ft_commands(t_cmd *cmd);
int		ft_history(t_cmd *cmd, char *seq);
void	ft_dupin(t_cmd *cmd);

/*
*** utils.c
*/

t_data	*ft_lst_last(t_data *elem);
t_data	*ft_lst_first(t_data *elem);
void	ft_printlist(t_data *x);
void	ft_print_env(t_envp *x);

/*
*** arguments.c
*/

void	ft_pwd(t_cmd *cmd);
void	ft_env(t_cmd *cmd);
void	ft_export(t_cmd *cmd);

#endif
