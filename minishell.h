/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narroyo- <narroyo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 20:20:24 by narroyo-          #+#    #+#             */
/*   Updated: 2021/09/16 11:14:34 by narroyo-         ###   ########.fr       */
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
# include <sys/types.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/errno.h>
# include <termios.h>
# include <term.h>

# define STDIN 0
# define STDOUT 1
# define STDERR 2
# define READ_END 0
# define WRITE_END 1

int	g_reset;

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
	char	*in;
	int		i;
	int		fd1[2];
	int		fd2[2];
	t_list	*fdlist;
	int		not_found;
	int		out_fd;
	int		bkp_fdout;
	int		bkp_fdin;
	char	*outp;
	int		in_fd;
	char	*inpt;
	char	*buff;
	char	**env;
	char	**envorg;
	char	**path;
	char	*relative_path;
	char	*old_path;
	char	*tmp_in;
	int		quote_s;
	int		quote_d;
	int		quotes;
	int		output_status;
	char	**dollar_value;
	int		*old_len;
	int		d_counter;
	int		counter;
	int		dc;
	int		c_replace;
	int		c2_replace;
	char	*original;
	char	*without_quotes;
	int		check_replacement;
	int		c1;
	int		c2;
	int		simple;
	int		doubl;
	int		echo_nl;
	t_data	*list;
	t_data	*param;
	t_data	*nexcom;
	t_data	*nexpip;
	t_envp	*envp;
	t_raw	*raw;
}			t_cmd;

/*
*** arguments.c
*/
int		command_not_found(char *str, t_cmd *cmd);
void	ft_pwd(t_cmd *cmd);
void	ft_exit(t_cmd *cmd, int i);

/*
*** cd.c
*/
void	save_path(t_cmd *cmd, int i);
void	previous_folder(t_cmd *cmd);
void	ft_cd(t_cmd *cmd, int i);

/*
*** echo.c
*/
int		while_echo(t_cmd *cmd, int i, int j);
int		print_echo_nl(t_cmd *cmd, int i, int j);
void	print_echo(t_cmd *cmd, int i, int j);
void	ft_echo(t_cmd *cmd);

/*
*** main.c
*/
void	ft_init(t_cmd *cmd, char **envp, t_raw *raw);
void	ft_reset(t_cmd *cmd);
void	ft_presentation(void);
void	ft_cmd_line(t_cmd *cmd);

/*
*** f_rawmode
*/
void	die(const char *s, t_raw *raw);
void	refresh_screen(void);
void	enable_raw_mode(t_raw *raw);
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
void	ft_lst_add_back(t_data **in, t_data *new);
void	ft_lst_edit(t_data **in, t_data *new);
int		lst_size(t_envp *lst);

/*
*** free.c
*/
t_data	*free_list(t_data *lst);
t_envp	*free_env(t_envp *lst);
void	free_elem(t_envp *elem);
void	free_split(char **split);
t_data	*free_first(t_data *data);

/*
*** dollar.c
*/
int		new_lenght_amount(t_cmd *cmd);
void	replace(t_cmd *cmd);
void	replace_allocation(t_cmd *cmd);
int		cpy_global_var(t_cmd *cmd, int ch, int i);
void	dollar(t_cmd *cmd);

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
*** envp.c
*/
void	ft_print_env(t_envp *x);
char	*search_value(char *elem, t_cmd *cmd);
t_envp	*ft_new_env_value(char *in, t_envp	*new, int i);
t_envp	*ft_new_env(char *in);
void	ft_save_env(t_cmd *cmd, char **envp);

/*
*** export_utils.c
*/
void	ft_unset(t_cmd *cmd);
t_envp	*copy_env(t_envp *envp);
void	envp_to_arr(t_cmd *cmd, int i);

/*
*** export.c
*/
int		check_existence(t_cmd *cmd, char *aux, int i);
void	ft_include(t_cmd *cmd, char *aux);
int		new_env_element(t_cmd *cmd, int i);
void	ft_export(t_cmd *cmd);

/*
*** keypress.c
*/
void	processkeypress(t_cmd *cmd);
void	ft_backspace(t_cmd *cmd);
void	ft_editstring(t_cmd *cmd, char c);
void	ft_enter(t_cmd *cmd);
void	noprintable(t_cmd *cmd, char c);

/*
*** commandkeys.c
*/
int		commandkeys(t_cmd *cmd);
int		ft_arrows(t_cmd *cmd, char *seq);
int		ft_homeend(t_cmd *cmd, char *seq);
int		ft_delete(t_cmd *cmd);
int		ft_jumpword(t_cmd *cmd, char seq);

/*
*** semicolon.c
*/
void	ft_semicolon(t_cmd *cmd);
int		prepstr(char *str, int pos, int qt);
int		countleft(char *str, int pos, char c, char d);
int		countright(char *str, int pos, char c, char d);
int		findpipes(char *str);
int		findredir(char *str);

/*
*** history.c
*/
int		ft_history(t_cmd *cmd, char *seq);
void	ft_dupin(t_cmd *cmd, int src);
int		ft_altarrow(t_cmd *cmd);

/*
*** quotes.c
*/
int		check_quotes_error(t_cmd *cmd);
void	omit_quotes(t_cmd *cmd, char q1, char q2);
char	*replace_quotes(t_cmd *cmd);
int		check_replacement(t_cmd *cmd);

/*
*** quotes_utils.c
*/
int		count_char(char *line, char character);
int		ret_close(char quote, char *line, int i);
int		look_for_closure(char quote, char dollar, char *line, int i);
int		look_for_open(char quote, char quote_2, char *str, int i);
void	replace_global_var(t_cmd *cmd, char *var);

/*
*** read_arguments.c
*/
void	ft_read_arguments(t_cmd *cmd);
void	builtins(t_cmd *cmd, int i);
void	init_arguments(t_cmd *cmd);
int		ft_arguments(t_cmd *cmd);
void	ft_lst_add_arguments(t_data **in, char *new);

/*
*** utils.c
*/
void	ft_printlist(t_data *x);
void	swap(t_envp *a, t_envp *b);
void	ft_sort_env(t_envp *list, t_envp *elem, t_envp *next_elem, int swapped);
void	ft_print_export(t_envp *x);

/*
*** moreprompt.c
*/
void	ft_tab(t_cmd *cmd);
void	promptin(int i);
void	do_nothing(int i);

/*
*** exec.c
*/
int		executor(t_cmd *cmd);
int		exec(char *str, t_cmd *cmd);
char	**copyparam(t_cmd *cmd);
size_t	ft_strlentochar(const char *s, char c);
char	*ft_strduptochar(const char *s1, char c);

/*
*** path.c
*/
void	ft_path(t_cmd *cmd);
int		addpath(t_cmd *cmd, char *tmp);
int		pipexector(char *file, char *const *argv, char *const *envp);

/*
*** pipenator.c
*/
int		pipewhiler(t_cmd *cmd, int i);
void	pipenator(t_cmd *cmd, int i);
void	prep_exec(t_cmd *cmd);

/*
*** pipes.c
*/
int		pipes(t_cmd *cmd);
int		ft_startpipe(char *str, t_cmd *cmd);
int		ft_midpipe(char *str, t_cmd *cmd, int *ft_in, int *fd_out);
int		middlepiper(char *str, t_cmd *cmd, int i);
int		ft_endpipe(char *str, t_cmd *cmd, int i);

/*
*** redir.c
*/
int		redir(t_cmd *cmd, int i, int j, int k);
void	redirout_one(t_cmd *cmd, int *in[2], int *out[2]);
void	redirout(t_cmd *cmd, int i);;
int		tempinput(t_cmd *cmd);
int		redirector(t_cmd *cmd, int i, int j);

/*
*** clean.c
*/
int		cleanfds(t_cmd *cmd, int i, int red);
void	cleanspcback(char *str, int k);

/*
*** get_next_line.c
*/
int		get_next_line(int fd, char **line);

/*
*** other.c
*/
void	init_counters(t_cmd *cmd);
int		question_mark(t_cmd *cmd, char	*var);
void	free_all(t_cmd *cmd);
int		ctrl_d_c(t_cmd *cmd, char *seq);
void	open_files(t_cmd *cmd, int i, int j);

#endif
