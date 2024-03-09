/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldi-fior <ldi-fior@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 17:23:10 by ldi-fior          #+#    #+#             */
/*   Updated: 2024/02/15 14:57:49 by ldi-fior         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*Funzioni per la gestioni dell'immagine*/
#include "so_long.h"


/*INIT_COIN____________________________________________________________________
- Inizializza le 5 immagini della moneta per tutte le monete presenti in gioco*/
static void init_coin(t_game *p_g)
{ 
    p_g->map.collect[0].img[0] = mlx_xpm_file_to_image(p_g->mlx, "xpm/Coin.xpm",
      &p_g->map.img_width, &p_g->map.img_height);
    p_g->map.collect[0].img[1] = mlx_xpm_file_to_image(p_g->mlx, "xpm/Coin1.xpm",
      &p_g->map.img_width, &p_g->map.img_height);
    p_g->map.collect[0].img[2] = mlx_xpm_file_to_image(p_g->mlx, "xpm/Coin2.xpm",
      &p_g->map.img_width, &p_g->map.img_height);
    p_g->map.collect[0].img[3] = mlx_xpm_file_to_image(p_g->mlx, "xpm/Coin3.xpm",
      &p_g->map.img_width, &p_g->map.img_height);
    p_g->map.collect[0].img[4] = mlx_xpm_file_to_image(p_g->mlx, "xpm/Coin4.xpm",
      &p_g->map.img_width, &p_g->map.img_height);
}


/*INIT_IMAGES__________________________________________________________________
  - estrae il puntatore all'immagine con la funzione mlx_xpm_file_to_image*/
int	init_images(t_game *p_g)
{
  init_coin(p_g);
  /*carico l'immagine dello sfondo*/
  p_g->map.ground.img[0] = mlx_xpm_file_to_image(p_g->mlx, "xpm/ground.xpm", &p_g->map.img_width, &p_g->map.img_height);
  /*carico l'immagine del muro*/
  p_g->map.wall.img[0] = mlx_xpm_file_to_image(p_g->mlx, "xpm/wall2.xpm",
      &p_g->map.img_width, &p_g->map.img_height);
  /*carico l'img del player a dx*/
  p_g->map.player.img[0] = mlx_xpm_file_to_image(p_g->mlx, "xpm/P_dx.xpm",
      &p_g->map.img_width, &p_g->map.img_height);
  /*carico l'img del player a sx*/
  p_g->map.player.img[1] = mlx_xpm_file_to_image(p_g->mlx, "xpm/P_sx.xpm",
      &p_g->map.img_width, &p_g->map.img_height);
  /*carico l'img dell'uscita chiusa*/
  p_g->map.exit.img[0] = mlx_xpm_file_to_image(p_g->mlx, "xpm/E_cl.xpm",
      &p_g->map.img_width, &p_g->map.img_height);
  /*carico l'img dell'uscita aperta*/
  p_g->map.exit.img[1] = mlx_xpm_file_to_image(p_g->mlx, "xpm/E_op.xpm",
      &p_g->map.img_width, &p_g->map.img_height);
  /*carico l'img del nemico a dx*/
  p_g->map.enemy.img[0] = mlx_xpm_file_to_image(p_g->mlx, "xpm/N_dx.xpm",
      &p_g->map.img_width, &p_g->map.img_height);
  /*carico l'img del nemico a sx*/
  p_g->map.enemy.img[1] = mlx_xpm_file_to_image(p_g->mlx, "xpm/N_sx.xpm",
      &p_g->map.img_width, &p_g->map.img_height);
  /*carico l'img della score box*/
  p_g->map.score.img[0] = mlx_xpm_file_to_image(p_g->mlx, "xpm/ground.xpm",
      &p_g->map.img_width, &p_g->map.img_height);

  return (1);    
}


/*PUT_IMAGES__________________________________________________________________
  - Carica le immagini e mostra a schermo con la funzione mlx_put_image_to_window*/
static void put_images(t_game *g, int i, int j)
{
  int   x;
  int   y;

  y = i * g->map.img_height;
  x = j * g->map.img_width;
  /*Senza condizioni questa funzione posizionerà l'img di sfondo su tutta la mappa*/

  mlx_put_image_to_window(g->mlx, g->win, g->map.ground.img[0], x, y);

  /*A seconda della lettera letta posizionerà l'immagine corrispondente
    NOTA: Non mi serve spostarmi nell'array collect. Come immagini
           userò sempre quelle salvate in collect[0]. Gli altri elementi
           di collect non hanno l'elemento immagine popolato, solo le
           posizioni*/
  
  /*immagine della score box*/
  mlx_put_image_to_window(g->mlx, g->win, g->map.score.img[0], 0, 0);
  mlx_put_image_to_window(g->mlx, g->win, g->map.score.img[0], g->map.width * g->map.img_width - 64, 0);
  
  /*mando a schermo gli asset che incontro*/
  if (g->matrix[i][j] == 'C')
    mlx_put_image_to_window(g->mlx, g->win, g->map.collect[0].img[0], x, y);
  else if (g->matrix[i][j] == '1')
    mlx_put_image_to_window(g->mlx, g->win, g->map.wall.img[0], x, y);
  else if (g->matrix[i][j] == 'P')
    mlx_put_image_to_window(g->mlx, g->win, g->map.player.img[0], x, y);
  else if (g->matrix[i][j] == 'E')
    mlx_put_image_to_window(g->mlx, g->win, g->map.exit.img[0], x, y);
  else if (g->matrix[i][j] == 'N')
    mlx_put_image_to_window(g->mlx, g->win, g->map.enemy.img[0], x, y);
}


void  d_score(t_game *p_g)
{
  char  *moves;
  char  *coin;
  char  *c_coin;

  moves = ft_itoa(p_g->n_move);
  coin = ft_itoa(p_g->map.n_coin);
  c_coin = ft_itoa(p_g->map.c_take);
  mlx_put_image_to_window(p_g->mlx, p_g->win, p_g->map.ground.img[0], 0, 0);
  mlx_put_image_to_window(p_g->mlx, p_g->win, p_g->map.ground.img[0], 
    (p_g->map.width) * p_g->map.img_width - 64, 0);
  mlx_string_put(p_g->mlx, p_g->win, (p_g->map.width) * p_g->map.img_width - 64, 
    10, 0x00FFFFFF, "MOVES: ");
  mlx_string_put(p_g->mlx, p_g->win, (p_g->map.width) * p_g->map.img_width - 64, 
    35, 0x00FFFFFF, moves);
  mlx_string_put(p_g->mlx, p_g->win, 25, 10, 0x00FFFFFF, c_coin);
  mlx_string_put(p_g->mlx, p_g->win, 15, 35, 0x00FFFFFF, "/");
  mlx_string_put(p_g->mlx, p_g->win, 25, 35, 0x00FFFFFF, coin);
  free(moves);
  free(coin);
  free(c_coin);
}




/*ON_SCREEN__________________________________________________________________
  - Stampa le immagini a schermo */
int on_screen (t_game *p_g)
{
  int i;
  int j;

  i = -1;
  while (++i < p_g->map.heigth)
  {
    j = -1;
    while (++j < p_g->map.width)
      put_images(p_g, i, j);
  }
  d_score(p_g);
  return (1);  
}

