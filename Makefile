# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ineumann <ineumann@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/27 10:24:24 by narroyo-          #+#    #+#              #
#    Updated: 2021/09/22 19:53:20 by ineumann         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	minishell
HEADER			=	-I ./includes/libft/
SRCS			=	main.c ./includes/gnl/get_next_line.c ./f_rawmode.c \
					lists.c env.c commandkeys.c keypress.c utils.c arguments.c \
					lists_utils.c export.c envp.c read_arguments.c history.c \
					semicolon.c moreprompt.c exec.c export_utils.c pipes.c \
					free.c path.c pipenator.c redir.c quotes.c dollar.c cd.c \
					quotes_utils.c other.c echo.c echo_nl.c clean.c init.c \
					filename.c
LIBFT			=	./includes/libft
OBJS 			=	$(SRCS:.c=.o)
LIBS			=	./includes/libft/libft.a
CC				=	@gcc -g -Wall -Wextra -Werror

#  al final de CC -g3 -fsanitize=address

all: $(NAME)

$(NAME): $(OBJS)
	@$(MAKE) -s bonus -C $(LIBFT)
	$(CC) $(SRCS) $(LIBS) -o $(NAME)

run: re
	@reset
	@./minishell

norm:
	@norminette -R ./

clean:
	@rm -f $(OBJS)
	@$(MAKE) -s clean -C $(LIBFT)

fclean: clean
	@rm -f $(NAME)
	@rm -Rf minishell.dSYM
	@$(MAKE) -s fclean -C $(LIBFT)

re: fclean all

.PHONY: all clean fclean re norm run
