# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: narroyo- <narroyo-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/27 10:24:24 by narroyo-          #+#    #+#              #
#    Updated: 2021/05/27 10:28:51 by narroyo-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	minishell
HEADER			=	-I ./includes/libft/
SRCS			=	main.c f_rawmode.c lists.c instructions.c
LIBFT			=	../Libft
OBJS 			=	$(SRCS:.c=.o)
LIBS			=	../Libft/libft.a
CC				=	@gcc -g -Wall -Wextra -Werror -g3 -fsanitize=address

# -g3 -fsanitize=address

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

run:	fclean all
		@make compile

.PHONY: all clean fclean re norm
