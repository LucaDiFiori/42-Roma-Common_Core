/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldi-fior <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 10:26:10 by ldi-fior          #+#    #+#             */
/*   Updated: 2024/03/20 15:19:52 by ldi-fior         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
 - controlla se argv[1] == "here_doc"
   * In caso lo sia: - nel FILE DI INPUT apre (e crea) un file temporaneo le cui
                       informazioni verranno rimpiazzate ad ogni scrittura

 - Se non lo e' = apro argv[1] in modalita' sola lettura
 - restituisce l'fd del file aperto
*/
int fd_open_input(char **argv)
{
    int fd_in;

    if (ft_strncmp("here_doc", argv[1], 8) == 0)
        fd_in = open(".temp", O_RDWR | O_CREAT | O_TRUNC, 0777);
    else
        fd_in = open(argv[1], O_RDONLY, 0777);
    if (fd_in == -1)
        quit_free("Error: Unable to open input file\n", NULL, NULL, 1);
    return (fd_in);
}

/*
 - controlla se argv[1] == "here_doc"
   * In caso lo sia: - nel FILE DI OUTPUT apre (e crea) un file (ultimo argv) 
                       le cui informazioni verranno appese ad ogni scrittura

 - Se non lo e' = apro (e creo) l'ultimo argv in modalita' sola scrittura le cui
   informazioni verranno rimpiazzate ad ogni scrittura
 - restituisce l'fd del file aperto
*/
int fd_open_output(char **argv, int argc)
{
    int fd_out;

     if (ft_strncmp("here_doc", argv[1], 8) == 0)
        fd_out = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0777);
    else
        fd_out = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
    if (fd_out == -1)
        quit_free("Error: Unable to open output file\n", NULL, NULL, 1);
    return (fd_out);
}

void    dup_and_close(int fd_to_dup, int fd_needed)
{
    if (dup2(fd_to_dup, fd_needed) == -1)
        quit_free("Error: in dup2 function\n", NULL, NULL, 1);
    if (close(fd_to_dup) == -1)
        quit_free("Error: in close function\n", NULL, NULL, 1);;   
}
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (*s1 && *s2 && i < (n - 1) && *s1 == *s2)
	{
		s1++;
		s2++;
		i++;
	}
	return ((unsigned char)(*s1) - (unsigned char)(*s2));
}