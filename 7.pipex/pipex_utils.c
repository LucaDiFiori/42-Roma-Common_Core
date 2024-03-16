/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldi-fior <ldi-fior@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 17:20:35 by ldi-fior          #+#    #+#             */
/*   Updated: 2024/03/15 11:51:49 by ldi-fior         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int quit_free(const char *error, char *str, char **mat, int err_type)
{
	int	i;

	/*Stampa un messaggio d errore e esco*/
    if (err_type == 1)
        write (2, error, s_len(error));
	/*Libero una stringa, stampo ed esco*/
	else if (err_type == 2)
	{
		free(str);
		write (2, error, s_len(error));
	}
	/*Libero una matrice, stampo ed esco*/
	else if (err_type == 3)
	{
		i = -1;
		while (mat[++i])
			free(mat[i]);
		free(mat);
		write (2, error, s_len(error));
	}
	/*Libero la stringa, la matrice, stampo ed esco*/
	else if (err_type == 4)
	{
		i = -1;
		free(str);
		while (mat[++i])
			free(mat[i]);
		free(mat);
		write (2, error, s_len(error));
	}
	exit (1); 
}