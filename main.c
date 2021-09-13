/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineumann <ineumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 19:18:47 by narroyo-          #+#    #+#             */
/*   Updated: 2021/09/13 19:19:44 by ineumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_init(t_cmd *cmd, char **envp, t_raw *raw)
{
	refresh_screen();
	cmd->raw = raw;
	cmd->i = 0;
	cmd->check_replacement = 0;
	cmd->list = NULL;
	cmd->nexcom = NULL;
	cmd->bkp_fdin = -1;
	cmd->bkp_fdout = -1;
	cmd->inpt = ft_strdup("\x0D");
	cmd->outp = ft_strdup("\x0D");
	cmd->in = ft_strdup("\x0D");
	cmd->buff = ft_strdup("\x0D");
	cmd->dollar_value = NULL;
	cmd->env = NULL;
	cmd->counter = 0;
	ft_save_env(cmd, envp);
	enable_raw_mode(raw);
}

void	ft_reset(t_cmd *cmd)
{
	free(cmd->in);
	cmd->in = ft_strdup("\x0D");
	free(cmd->inpt);
	cmd->inpt = ft_strdup("\x0D");
	free(cmd->outp);
	cmd->outp = ft_strdup("\x0D");
	cmd->param = free_list(cmd->param);
	cmd->nexpip = free_list(cmd->nexpip);
	free(cmd->buff);
	cmd->buff = ft_strdup("\x0D");
	cmd->i = 0;
	cmd->fd2[0] = 0;
	cmd->fd1[0] = 0;
	cmd->bkp_fdin = -1;
	cmd->bkp_fdout = -1;
	cmd->in_fd = -1;
	cmd->out_fd = -1;
}

void	ft_presentation(void)
{
	ft_putstr("\r\n\r\n                \x1B[33mᕙ ( \x1b[36m^");
	ft_putstr("\x1b[35m ₒ \x1b[36m^\x1B[33m   ) (");
	ft_putstr("\x1b[35m ✿\x1b[36m  ◠\x1b[35m ‿ \x1b[36m◠ \x1B[33m)\r\n\r\n");
	ft_putstr("                         \e[1;32mMiniShell\e[0m\r\n");
	ft_putstr("\x1b[36m                   ineumann && narroyo-\r\n\r\n\r\n");
}

void	ft_cmd_line(t_cmd *cmd)
{
	signal(SIGINT, promptin);
	while (1)
	{
		if (g_reset == 2 || (cmd->i == 0 && cmd->in[0] == 13))
		{
			if (g_reset == 2)
				cmd->i = 0;
			free(cmd->in);
			cmd->in = ft_strdup("\0");
			ft_putstr("\e[1;32m¿En qué puedo ayudarte?: \e[0m");
			g_reset = 0;
		}
		processkeypress(cmd);
	}
	free(cmd->in);
	free(cmd->buff);
	cmd->in = NULL;
	cmd->buff = NULL;
}

int	main(int argc, char **argv, char **envp)
{
	t_cmd	cmd;
	t_raw	raw;

	(void)argc;
	(void)argv;
	ft_init(&cmd, envp, &raw);
	ft_presentation();
	ft_cmd_line(&cmd);
	die(0, &raw);
	return (0);
}
