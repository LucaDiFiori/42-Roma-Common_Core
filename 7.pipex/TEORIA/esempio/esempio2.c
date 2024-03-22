#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>
#include <limits.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>

/*Voglio che il processo figlio scriva un argv nella pipe e che il padre lo printi
  Questa volta reindirizzando l'output su un file invece che sullo STDOUT.
  Nello specifico: Potrei farlo creando un file ed usando l'fd specifico con write
                   ma invece voglio usare printf che stampa sullo STDOUT
                   (Dovrò quindi reindirizzare lo STDOUT assegnandogli il mio file)*/

int main(int argc, char **argv)
{
    int fd[2];
    int pid;
    char buffer[100];
    int fdfile;

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
    - chiudo l fd di scrittura della pipe perchè non serve
    - apro il file
    - sostituisco lo STDOUT con il mio file
    - Chiudo il vecchio fd legato al file dato che è stato reindirizzaro su STDOUT
    - leggo dalla pipe e salvo nel buffer la stringa inviata dal figlio
    - chiudo l fd di lettura fd[0]
    - stampo la stringa ricevuta sul file creato tramite printf*/

    else
    {
        waitpid(pid, NULL, 0);
        close(fd[1]);

        fdfile = open("esempio2.txt", O_WRONLY | O_CREAT, 0777);
        if (fdfile == -1)
        {
            printf("Opening Error\n");
            return (2);
        }

        printf("Sono il processo e scriverò il messaggio sul file esempio2.txt:\n");

        dup2(fdfile, 1);
        close(fdfile);

        read(fd[0], buffer, strlen(argv[1]) + 1);
        close (fd[0]);

        printf("%s\n", argv[1]);
    }  
}