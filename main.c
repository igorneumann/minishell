/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineumann <ineumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 19:18:47 by narroyo-          #+#    #+#             */
/*   Updated: 2021/06/01 19:33:30 by ineumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_init(t_cmd *cmd, t_raw *raw)
{
	editorRefreshScreen();
	cmd->raw = raw;
	cmd->list = NULL;
	cmd->i = 0;
	cmd->list = NULL;
	cmd->in = (char*)calloc(1024, sizeof(char) * (1024));
	cmd->in[0] = 13;
}

void ft_presentation(void)
{
	ft_putstr("\r\n\r\n                \x1B[33mᕙ ( \x1b[36m^");
	ft_putstr("\x1b[35m ₒ \x1b[36m^\x1B[33m   ) (");
	ft_putstr("\x1b[35m ✿\x1b[36m  ◠\x1b[35m ‿ \x1b[36m◠ \x1B[33m)\r\n\r\n");
	ft_putstr("                         \e[1;32mMiniShell\e[0m\r\n");
	ft_putstr("\x1b[36m                   narroyo- && ineumann\r\n\r\n\r\n");
}

void	ft_read_arguments(t_cmd *cmd)
{
	int		i;
	char	code[2];
	char	buffer[512];
	t_data	*x;

	i = 0;
	code[0] = 0;
	code[1] = 0;
	while (cmd->in[i] == ' ')
		i++;
	if (ft_strlen(cmd->in) > 0)
		ft_lst_add_front(&cmd->list, ft_new(cmd->in));
	x = cmd->list;
	ft_printlist(x);
	if (ft_strnstr(cmd->in, "pwd", 3) != NULL)
	{
		getcwd(buffer, -1);
		ft_putstr("\x1B[33m¿Ya te has perdido? Estás en \e[1;33m");
		ft_putstr(buffer);
		ft_putstr("\e[0m\r\n");
	}
	else if (ft_strnstr(cmd->in, "exit", 4) != NULL)
	{
		i += 4;
		while (cmd->in[i] == ' ')
			i++;
		if 	(cmd->in[i] >= 0 || cmd->in[i] <= 9 ||
		cmd->in[i] == '-' || cmd->in[i] == '+')
			code[1] = ft_atoi(&cmd->in[i]);
		die(code, cmd->raw);
	}
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
	t_raw raw;

	ft_init(&cmd, &raw);
	ft_presentation();
	ft_cmd_line(&cmd);
	die(0, &raw);
	return (0);
}

void	ft_printlist(t_data *x)
{
	t_data *y;

	y = ft_lst_first(x);
	while (y && y != x)
	{
		printf("%s %p\r\n", y->in, x);
		y = y->next;
	}	
	ft_putstr("\x1B[33mᕙ ( \x1b[35m ₒ \x1b[36m^\x1B[33m   ) (");
	ft_putstr("\x1b[35m ✿\x1b[36m  ◠\x1b[35m ‿ \x1b[36m◠ \x1B[33m)\r\n");
	while (x)
	{
		printf("%s %p\r\n", x->in, x);
		x = x->next;
	}
}