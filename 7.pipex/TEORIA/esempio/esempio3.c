#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>
#include <limits.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>

/* Programma in cui il processo figlio legge una stringa da un file, la invia al
   padre il quale la stamperà su un altro file che andrà a creare*/ 

int main()
{
    int fd[2];
    int pid;
    char buffer[100];
    int fdfile_in;
    int fdfile_out;

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
      - Apro il file di input
      - Chiudo l'fd di lettura della pipe perchè non serve
      - reindirizzo lo STDIN con l'fd del file (faccio diventare il file lo STDIN)
      - Chiudo l fd del file in quanto reindirizzato
      - Reindirizzo lo STDOUT per scrivere nella pipe con printf
      - chiudo l'fd di scrittura della pipe in quanto reindirizzato
      - Leggo dal nuovo STDIN (il fileIn)
      - Scrivo, tramite printf, il messaggio letto nella pipe*/
    else if (pid == 0)
    {
        fdfile_in = open("esempio3In.txt", O_RDWR, 0777);
        if (fdfile_in == -1)
        {
            printf("Opening Error\n");
            return (2);
        }
        printf("Sono Il processo figlio e sto inviando un messaggio tramite il file esempio3In.txt\n");

        close(fd[0]);

        dup2(fdfile_in, 0);
        close(fdfile_in);

        dup2(fd[1], 1);
        close(fd[1]);

        read (0, buffer, 17);

        printf("%s", buffer);
    }

    
    /*Nel padre:
    - Aspetto il figlio
    - chiudo l'fd[1] di scrittura della pipe perchè non mi serve
    - Creo e apro il file di output
    - reindirizzo l'fd di input rendendo quello della pipe (fd[0]) lo STDIN
    - chiudo fd[0] in quanto reindirizzato
    - leggo dalla pipe (STDIN) il messaggio tramite read
    - rimpiazzo l'fd di output standard (1) con l'fd del file aperto
    - chiudo l'fd del file in quanto reindirizzato
    - stampo sul fileOut il messaggio di risposta con printf*/
    else
    {
        waitpid(pid, NULL, 0);
        close(fd[1]);

        fdfile_out = open("esempio3Out.txt", O_WRONLY | O_CREAT, 0777);
        if (fdfile_out == -1)
        {
            printf("Opening Error\n");
            return (2);
        }

        printf("Sono il processo e scriverò il messaggio sul file esempio3Out.txt:\n");

        dup2(fd[0], 0);
        close(fd[0]);

        if (read(0, buffer, 17) == -1)
        {
            printf("Error reading (padre)");
            return (3);
        }

        dup2(fdfile_out, 1);
        close(fdfile_out);


        printf("%s\n", buffer);
    }
}