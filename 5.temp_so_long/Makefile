# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ldi-fior <ldi-fior@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/23 15:45:49 by ldi-fior          #+#    #+#              #
#    Updated: 2024/02/13 17:22:52 by ldi-fior         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long

SRCS = main.c get_next_line/get_next_line.c get_next_line/get_next_line_utils.c \
		map_checks.c map_utils.c launch.c close_utils.c tile.c TEMP_UTILS.c \
		path_check.c hook_player.c hook_enemy.c loop.c image.c

OBJS = $(SRCS:.c=.o)

CC = gcc

FTPRINTF = ft_printf/

CFLAGS	= -Wall -Wextra -Werror
MFLAGS	= -lmlx -framework OpenGL -framework AppKit

$(NAME) : $(OBJS)
	@ make -C $(FTPRINTF)
	@ make -C ./mlx
	cp ./mlx/libmlx.dylib .
	${CC} ${CFLAGS} ${OBJS} ${MFLAGS} -o ${NAME} ft_printf/libftprintf.a


all:	$(NAME)

clean:
	@make clean -C $(FTPRINTF)
	@make clean -C ./mlx
	@rm -f $(OBJS)

fclean: clean
	@make fclean -C $(FTPRINTF)
	@rm -f libmlx.dylib
	@rm -f $(NAME)

re: fclean all