/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldi-fior <ldi-fior@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 15:52:27 by ldi-fior          #+#    #+#             */
/*   Updated: 2024/01/26 18:31:13 by ldi-fior         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*PRINT ERROR_________________________________________________________________________
Stampa l'errore*/
void	print_error(char *s)
{
	ft_printf("Error: %s\n", s);
}
/*_____________________________________________________________________________________*/


/*FREE_MAP_MATRIX______________________________________________________________________
Libera la matrice in caso di errore*/
void	free_map_matrix(char **ptr_map, t_game *ptr_game)
{
	int	i;
	
	i = 0;
	while(i < ptr_game->map.heigth)         /*Libera ogni puntatore della stringa di puntatore*/
	{
		free(ptr_map[i]);
		i++;
	}
	free(ptr_map);            /*libero la stringa di puntatori*/
}
/*_____________________________________________________________________________________*/


/*QUIT_AND_FREE_________________________________________________________________________*/
/*Questa funzione: - stampa l'errore
                - a seconda del numero passatole esegue una funzione di pulizia diversa
				- ritorna 0*/
int	quit_and_free(char *error, int err_type, t_game *ptr_game)
{
	if (err_type == 1)
		print_error(error);
	else if (err_type == 2)
	{
		free_map_matrix(ptr_game -> matrix, ptr_game);
		print_error(error);
	}
	else if (err_type == 3)  
	{
		free_map_matrix(ptr_game -> matrix, ptr_game);
		ft_printf("%s", error);
		ft_destroy(ptr_game);
                                  /*Il caso 3 si verifica quando decido di uscire*/
	}
	exit (0);  /*In qualunque punto viene chiamata "exit" chiude il programma*/
}
/*_____________________________________________________________________________________*/




/*FT_CLOSE_X_________________________________________________________________________*/
/*Questa funzione serve per chiamare quit_and_free con il paramentro 3 (mi serve 
  altrimenti non chiude bene quando premo la x sulla finestra)*/
int ft_close_x(t_game *ptr_game)
{
	quit_and_free("See U <3", 3, ptr_game);
	return (0);
}
/*_____________________________________________________________________________________*/





/*FT_DESTROY_______________FINIRE________________________________________________________________
Usa le funzioni destroy di mlx*/     
void	ft_destroy(t_game *ptr_game)
{
	if (ptr_game->win)
		mlx_destroy_window(ptr_game->mlx, ptr_game->win);  /*Se la finestra esistedistruggila*/

    /*METTERE I DESTROY DELLE IMMAGINI */
}