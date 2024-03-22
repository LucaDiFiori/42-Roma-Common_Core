NAME = pipex

CC = gcc

CFLAGS = -Wall -Werror -Wextra

SRCS = main.c pipex_utils.c minilib.c command.c minilib_2.c dquote_split.c \
       split_utils.c

BSRCS =  bonus.c  bonus_utils.c pipex_utils.c minilib.c command.c \
         minilib_2.c dquote_split.c split_utils.c \
		 get_next_line/get_next_line.c \
		 get_next_line/get_next_line_utils.c \

OBJS = $(SRCS:.c=.o)

BOBJS = $(BSRCS:.c=.o)


#$(NAME) : $(OBJS): Questa è una regola di dipendenza nel Makefile. 
#Indica che il target $(NAME) dipende dai file elencati nella variabile $(OBJS). 
#Ciò significa che se uno o più file elencati in $(OBJS) sono stati modificati 
#più recentemente rispetto a $(NAME), Make eseguirà i comandi associati 
#per aggiornare $(NAME).
$(NAME) : $(OBJS)
		$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

bonus:	$(BOBJS)
		$(CC) $(CFLAGS) $(BOBJS) -o $(NAME)

all:	$(NAME) bonus

clean:
		@rm -f $(OBJS)
		@rm -f $(BOBJS)

fclean: clean
		@rm -f $(NAME)
re: 	fclean all