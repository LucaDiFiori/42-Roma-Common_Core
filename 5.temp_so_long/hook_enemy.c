/*FUNZIONI PER FAR MUOVERE IL NEMICO*/
#include "so_long.h"

/*CH____________________________________________________________-
   - Verifica cosa c'è nella casella in cui voglio spostarmi e, 
     a seconda del contenuto,esegue un azione.
   - restituisce 1 se lo spostamento è valido, 0 se non lo 
*/
static  int ch(t_game *p_g, int x, int y)
{
    if (p_g->matrix[x][y] == 'E')
        return (0);
    if (p_g->matrix[x][y] == 'C')
        return (0);
    else if (p_g->matrix[x][y] == 'P')											 		
	{
		printf(" *******\n*********\n* o * o *\n****A****\n  |!!!| \n");
		quit_and_free("YOU DIED", 3, p_g);
		return (0);
	}
    if (p_g->matrix[x][y] == '0')
        return (1);
    
    return (0);  		
}



/*MV________________________________________________________________________   //COMPLETTARLA CON LA MODIFICAZIONE DELLE IMMAGINI//NOTA: de commentare fr_bk quando sapro quante immagini ho
- Aggiorna i valori della matrine
- Nota: La variabile fr_bk (front_back) serve a posizionare l'immagine corretta
        (fronte o di spalle) a seconda che il personaggio vada avanti o indietro
*/
static void mv(t_game *p_g, int n_x, int n_y, int fr_bk)
{
    p_g->matrix[p_g->map.enemy.x_axis][p_g->map.enemy.y_axis] = '0';
    p_g->matrix[n_x][n_y] = 'N';
    mlx_put_image_to_window(p_g->mlx, p_g->win, p_g->map.ground.img[0], 
            (p_g->map.enemy.y_axis) * 64, (p_g->map.enemy.x_axis) * 64);
    if (fr_bk == 1)
        mlx_put_image_to_window(p_g->mlx, p_g->win, p_g->map.enemy.img[1], n_y * 64, n_x * 64);
    else if (fr_bk == 0)
        mlx_put_image_to_window(p_g->mlx, p_g->win, p_g->map.enemy.img[0], n_y * 64, n_x * 64);
    else if (fr_bk == -1) 
        mlx_put_image_to_window(p_g->mlx, p_g->win, p_g->map.enemy.img[0], n_y * 64, n_x * 64);   
}



/*CH_IF_ALV____________________________________________________________-
  - Controlla se il movimento e' possibile. Se lo e' modifica la matrice 
  - Restituendo 1 o 0
*/
static  int ch_if_alv(t_game *p_g, int rand_n, int x, int y)
{
    if (rand_n == 0 && ch(p_g, x - 1, y))
    {
        
		mv(p_g, x - 1, y, -1);
		return (1);
	}
    else if (rand_n == 1 && ch(p_g, x + 1, y))
	{
        mv(p_g, x + 1, y, -1);
		return (1);
	}
    
    /*Muovo a destra*/
    else if (rand_n == 2 && ch(p_g, x, y + 1))
	{
		mv(p_g, x, y + 1, 0);
		return (1);
	}

    /*Muovo a sinistra*/
    else if (rand_n && ch(p_g, x, y - 1))
	{
		mv(p_g, x, y - 1, 1);
		return (1);
	}
    return (0);
}

/*CH_IF_ALV____________________________________________________________-
  - A seconda del numero casuale uscito modifica la matrice (spostando il nemico)
    e aggiorna le sue coordinate
*/
int is_alive(t_game *p_g)
{
    int rand_n;
    int x;
    int y;

    rand_n = random_n(0, 3);
    x = p_g->map.enemy.x_axis;
    y = p_g->map.enemy.y_axis;

 
    /*Se il numero generato è 0 in nemico si muoverà verso l'alto*/
    if (rand_n == 0 && p_g->matrix[x - 1][y] != '1' && p_g->matrix[x - 1][y] != 'C'
        && ch_if_alv(p_g, rand_n, x, y))
        p_g->map.enemy.x_axis--;
            
    /*Se il numero generato è 1 in nemico si muoverà verso il basso*/
    else if (rand_n == 1 && p_g->matrix[x + 1][y] != '1' && p_g->matrix[x + 1][y] != 'C' 
        && ch_if_alv(p_g, rand_n, x, y))
        p_g->map.enemy.x_axis++;
                
    /*Se il numero generato è 2 in nemico si muoverà verso dx*/
    else if (rand_n == 2 &&  p_g->matrix[x][y + 1] != '1' &&  p_g->matrix[x][y + 1] != 'C' 
        && ch_if_alv(p_g, rand_n, x, y))
        p_g->map.enemy.y_axis++;
            
    /*Se il numero generato è 3 in nemico si muoverà verso sx*/
    else if (rand_n == 3 && p_g->matrix[x][y - 1] != '1' &&  p_g->matrix[x][y - 1] != 'C'
        && ch_if_alv(p_g, rand_n, x, y))
        p_g->map.enemy.y_axis--;
        

    /*"se non funziona mettere on_sceen qui"*/   
    print_matrix(p_g);  /****************************CANCELLARE**************************/


    return (0);        
}