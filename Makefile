# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ineumann <ineumann@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/27 10:24:24 by narroyo-          #+#    #+#              #
#    Updated: 2021/05/25 18:04:24 by ineumann         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	minishell
HEADER			=	-I ./includes/libft/
MAIN			=	./main.c
SRCS			=	./includes/gnl/get_next_line.c ./f_rawmode.c
LIBFT			=	./includes/libft
LIB_SRC			=	$(shell find libft | fgrep ".c")
OBJS 			=	$(MAIN:.c=.o)
SOBJ 			=	$(SRCS:.c=.o)
LIBS			=	./includes/libft/libft.a
CC				=	@gcc -g -Wall -Wextra -Werror

#  al final de CC -g3 -fsanitize=address

all: $(NAME)

$(NAME):
	-@make -C ./includes/libft
	-$(CC) $(HEADER) $(MAIN) $(SRCS) $(LIBS) -o $(NAME)

compile:
	-$(CC) $(HEADER) $(MAIN) $(SRCS) $(LIBS) -o $(NAME)

norm:
	norminette -R ./

clean:
	@rm -f $(OBJS)
	@rm -f *.bmp
	@make clean -C $(LIBFT)

fclean: clean
	@rm -f $(NAME)
	@make fclean -C $(LIBFT)

re: fclean all

run:	fclean all
		@make compile

.PHONY: all clean fclean re norm compile run
