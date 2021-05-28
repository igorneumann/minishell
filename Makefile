# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: narroyo- <narroyo-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/27 10:24:24 by narroyo-          #+#    #+#              #
#    Updated: 2021/05/28 09:52:50 by narroyo-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	minishell
HEADER			=	-I ./includes/libft/
SRCS			=	main.c ./includes/gnl/get_next_line.c ./f_rawmode.c lists.c \
					instructions.c
LIBFT			=	./includes/libft
LIB_SRC			=	$(shell find libft | fgrep ".c")
OBJS 			=	$(SRCS:.c=.o)
LIBS			=	./includes/libft/libft.a
CC				=	@gcc -g -Wall -Wextra -Werror -g3 -fsanitize=address

#  al final de CC -g3 -fsanitize=address

all: $(NAME)

$(NAME): $(OBJS)
	-@make -C ./includes/libft
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

.PHONY: all clean fclean re norm
