/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldi-fior <ldi-fior@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 12:54:44 by ldi-fior          #+#    #+#             */
/*   Updated: 2024/02/13 13:33:25 by ldi-fior         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*FUNZIONI PER CONTROLLARE LA VALIDITA' DEL PERCORSO*/

/*QUESTA FUNZIONE DUPLICA LA MATRICE________________________________________________________________________________________________________
  Per verificare che il percorso sia valida devo modificare i valori contenuti 
  allínterno della matrice. Per questo motivo avro' bisogno di farne una 
  copia
*/
char	**matrix_duplicator(t_game *ptr_game)
{
	char	**mat_duplicate;
	int		i;

	i = -1;
	mat_duplicate = (char **)malloc(sizeof(char *)
			* ptr_game -> map.heigth);         /*Alloca memoria per la matrice duplicata.
													 Essenso una stringa di puntatori dovro'
													 allocare "height" posizioni (una per 
													 ogni puntatore, o linea di mappa, presente)*/
	while (++i < ptr_game->map.heigth)
		mat_duplicate[i] = ft_strdup(ptr_game -> matrix[i]);
	return (mat_duplicate);
}
/*___________________________________________________________________________________________________________________________________________*/



/*QUESTA FUNZIONE CONTROLLA RICORSIVAMENTE OGNI POSIZIONE DELLA MATRICE, 
  SETTANDO AD "1" LA POSIZIONE CORRISPONDENTE NELLA MATRICE DUPLICATA PARTENDO
  DALLA POSIZIONE DI PARTENZA DEL PLAYER_______________________________________________________________________________________________________
  
  NOTA: Attraverso questo metodo potro' controllare successivamente se le posizioni
        da raggiungere sono accessibili al giocator (e quindi se la mappa 
		rosilta valida)
  
  LOGICA: Andro' a riempire la matrice duplicata di 1 partendo dalla posizione del player
          e spostandomi a sinistra, destra, su e giu'.
          Controllero' poi le posizioni che voglio raggiungere (ad esempio la posizione della E),
		  se "E" e' diventato "1" significato che puo' essere raggiunto
  */
void	trace_all_path(t_game *ptr_game, int x, int y, char **traced_path)
{
/*VECCHIA VERSIONE
	if (x >= 0 && x < ptr_game -> map.heigth && y >= 0 && 
		y < ptr_game -> map.width && (ptr_game -> matrix[x][y] == '0'
		|| ptr_game -> matrix[x][y] == 'C' || ptr_game -> matrix[x][y] == 'E') 
		&& traced_path[x][y] != '1' && traced_path[x][y] != 'N')
		traced_path[x][y] = '1'; */



	if (x >= 0 && x < ptr_game -> map.heigth - 1 && y >= 0 && y < ptr_game->map.width - 1 
		&& (ptr_game -> matrix[x][y] == '0'|| ptr_game -> matrix[x][y] == 'C' 
		|| ptr_game -> matrix[x][y] == 'E') && traced_path[x][y] != '1' && traced_path[x][y] != 'N')
		traced_path[x][y] = '1';                  /* CONDIZIONI DELLÍF:
												   -  x > 0 && x < ptr_game -> map.width && y > 0 && 
												      y < ptr_game -> map.heigth: 
													  Questa condizione verifica che la posizione che 
													  andro' a modificare sui trova all'interno dei muri
												    	                     &&
												   - (ptr_game -> matrix[x][y] == '0' 
												      || ptr_game -> matrix[x][y] == 'E' 
													  || ptr_game -> matrix[x][y] == 'E'):
													  Questa condizione assicura che adro' a modificare soli
													  le posizioni contenenti "1", "E" e "C"
													                          &&
												   - traced_path[x][y] != '1'
												     Se ho gia' modificato un valore passo oltre

													 Quando queste condizioni sono ferificate modifico 
													 la posizione in cui mi trovo assegnandole "1"*/
		
	if (traced_path[x + 1][y] != '1' && traced_path[x + 1][y] != 'P')
		trace_all_path(ptr_game, x + 1, y, traced_path);                   /*Mi Sposto a destra:
																			 Se la posizione a destra rispetto a quella di partenza,
																			 nella matrice duplicata, trovo un valore diverso da 1, 
																			 e dal Player, allora richiamo la funzione spostandomi 
																			 di una posizione sull'asse x
																			 
																			 NOTA: necessito anche della condizione traced_path[..][..] != 'P'
																			       perche' altrimenti non funzionerebbe una mappa fatta 
																				   in questo modo:  |C|P|E|*/
	
	if (traced_path[x][y + 1] != '1' && traced_path[x][y + 1] != 'P')    							/*Mi Sposto in alto */
		trace_all_path(ptr_game, x, y + 1, traced_path);
	
	if (traced_path[x - 1][y] != '1' && traced_path[x - 1][y] != 'P') 							   /*Mi Sposto a sonistra */
		trace_all_path(ptr_game, x - 1, y, traced_path);
	
	if (traced_path[x][y - 1] != '1' && traced_path[x][y - 1] != 'P')    						   /*Mi Sposto in basso */
		trace_all_path(ptr_game, x, y - 1, traced_path);

}
/*_____________________________________________________________________________________________________________________________________________*/


/*FUNZIONE AUSILIARIA CHE CONTROLLA SE I COLLEZIONABILI SIANO RIAGGIUNGIBILI 
  - Controlla se nelle posizioni di ciascuna moneta sia stato sostituito '1' a 'C'
  - e nella posizione in cui si trova la moneta i-esima non trovo "1"
	significa che il percorso non e' valido. Libero quindi la matrice duplicata
	e quella original*/
static int	check_coin(t_game *ptr_game, char **trace_path)
{
	int	i;

	i = -1;
	while (++i < ptr_game->map.n_coin)
	{
		if (trace_path[ptr_game->map.collect[i].x_axis][ptr_game->map.collect[i].y_axis] != '1')
		return (0);
	}
	return (1);
}


/*FUNZIONE CHE VERIFICA LA PRESENZA DI UN PERCORSO VALIDO SULLA MAPPA________________________________________________________
  - Alloco un array di struct di tipo tile in cui salvero' la posizione degli zeri
  - Verifico (mediante le altre funzioni) se la E e le C sono state sostituite con '1'
    e risultabo quindi raggiungibili */
int	check_path(t_game *ptr_game)
{
	char	**traced_path;

	traced_path = matrix_duplicator(ptr_game);             /*Duplico la matrice*/
	
	
	trace_all_path(ptr_game, ptr_game -> map.player.x_axis, 
		ptr_game -> map.player.y_axis, traced_path);       /*Chiamo la funzione trace_all_path*/



	if (!check_coin(ptr_game, traced_path))
	{
		free_map_matrix(traced_path, ptr_game);
		quit_and_free("Path not valid", 2, ptr_game);
	}       									                 /*controllo sulle monete */
	if (traced_path[ptr_game->map.exit.x_axis]              /*Controllo se la "E" non e' stata raggiunta dalla funzione "trace_all_path"*/
			[ptr_game->map.exit.y_axis] != '1')
	{
		free_map_matrix(traced_path, ptr_game);
		quit_and_free("Path not valid", 2, ptr_game);
	}	
	free_map_matrix(traced_path, ptr_game); 	            /*Se non sono uscito prima significa che il percorso e' valida e posso
													         liberare la matrice duplicata*/	 
	
	return (1);		
}  