#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>
#include <limits.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>

/*Voglio che il processo figlio scriva un argv nella pipe e che il padre lo printi*/

int main(int argc, char **argv)
{
    int fd[2];
    int pid;
    char buffer[100];

    if (argc != 2)
    {
        printf("Error");
        return (1);
    }

    if (pipe(fd) == -1)
    {
        write(2,"Error", 5);
        return (1);
    }

    /*Creo il nuovo processo*/
    pid = fork();
    if (pid == -1)
    {
        write(2,"Error", 5);
        return (2);   
    }

    /*Nel figlio:
      - chiudo fd[0] di lettura della pipe perchè non serve
      - scrivo nella pipe
      - chiudo l fd di scrittura*/
    else if (pid == 0)
    {
        close(fd[0]);
        printf("Sono Il processo figlio e sto inviando un messaggio\n");
        write(fd[1], argv[1], strlen(argv[1]));
        write(fd[1], "\n", 1);
        close(fd[1]);
    }

    /*Nel padre:
    - Aspetto il figlio
    - chiudo l fd della pipe di scrittura perchè non serve
    - leggo dalla pipe e salvo nel buffer la stringa inviata dal figlio
    - chiudo l fd di lettura
    - stampo la stringa ricevuta a schermo*/

    else
    {
        waitpid(pid, NULL, 0);
        close(fd[1]);
        read(fd[0], buffer, strlen(argv[1]) + 1);
        close (fd[0]);
        printf("Sono il processo padre ed ho ricevuto il messaggio:\n");
        write(1, argv[1], strlen(argv[1]));
        printf("\n");
    }  
}