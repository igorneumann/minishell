/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineumann <ineumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 19:18:47 by narroyo-          #+#    #+#             */
/*   Updated: 2021/05/26 20:47:33 by ineumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_init(t_cmd *cmd)
{
	editorRefreshScreen();
	cmd->i = 0;
	cmd->in = (char*)calloc(1024, sizeof(char) * (1024));
	cmd->in[0] = 13;
}

void ft_presentation(void)
{
	ft_putstr("\r\n\r\n                \x1B[33mᕙ ( \x1b[36m^");
	ft_putstr("\x1b[35m ₒ \x1b[36m^\x1B[33m   ) (");
	ft_putstr("\x1b[35m ✿\x1b[36m  ◠\x1b[35m ‿ \x1b[36m◠ \x1B[33m)\r\n\r\n");
	ft_putstr("                         ");
	ft_putstr("\e[1;32mMiniShell\e[0m\r\n            ");
	ft_putstr("\x1b[36m         narroyo- && ineumann\r\n\r\n\r\n");
}

void	ft_read_arguments(t_cmd *cmd)
{
	int		i;
	char	buffer[512];

	i = 0;
	if (ft_strnstr(cmd->in, "pwd", 3) != NULL)
	{
		getcwd(buffer, -1);
		ft_putstr("\x1B[33m¿Ya te has perdido? Estás en \e[1;33m");
		ft_putstr(buffer);
		ft_putstr("\e[0m\r\n");
	}
	else if (ft_strnstr(cmd->in, "exit", 4) != NULL)
		die(0);
}

void ft_cmd_line(t_cmd *cmd)
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
	cmd->in = NULL;
}

int main()
{
	t_cmd cmd;

	ft_init(&cmd);
	ft_presentation();
	ft_cmd_line(&cmd);

	return (0);
}
