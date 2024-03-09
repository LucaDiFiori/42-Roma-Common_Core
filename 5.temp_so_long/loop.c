#include "so_long.h"


/*NOTA:
La funzione gettimeofday popola una struttura di tipo struct timeval con i valori dei secondi e dei microsecondi. 
Ecco come funziona:

- int gettimeofday(struct timeval *tv, struct timezone *tz);
Con:
tv: è un puntatore a una struttura di tipo struct timeval che verrà popolata con il tempo corrente.
tz: è un puntatore a una struttura di tipo struct timezone, che può essere impostato a 
    NULL se non si desidera ottenere informazioni sul fuso orario.

- La struttura struct timeval ha i seguenti membri:
struct timeval {
    time_t      tv_sec;     // secondi
    suseconds_t tv_usec;    // microsecondi
};

Dopo la chiamata a gettimeofday, la struttura tv conterrà i valori dei secondi e dei microsecondi d
el tempo corrente del sistema.
Per ottenere i millisecondi, la parte dei microsecondi può essere convertita in millisecondi dividendola 
per 1000, poiché 1 secondo equivale a 1000 millisecondi.
*/




/*FT_COIN_________________________________________________________________________________________________________
- aggiungerla

*/



/*FT_TIME_COIN_________________________________________________________________________________________________________
- mi restituisce la differenza in millisecondi fra il tempo corrente e Epoch
*/
static int	ft_time_coin(t_game *p_g)
{
	struct timeval	current_e;
	int 			ret;

	gettimeofday(&current_e, NULL);

	/*Le operazioni servono per convertire i valori in millisecondi ed eseguire poi la differenza*/
	ret = (((current_e.tv_sec * 1000) + (current_e.tv_usec / 1000))
			- (((p_g->time_coin.tv_sec * 1000)) + (p_g->time_coin.tv_usec / 1000)));

	/*Quando la differenza e' di 200 millisecondi aggiorno il valore di time col nuovo valore di current*/
	if (ret >= 200)
		p_g->time_coin = current_e;
	return (ret);		
}

/*FT_TIME_ENEMY_________________________________________________________________________________________________________
- mi restituisce la differenza in millisecondi fra il tempo corrente e Epoch
*/
static int	ft_time_enemy(t_game *p_g)
{
	struct timeval	current_n;
	int 			ret;

	gettimeofday(&current_n, NULL);

	/*Le operazioni servono per convertire i valori in millisecondi ed eseguire poi la differenza*/
	ret = (((current_n.tv_sec * 1000) + (current_n.tv_usec / 1000))
			- (((p_g->time_enemy.tv_sec * 1000)) + (p_g->time_enemy.tv_usec / 1000)));

	/*Quando la differenza e' di 200 millisecondi aggiorno il valore di time col nuovo valore di current*/
	if (ret >= 1000)
		p_g->time_enemy = current_n;
	return (ret);		
}


/*LOOP_COIN_________________________________________________________________________________________________________
- Gestisce il loop delle monete 
*/
int loop_coin(t_game *g)
{
	int	i;

	i = -1;
	if (ft_time_coin(g) >= 200)
	{
		if (g->map.c_take != g->map.n_coin)
		{
			if (g->coin_mov == 4)
				g->coin_mov = 0;
				
			if (g->coin_mov != 4 )	
				g->coin_mov++;
			while (++i <= g->map.n_coin /*&& ft_time_coin(g) >= 200*/)
			{
				if (g->matrix[g->map.collect[i].x_axis][g->map.collect[i].y_axis] == 'C')
				{
					mlx_put_image_to_window(g->mlx, g->win, g->map.ground.img[0], 
						(g->map.collect[i].y_axis) * 64, (g->map.collect[i].x_axis) * 64);
					mlx_put_image_to_window(g->mlx, g->win, g->map.collect[0].img[g->coin_mov], 
						(g->map.collect[i].y_axis) * 64, (g->map.collect[i].x_axis) * 64);

				}
		
			}
		}
		else
			mlx_put_image_to_window(g->mlx, g->win, g->map.exit.img[1], 
						(g->map.exit.y_axis) * 64, (g->map.exit.x_axis) * 64);	
	}
return (1);
}





/*LOOP_ENEMY_________________________________________________________________________________________________________
- Gestisce il loop delle monete e dei nemici
*/
int	loop_enemy(t_game *p_g) /*SE FUNZIONA CHIAMARE QUESTA FUNZIONE LOOP*/
{
	loop_coin(p_g);
	if (ft_time_enemy(p_g) >= 1000)
		is_alive(p_g);

	return (0);	
}