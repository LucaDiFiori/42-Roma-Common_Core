/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldi-fior <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 14:37:06 by ldi-fior          #+#    #+#             */
/*   Updated: 2024/03/13 14:37:06 by ldi-fior         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*Nel processo figlio:
  *Questa funzione reindirizza lo STDIN per leggere dal file,lo STDOU
   per scrivere nella pipe ed infine lancia il primo comando da eseguire

  - Apro il file di input
  - Chiudo l'fd di lettura della pipe perchè non serve
  - reindirizzo lo STDIN con l'fd del file (faccio diventare il file lo STDIN)
  - Chiudo l fd del file in quanto reindirizzato
  - Reindirizzo lo STDOUT per scrivere nella pipe
  - chiudo l'fd di scrittura della pipe in quanto reindirizzato
  - chiama la funzione che lancia il comando
*/
static void child_p(char **argv, char **envp, int *fd)
{
    int fd_file_in;

    fd_file_in = open(argv[1], O_RDONLY, 0777);
    if (fd_file_in == -1)
        quit_free("Error: Unable to open input file\n", NULL, NULL, 1);
    close(fd[0]);
    dup2(fd_file_in, 0);
    close(fd_file_in);
    dup2(fd[1], 1);
    close(fd[1]);
    command(argv[2], envp);
}

/*Nel processo padre:
  *Questa funzione reindirizza lo STDIN per leggere dalla pipe, lo STDOU
   per scrivere nel file di output ed infine lancia il secondo comando da eseguire

  - Apro il file di output (se non c'e' lo creo)
  - chiudo l'fd[1] di scrittura della pipe perchè non mi serve
  - reindirizzo l'fd di input rendendo quello della pipe (fd[0]) lo STDIN
  - chiudo fd[0] in quanto reindirizzato
  - rimpiazzo l'fd di output standard (1) con l'fd del file aperto
  - chiudo l'fd del file in quanto reindirizzato
  - chiamo la funzione del comando
*/
static void parent_p(char **argv, char **envp, int *fd)
{
    int fd_file_out;

    fd_file_out = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
    if (fd_file_out == -1)
        quit_free("Error: Unable to open output file\n", NULL, NULL, 1);
    close(fd[1]);
    dup2(fd[0], 0);
    close(fd[0]);
    dup2(fd_file_out, 1);
    close(fd_file_out);
    command(argv[3], envp);
}



int main(int argc, char **argv, char **envp)
{
    int fd[2];
    pid_t pid;

    if (argc == 5)
    {   
        /*Apro la pipe*/
        if (pipe(fd) == -1)
            quit_free("Error: pipe creation failed\n", NULL, NULL, 1);
        
        /*Creo il processo figlio*/
        pid = fork();
        if (pid == -1)
            quit_free("Error encountered during fork call\n", NULL, NULL, 1);

        /*processo figlio*/
        if (pid == 0)
            child_p(argv, envp, fd);        
        
        /*processo padre*/
        else
        {
            waitpid(pid, NULL, 0);
            parent_p(argv, envp, fd);
        }

    }
    else
        quit_free("Error: Ivalid parameters\n", NULL, NULL, 1);
}

