/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineumann <ineumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 20:20:24 by narroyo-          #+#    #+#             */
/*   Updated: 2021/06/09 17:44:37 by ineumann         ###   ########.fr       */
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
	int			not_found;
	char		*buff;
	char		**env;
	t_data		*list;
	t_envp		*envp;
	t_raw		*raw;
}				t_cmd;

/*
*** arguments.c
*/

void	ft_pwd(t_cmd *cmd);
void	ft_echo(t_cmd *cmd);
void	previous_folder(char *path, char *old_path, int j);
void	ft_cd(t_cmd *cmd, int i);

/*
*** main.c
*/

void	ft_init(t_cmd *cmd, char **envp, t_raw *raw);
void	ft_presentation(void);
void	ft_cmd_line(t_cmd *cmd);

/*
*** f_rawmode
*/

void	die(const char *s, t_raw *raw);
void	editorRefreshScreen(void);
void	enableRawMode(t_raw *raw);
char	f_raw(t_raw *raw);

/*
*** lists_utils
*/

t_data	*ft_lst_last(t_data *elem);
t_data	*ft_lst_first(t_data *elem);
t_envp	*search_elem(t_envp *elem, char *wanted);
t_envp	*change_value(t_envp *elem, char *new_value);
t_envp	*remove_elem(t_envp *elem);

/*
*** lists
*/

t_data	*ft_new(char *in);
void	ft_lst_add_front(t_data **in, t_data *new);
void	ft_lst_remove_front(t_data *in);
void	ft_lst_add_back(t_data **in, t_data *new);
void	ft_lst_edit(t_data **in, t_data *new);

/*
*** env.c
*/

t_envp	*ft_new_env_value(char *in, t_envp	*new, int i);
t_envp	*ft_new_env(char *in);
void	ft_save_env(t_cmd *cmd, char **envp);
void	ft_options(t_cmd *cmd, int i);
void	error_file_or_directory(t_cmd *cmd, int i);
void	ft_env(t_cmd *cmd);

/*
*** export.c
*/

void	ft_include(t_cmd *cmd, char *aux);
void	ft_export(t_cmd *cmd);
void	ft_unset(t_cmd *cmd);

/*
*** keypress.c
*/

void	processkeypress(t_cmd *cmd);
void	ft_backspace(t_cmd *cmd);
void	ft_editstring(t_cmd *cmd, char c);
void	ft_enter(t_cmd *cmd);
void	noprintable(t_cmd *cmd, char c);

/*
*** commands.c
*/

int		ft_commands(t_cmd *cmd);
int		ft_arrows(t_cmd *cmd, char *seq);
int		ft_homeend(t_cmd *cmd, char *seq);
int		ft_delete(t_cmd *cmd);

/*
*** history.c
*/

int		ft_history(t_cmd *cmd, char *seq);
void	ft_dupin(t_cmd *cmd, int src);
void	ft_updatehist(t_cmd *cmd);

/*
*** read_arguments.c
*/

void	arguments(t_cmd *cmd, int i);
void	ft_read_arguments(t_cmd *cmd);

/*
*** utils.c
*/

int		command_not_found(char *str, t_cmd *cmd);
void	ft_printlist(t_data *x, char *buff);
void	ft_print_env(t_envp *x);
void	ft_sort_env(t_cmd *cmd);
void	ft_print_export(t_envp *x);

#endif
