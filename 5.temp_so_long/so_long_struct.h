/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_struct.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldi-fior <ldi-fior@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 11:34:01 by ldi-fior          #+#    #+#             */
/*   Updated: 2024/02/15 15:16:57 by ldi-fior         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*Qui sono contenute le struct necessarie*/

#ifndef SO_LONG_STRUCT_H_H
# define SO_LONG_STRUCT_H_H

/*Numero di coin nel gioco*/
# define NUM_COLLECTABLE 5
# define MAX_XPM 5


typedef struct s_tile
{
	/*Carattere che indichera' che tipo di elemento ho es: muro, personaggio etc*/
	char	tile_type;
	/*Coordinata x del mio asset*/
	int		x_axis;
	/*Coordinata y del mio asset*/
	int		y_axis;
	/*struct contenente le informazioni sullaa skin*/
	void	*img[MAX_XPM];	
}			t_tile;

/*count di player, uscite, coin e nemici*/
typedef struct s_count
{
	int	count_p;                            /*count di player ed uscite*/
	int count_e;
	int	count_c; 
	int count_n;
}	t_count;


typedef struct s_map
{
	/*Contiene il percorso alla cartella "maps" ed il nome della mappa inserito (argv[1]) */
	char	*map_path;
	/*altezza della mappa*/
	int		heigth;
	/*Larghezza della mappa*/
	int		width;
	/*count di player, uscite, coin e nemici*/
	t_count	count;
	/*struct di tipo "tile" per il player*/
	t_tile	player;
	/*struct contenente le info sul nemico*/
	t_tile	enemy;
	/*struct contenente le info sull'scita*/
	t_tile	exit;
	/*struct contenente le info suli muri*/
	t_tile	wall;
	/*struct contenente le info sul pavimento*/
	t_tile	ground;
	/*struct contenente le info sullo score*/
	t_tile	score;
	/*array di struct contenenteile info sugli n collectable*/
	t_tile	collect[NUM_COLLECTABLE];
	/*Numero di collezionabili presenti sulla mappa*/
	int		n_coin;
	/*Numero di collezionabili raccolti*/
	int		c_take;
	/*Dimensioni delle immagini*/
	int		img_width;
	int		img_height;
}		t_map;

/*Questa atruct contiene i puntatori e variabili fondamentali del gioco*/
typedef struct	s_game
{
	/*puntatore all'ambiente grafico*/
	void	*mlx;
	/*puntatore alla finestra di gioco*/
	void	*win;
	/*var. che contiene le info sulla mappa*/
	t_map	map;
	/*matrice*/
	char	**matrix;
	/*Numero di mosse*/
	int		n_move;
	/* per la velocità delle animazioni */
	struct timeval	time_coin;
	struct timeval	time_enemy;
	/*movimenti della moneta*/
	int		coin_mov;
}				t_game;

#endif