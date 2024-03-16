NAME = pipex

SRCS = main.c pipex_utils.c minilib.c command.c minilib_2.c

BSRCS = 

OBJS = $(SRCS:.c=.o)

BOBJS = $(BSRCS:.c=.o)

CC = gcc

CFLAGS = -Wall -Werror -Wextra

#$(NAME) : $(OBJS): Questa è una regola di dipendenza nel Makefile. 
#Indica che il target $(NAME) dipende dai file elencati nella variabile $(OBJS). 
#Ciò significa che se uno o più file elencati in $(OBJS) sono stati modificati 
#più recentemente rispetto a $(NAME), Make eseguirà i comandi associati 
#per aggiornare $(NAME).
$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

bonus:	$(BOBJS)
			$(CC) $(CFLAGS) $(BOBJS) -o $(NAME)

all:	$(NAME)

clean:
		@rm -f $(OBJS)
		@rm -f $(BOBJS)

fclean: clean
		@rm -f $(NAME)

re: 	fclean all