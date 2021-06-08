/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narroyo- <narroyo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 19:18:47 by narroyo-          #+#    #+#             */
/*   Updated: 2021/06/08 19:02:09 by narroyo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_init(t_cmd *cmd, char **envp, t_raw *raw)
{
	editorRefreshScreen();
	cmd->raw = raw;
	cmd->list = NULL;
	cmd->i = 0;
	cmd->list = NULL;
	cmd->in = (char *)calloc(1024, sizeof(char) * (1024));
	cmd->buff = (char *)calloc(1024, sizeof(char) * (1024));
	cmd->in[0] = 13;
	cmd->buff[0] = 13;
	ft_save_env(cmd, envp);
	enableRawMode(raw);
}

void	ft_presentation(void)
{
	ft_putstr("\r\n\r\n                \x1B[33mᕙ ( \x1b[36m^");
	ft_putstr("\x1b[35m ₒ \x1b[36m^\x1B[33m   ) (");
	ft_putstr("\x1b[35m ✿\x1b[36m  ◠\x1b[35m ‿ \x1b[36m◠ \x1B[33m)\r\n\r\n");
	ft_putstr("                         \e[1;32mMiniShell\e[0m\r\n");
	ft_putstr("\x1b[36m                   narroyo- && ineumann\r\n\r\n\r\n");
}

void	ft_cmd_line(t_cmd *cmd)
{
	while (1)
	{
		if (cmd->i == 0 && cmd->in[0] == 13)
		{
			cmd->in[0] = '\0';
			ft_putstr("\e[1;32m¿En qué puedo ayudarte?: \e[0m");
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
