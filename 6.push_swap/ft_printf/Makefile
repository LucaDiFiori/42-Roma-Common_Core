# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ldi-fior <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/17 18:36:18 by ldi-fior          #+#    #+#              #
#    Updated: 2024/01/18 13:08:44 by ldi-fior         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

SRCS = ft_putstr_f.c ft_print_u_f.c ft_putnbr_f.c ft_putnbr_base_up_f.c \
	   ft_putnbr_base_low_f.c ft_putchar_f.c ft_printf.c \
	   ft_print_memory_f.c

OUT = $(SRCS:.c=.o)

CC = gcc

CFLAGS = -Wall -Werror -Wextra
 
.c.o:
		${CC} ${CFLAGS} -g -c $< -o ${<:.c=.o}

$(NAME): $(OUT)
		ar rcs $(NAME) $(OUT)

all:	$(NAME)

clean:
		rm -f $(OUT) $(BOUT)

fclean: clean
		rm -f $(NAME)

re: 	fclean all
