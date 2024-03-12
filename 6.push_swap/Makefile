# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ldi-fior <ldi-fior@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/19 12:04:17 by ldi-fior          #+#    #+#              #
#    Updated: 2024/02/29 14:30:33 by ldi-fior         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = push_swap

NAME_BONUS =  checker

SRCS = checks.c close_utils.c init.c lib.c lib_2.c main.c max_min.c \
	   moves_s.c moves_p.c moves_r.c move_rr.c sorting_utils.c find_target.c \
	   push_swap.c utils_target.c sort.c\

OBJS = $(SRCS:.c=.o)

B_SRCS = ./bonus/get_next_line/get_next_line.c ./bonus/moves_rr_bonus.c \
		 ./bonus/moves_p_bonus.c ./bonus/moves_r_bonus.c \
		 ./bonus/moves_s_bonus.c ./bonus/main.c ./bonus/check_bonus.c \
		 ./bonus/get_next_line/get_next_line_utils.c \
		 checks.c close_utils.c init.c lib.c lib_2.c max_min.c \
	   	 moves_s.c moves_p.c moves_r.c move_rr.c sorting_utils.c find_target.c \
	     push_swap.c utils_target.c sort.c ./bonus/make_moves.c \
		 
B_OBJS = $(B_SRCS:.c=.o)

CC = gcc

FTPRINTF = ft_printf/

CFLAGS = -Wall -Werror -Wextra


$(NAME) : $(OBJS)
		  @ make -C $(FTPRINTF)
		  $(CC) $(CFLAGS) $(OBJS) -o $(NAME) ft_printf/libftprintf.a

bonus:	$(B_OBJS)
		@ touch $@
		@ make -C ./ft_printf/
		$(CC) $(CFLAGS) $(B_OBJS) -o $(NAME_BONUS) ./ft_printf/libftprintf.a

all:	$(NAME) bonus

clean:
		@make clean -C $(FTPRINTF)
		@rm -f $(OBJS) $(B_OBJS)

fclean: clean
		@make fclean -C $(FTPRINTF)
		@rm -f $(NAME) $(NAME_BONUS)

re: fclean all	