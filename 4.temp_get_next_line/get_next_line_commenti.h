#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

/*In C, puoi utilizzare direttive di precompilazione 
per definire macro durante la compilazione del programma. 
Se desideri definire una macro con un valore specifico 
durante la compilazione, puoi farlo utilizzando 
l'opzione -D seguita dal nome della macro e dal suo valore

Nel nostro caso, se non viene inserito in compilazione un
valore per BUFFER_SIZE, questa macro sarà automaticamente
settata ad 1
*/
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

/*fcntl.h contiene funzioni read, open etc*/
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>

size_t	ft_strlen(const char *s);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *src);
char	*ft_strjoin(char *s1, char *s2);
char    *get_next_line(int fd);

#endif