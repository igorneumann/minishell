# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ineumann <ineumann@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/27 10:24:24 by narroyo-          #+#    #+#              #
#    Updated: 2021/06/09 17:22:28 by ineumann         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	minishell
HEADER			=	-I ./includes/libft/
SRCS			=	main.c ./includes/gnl/get_next_line.c ./f_rawmode.c \
					lists.c env.c commands.c keypress.c utils.c arguments.c \
					lists_utils.c export.c envp.c read_arguments.c history.c
LIBFT			=	./includes/libft
OBJS 			=	$(SRCS:.c=.o)
LIBS			=	./includes/libft/libft.a
CC				=	@gcc -g -Wall -Wextra -Werror -g3 -fsanitize=address

#  al final de CC -g3 -fsanitize=address

all: $(NAME)

$(NAME): $(OBJS)
	@$(MAKE) -s bonus -C $(LIBFT)
	$(CC) $(SRCS) $(LIBS) -o $(NAME)

norm:
	norminette -R ./

clean:
	@rm -f $(OBJS)
	@$(MAKE) -s clean -C $(LIBFT)

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -s fclean -C $(LIBFT)

re: fclean all

.PHONY: all clean fclean re norm
