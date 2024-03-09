/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldi-fior <ldi-fior@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 17:42:13 by ldi-fior          #+#    #+#             */
/*   Updated: 2024/02/15 15:17:23 by ldi-fior         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*Queste funzioni inizializzano le variabili e lanciano il gioco*/
#include "so_long.h"

/*SET_VAR_TO_ZERO______________________________________________________________________________
- inizializza tutte le variabili e puntatori a zero o NULL.
- NOTA: Questo perche' se dovessi fare free su un puntatore non inizializzato avrei un comportamento
  		  indefinito*/
int	set_var_to_zero(t_game *ptr_t_game)
{
	ptr_t_game -> mlx = NULL;
	ptr_t_game -> win = NULL;
	ptr_t_game -> map.map_path = NULL;
	ptr_t_game -> map.heigth = 0;
	ptr_t_game -> map.width = 0;
	ptr_t_game -> matrix = NULL;
	ptr_t_game -> map.n_coin = 0;
	ptr_t_game -> map.c_take = 0;
	ptr_t_game -> n_move = 0;
	ptr_t_game -> map.count.count_c = 0;
	ptr_t_game -> map.count.count_e = 0;
	ptr_t_game -> map.count.count_n = 0;
	ptr_t_game -> map.count.count_p = 0;
	ptr_t_game -> map.img_height = 64;
	ptr_t_game -> map.img_width = 64;
	ptr_t_game ->coin_mov = 0;
	gettimeofday(&(ptr_t_game->time_coin), NULL);
	gettimeofday(&(ptr_t_game->time_enemy), NULL);
	return (1);
}





/*LAUNCH_WINDOWS______________________________________________________________________________
- inizializza L'ambiente e la finestra di gioco.
- gestisce tutti i loop
*/
int	launch_game(t_game *ptr_t_game)
{
	ptr_t_game -> mlx = mlx_init(); 		                                   			 	 /* - La funzione mlx_init() inizializza la libreria <mlx.h> e va chiamata 
	  																				 		      prima di ogni altra funzione.*/
	if (!ptr_t_game -> mlx)
		quit_and_free("MLX initialization failed", 1, ptr_t_game); 			  				 /*  - restituisce un puntatore a void:
	  										  									  				 - La variabile mlx conterrà un puntatore al contesto grafico inizializzato 
																								   dalla funzione mlx_init().  
																								   Il puntatore a questo contesto può essere utilizzato per 
												 												   interagire con la libreria, creare finestre, gestire eventi etc*/


	/*Inizializzo la finestra di gioco*/
	ptr_t_game -> win = mlx_new_window(ptr_t_game -> mlx,
		(ptr_t_game -> map.width) * 64, (ptr_t_game -> map.heigth) * 64,"So Long");   	 
	if (!ptr_t_game -> win)
		quit_and_free("Windows initialization failed", 1, ptr_t_game);   					/*	- Questa fuznione ha come argomenti il puntatore al contesto 
																						   		  grafico, il secondo e terzo argomento rappresentano la 
																								  dimensione in pixel e l' ultimo il una stringa che rappresenta 
																								  il titolo della finestra*/
  
    

	/*funzione che carica le immagini*/
    init_images(ptr_t_game);
	/*funzione che disegna la mappa a schermo*/
	on_screen(ptr_t_game);


   	/*In questo modo vacevo muovere il nemico da solo*/
	if (ft_strncmp(ptr_t_game->map.map_path, "maps/bonusmap.ber") == 0 
		|| ft_strncmp(ptr_t_game->map.map_path, "maps/bonusmap2.ber") == 0)
		mlx_loop_hook(ptr_t_game -> mlx, *loop_enemy, ptr_t_game);
	else
		 mlx_loop_hook(ptr_t_game -> mlx, *loop_coin, ptr_t_game);	
	


	mlx_key_hook(ptr_t_game->win, *inputs, ptr_t_game);        								/*Questa riga imposta una funzione di callback denominata "imputs"" che verrà */
		/*FINIREEEEE IMPUTSSSS*/							    							/*  chiamata quando  verificano eventi di pressione di tasti nella finestra specificata 
																    							(ptr_t_game->win). 
                																				La funzione imputs e' responsabile di gestire gli input da tastiera.
               													    							(resta in attesa che un tasto venga premuto e, quando viene premuto esegue "inputs" 
																								(funzione che controlla che tasto e' e, a seconda del tasto che ho premuto, fa qualcosa))*/

    


	
	mlx_hook(ptr_t_game->win, 17, 0, *ft_close_x, ptr_t_game);   							/*Questa funzione chiude il gico se premo x sulla finestra*/

	mlx_loop(ptr_t_game -> mlx);      
	return (1);                            													/*La funzione mlx_loop inizia il rendering della finestra mantenendola aperta 
	  											 											  finche non premo ctrl-c.
	  											  											  La funzione ha come argomento il puntatore al contesto grafico */
}