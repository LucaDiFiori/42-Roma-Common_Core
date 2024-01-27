NAME = get_next_line.a

SRCS = \
	get_next_line_utils.c gnl_nocommenti.c
BSRCS = \

OUT = $(SRCS:.c=.o)

BOUT = $(BSRCS:.c=.o)

CC = gcc

CFLAGS = -Wall -Werror -Wextra
 
.c.o:
		${CC} ${CFLAGS} -g -c $< -o ${<:.c=.o}

$(NAME): $(OUT)
		ar rcs $(NAME) $(OUT)

bonus: 	$(BOUT)
		ar rcs $(NAME) $(BOUT)

all:	$(NAME)

clean:
		rm -f $(OUT) $(BOUT)

fclean: clean
		rm -f $(NAME)

re: 	fclean all
