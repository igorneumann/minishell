/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narroyo- <narroyo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 19:18:47 by narroyo-          #+#    #+#             */
/*   Updated: 2021/05/27 16:44:20 by narroyo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_init(t_cmd *cmd, char **envp)
{
	editorRefreshScreen();
	ft_env(&*envp);
	cmd->i = 0;
	cmd->in = (char*)malloc(sizeof(char) * (1024));
	cmd->in[0] = 13;
}

void	ft_presentation(void)
{
	printf("\r\n\r\n                \x1B[33mᕙ ( \x1b[36m^");
	printf("\x1b[35m ₒ \x1b[36m^\x1B[33m   ) (");
	printf("\x1b[35m ✿\x1b[36m  ◠\x1b[35m ‿ \x1b[36m◠ \x1B[33m)\r\n\r\n");
	printf("                         ");
	printf("\e[1;32mMiniShell\e[0m\r\n            ");
	printf("\x1b[36m         narroyo- && ineumann\r\n\r\n\r\n");
}

void	ft_read_arguments(t_cmd *cmd)
{
	int		i;
	char	buffer[512];

	i = 0;
	if (ft_strnstr(cmd->in, "pwd", 3) != NULL)
	{
		getcwd(buffer, -1);
		printf("\x1B[33m¿Ya te has perdido? Estás en \e[1;33m");
		printf("%s\n", buffer);
		printf("\e[0m\r\n");
	}
//	cmd->pos = ft_strnstr(cmd->pos, '\n', 1);
}

void	ft_cmd_line(t_cmd *cmd)
{
	while (1)
	{
		if (cmd->i == 0)
			printf("\e[1;32m¿En qué puedo ayudarte?: \e[0m");
		processkeypress(cmd);
	}
	free(cmd->in);
	cmd->in = NULL;
}

int main(int argc, char **argv, char **envp)
{
	t_cmd	cmd;

	(void)argc;
	(void)argv;
	ft_init(&cmd, &*envp);
	ft_presentation();
	ft_cmd_line(&cmd);

	return (0);
}
