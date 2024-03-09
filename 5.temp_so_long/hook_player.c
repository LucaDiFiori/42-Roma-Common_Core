/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldi-fior <ldi-fior@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 16:34:53 by ldi-fior          #+#    #+#             */
/*   Updated: 2024/02/15 13:27:40 by ldi-fior         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*FUNZIONI PER MUOVERE IL PERSONAGGIO ED AGGIORNARE LA MAPPA*/
#include "so_long.h"


/*CHECK________________________________________________________________________________________-
 - Verifica cosa c'è nella casella in cui voglio spostarmi e, a seconda del contenuto,
   esegue un azione.
 - restituisce 1 se lo spostamento è valido, 0 se non lo è  
*/
static int	check(t_game *p_g, int x, int y)
{
	/*Se in quella casella ho "1" restituisco 0*/
	if (p_g->matrix[x][y] == '1')                                            		
		return (0);
	
	/*Se in quella casella ho "N" chiudo il gioco*/
	if (p_g->matrix[x][y] == 'N')											 		
	{
		printf(" *******\n*********\n* o * o *\n****A****\n  |!!!| \n");
		quit_and_free("YOU DIED", 3, p_g);
		return (0);
	}
	
	/*Se in quella casella ho "C" chiudo aumento 
	  il numero dei collezionabili raccolti*/
	if (p_g->matrix[x][y] == 'C')										     
	{
		ft_printf("It's free if nobody sees ;)\n");
		p_g->map.c_take++;
	}																				

	/*Se in quella casella ho "E" ma non ho raccolto tutto restituisco 0*/
	if (p_g->matrix[x][y] == 'E' && p_g->map.c_take != p_g->map.n_coin)
	{
		ft_printf("You've forgotten something\n");
		return (0);
	}

	/*Se in quella casella ho "E" ed ho raccolto tutto aumento il count delle mosse
	  e chiudo il gioco*/																		
	else if(p_g->matrix[x][y] == 'E' && p_g->map.c_take == p_g->map.n_coin)
	{
		ft_printf("You complete the game in %d moves\n", ++p_g->n_move);
 		quit_and_free("\n()()\n( ..)\n*(')(')\nBYE!\n", 3, p_g);
	}
	ft_printf("Moves: %d\n", ++p_g->n_move);
	return (1);
}


/*MOVE________________________________________________________________________   //COMPLETTARLA CON LA MODIFICAZIONE DELLE IMMAGINI//NOTA: de commentare fr_bk quando sapro quante immagini ho
- Aggiorna i valori della matrine
- Nota: La variabile fr_bk (front_back) serve a posizionare l'immagine corretta
        (fronte o di spalle) a seconda che il personaggio vada avanti o indietro*/
static void	move(t_game *p_g, int n_x, int n_y, int fr_bk)
{
	/*Nella vecchia posizione di P metto '0' e nella nuova 'P'*/
	p_g->matrix[p_g->map.player.x_axis][p_g->map.player.y_axis] = '0';
	p_g->matrix[n_x][n_y] = 'P';
	mlx_put_image_to_window(p_g->mlx, p_g->win, p_g->map.ground.img[0], 
        (p_g->map.player.y_axis) * 64, (p_g->map.player.x_axis) * 64);
    if (fr_bk == 1)
        mlx_put_image_to_window(p_g->mlx, p_g->win, p_g->map.player.img[1], n_y * 64, n_x * 64);
    else if (fr_bk == 0)
        mlx_put_image_to_window(p_g->mlx, p_g->win, p_g->map.player.img[0], n_y * 64, n_x * 64);
    else if (fr_bk == -1) 
        mlx_put_image_to_window(p_g->mlx, p_g->win, p_g->map.player.img[0], n_y * 64, n_x * 64);  
	d_score(p_g);
}



/*SCRIVERE CHECK_N_MOVE_______________________________________________________
  - Controlla se il movimento e' possibile. Se lo e' modifica la matrice 
  - Restituendo 1 o 0*/
int	check_and_move(t_game *p_g, int key, int x, int y)
{
	if ((key == 13 || key == 126) && check(p_g, x - 1, y))
	{
		move(p_g, x - 1, y, -1);
		return (1);
	}
	else if ((key == 1 || key == 125) &&check(p_g, x + 1, y))
	{
		move(p_g, x + 1, y, -1);
		return (1);
	}
	else if ((key == 2 || key == 124) && check(p_g, x, y + 1))
	{
		move(p_g, x, y + 1, 0);
		return (1);
	}
	else if ((key == 0 || key == 123) && check(p_g, x, y - 1))
	{
		move(p_g, x, y - 1, 1);
		return (1);
	}
	return (0);
}


/*IMPUTS______________________________________________________________________
- A seconda del tasto premuto modifica la matrice (spostando il personaggio)
  e aggiorna le coordinate
- NOTA: La funzione deve essere int perchè sarà quella usata nella funzione hook che,
        da prototipo, richiede il puntatore ad una funzione int
*/
int		inputs(int key, t_game *ptr_game)
{
	int	x;
	int	y;

	x = ptr_game->map.player.x_axis;
	y = ptr_game->map.player.y_axis;
	if (key == 53)
		ft_close_x(ptr_game);             											/*Se premo ESC = 53 esco e libero*/
	if ((key == 13 || key == 126) && check_and_move(ptr_game, key, x, y))
		ptr_game->map.player.x_axis--;	 			 								/*Se premo freccia verso l alto o w sposto le corrdinate di P*/
	if ((key == 1 || key == 125) && check_and_move(ptr_game, key, x, y))
		ptr_game->map.player.x_axis++;	 			 								/*Se premo fraccia verso il basso o s sposto le corrdinate di P*/
	if ((key == 2 || key == 124) && check_and_move(ptr_game, key, x, y))
		ptr_game->map.player.y_axis++;	 			 								/*Se premo fraccia verso dx o d sposto le corrdinate di P*/
	if ((key == 0 || key == 123) && check_and_move(ptr_game, key, x, y))
		ptr_game->map.player.y_axis--;	 			 								/*Se premo fraccia verso sx o a sposto le corrdinate di P*/	
	return (0);
}
