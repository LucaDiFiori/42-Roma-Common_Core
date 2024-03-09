/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldi-fior <ldi-fior@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 11:16:34 by ldi-fior          #+#    #+#             */
/*   Updated: 2024/02/12 17:44:47 by ldi-fior         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*FUNZIONI DI CONTROLLO SULLA MAPPA*/
#include "so_long.h"

/*____________ORDINE DELLE FUNZIONI__________________________________________________________
1) check_mapsize: Legge il file, esegue controlli preliminari e riempie i parametri di altezza 
				  e lunghezza della matrice
2) matrix_generator: genera la matrice
3) matrix_complete_checker: Chiamata nel "return" di "matrix_generator". Questa funzione 
							chiamerà in ordine le successive
4) p_e_c_count
5) check_map_and_set_tyle
6) check_path (contenuta in path.c)
____________________________________________________________________________________________*/ 




/*CONTROLLO SULLA FORMA DELLA MAPPA___________________________________________________________________________________
  - riempie i parametri altezza e lunghezza della variabile struct
     map contenuta nella struct t_game 
  PARAMETRI:
  1) percorso mappa 
  2) puntatore alla variabile struct t_game che gli passero'
  
  RETURN
  restituisce 1 se la mappa e' valida -1 se non lo e'*/
int	check_mapsize(t_game *ptr_game, char *m_path)
{
	int		fd;
	int		width_map;
	char	*map_line;
	
	
	check_ber_file(m_path, ptr_game);              						 /*Inizializzo l'elemento percorso dell'elemento t_map 
	                                                 					  della mia variabile struct t_game passata come argomento*/

	fd = open(m_path, O_RDONLY);                    					 /*Apro il file mappa indicato*/
	
	if (fd < 0)                             							 /*Stampo errore se fd < 0*/
		return(quit_and_free("file opening error", 1, ptr_game)); 
	
	map_line = get_next_line(fd);          								 /*Estraggo la prioma linea dal file mappa e controllo*/
	
	if (!map_line[0] || !map_line )         	   						 /*Se non esiste nessuna riga o ne esiste una ed e' vuota esci*/
		return(quit_and_free("Empty map file", 1, ptr_game)); 
	
	ptr_game->map.width = ft_strlen(map_line) - 1; 					/*Inserisco la lunghezza nella mia struct. "-1" perche' 
	                                                  					  l'ultimo carattere e "\n"
	                                                   					  Questa verra' usata come lunghezza di controllo 
													   					  per le altri righe*/
	
	/*CICLO WHILE:
	  - Nelle condizioni mando avanti il contatore dell'altezza avendo gia' estratto una linea:
	  ++ptr_game -> map.heigth (++ perche' una linea l ho gia' estratta)*/  

	while (map_line && ++ptr_game -> map.heigth)
	{	
		width_map = ft_strlen(map_line);
		
		if (map_line[width_map - 1] == '\n')
			width_map--;                    							 /*Questo if mi serve perche' ogni riga estratta finira' con "../n/0". 
			                                  		 					   Lo /0 e' gia' non contato a strlen, e tolgo anche -1 per lo /n.
											  		  					   L'ultima riga estratta pero' non avra' lo /n. 
											   		  					   Quindi gli dico di togliere 1 solo quando lo incontra*/

		free(map_line);												/*Faccio il free su map_line perche' ho estratto le info che mi servono*/
		

		if (width_map != ptr_game->map.width) 	
			return(quit_and_free("invalid map shape", 1, ptr_game)); 		/*Se la lunghezza che ho calcolato e' 
		                                          	             		  diversa dalla prima estratta ho un errore*/
		map_line = get_next_line(fd); 								    /*estraggo una nuova linea*/
	}		
	close(fd);
	return (1);
}
/*____________________________________________________________________________________________________________________*/




/*FUNZIONE DI SUPPORTO A P_E_C_COUNT*/
static int p_e_c_n_support(t_game *game)
{
	/*Se uno dei valori p, e o c non e' valido, stampo l errore e libero il buffer della 
	matrice e tutte le stringhe che contiene*/
	if (game->map.count.count_p != 1)                         
		return(quit_and_free("invalid number of player", 2, game));
	else if ((ft_strncmp(game->map.map_path, "maps/bonusmap.ber") == 0) 
		&& (game->map.count.count_n != 1))                         
		return(quit_and_free("invalid number of enemy", 2, game));
	else if (game->map.count.count_e != 1)                
		return(quit_and_free("invalid number of exit", 2, game));
	else if (game->map.count.count_c > NUM_COLLECTABLE)                         
		return(quit_and_free("to many collectables on map", 2, game));
	else 
		return (1);	 /*Se i count sono validi ritorno 1*/
}
/*____________________________________________________________________________________________________________________*/





/*CONTROLLO SULLA PRESENZA DI ELEMENTI RIPETUTI NELLA MAPPA___________________________________________________________
  - Legge gli elementi della matrice e controlla se ci siano elementi ripetuti
  
  PARAMETRI:
  puntatore alla variabile struct t_game che gli passero' 
  
  RETURN:
  1 se valida 0 se non valida
  */
int	p_e_c_n_count(t_game *game)
{
	int	i;
	int	j;                          /*count per i collezionabili*/

	i = -1;
	while(++i < game->map.heigth)             /*NOTA: Dato che la matrice non ha il terminatore nullo, non posso scrivere i cicle normalmente*/
	{
		j = -1;
		while(++j < game->map.width) 
		{
			if (game->matrix[i][j] == 'P')       
				game->map.count.count_p++;                                                /*Se incontro una P aumento il contatore*/
			else if(game -> matrix[i][j] == 'E')                          /*Se incontro una E aumento il contatore*/
				game->map.count.count_e++; 																  
			else if (game->matrix[i][j] == 'C')
				game->map.count.count_c++; 	                                               /*Se incontra C aumenta il contatore*/
			else if (game->matrix[i][j] == 'N')
				game->map.count.count_n++; 	
		}									
	}

	/*Se uno dei due valori non e' valido, stampo l errore e libero il buffer della 
	  matrice e tutte le stringhe che contiene altrimenti restituisco 1*/
    return (p_e_c_n_support(game));
}
/*____________________________________________________________________________________________________________________*/





/*ESEGUE ALTRI CONTROLLI SULLA MAPPA E POSIZIONE LE TILE______________________________________________________________
- Controlla che il perimetro sia composto da "1" 
- Controlla che non siano presenti caratteri non validi (attraverso la funzione "check_char")                 
- Dopo avere effettuato i controlli chiama, su ogni posizione della matrice, la funzione 
  "set_tile_location" per salvare le posizioni degli elementi nella struct
- NOTA: In questa fase verrà anche effettualto il controllo sul numero di collezionabili presenti sulla mappa*/
int	check_map_and_set_tyle (t_game *ptr_game)
{
	int	i;
	int	j;

	i = -1;
	while(++i < ptr_game->map.heigth)                              			     /*Finchè la matrice esiste*/
	{
		j = -1;
		while (++j < ptr_game->map.width)                             		     /*finchè ogni stringa esiste*/
		{
			if (ptr_game -> matrix[i][j] != '1' && (i == 0 || j == 0 
				|| i == ptr_game -> map.heigth - 1  || j == ptr_game -> map.width - 1))
				return (quit_and_free("Invalid Map Walls", 2, ptr_game));        /*Attraverso questo "if" controllo che 
																				   i muri della mappa siano composti da "1".*/
			
			else if (!check_char(ptr_game -> matrix[i][j]))
				return (quit_and_free("Invalid Character On Map", 2, ptr_game)); /*Controllo i carattere presenti sulla mappa*/

			else if (ptr_game -> matrix[i][j] == 'P')
				set_tile_location(ptr_game, 'P', i, j);                          /*Salvo la posizione del player*/

			else if (ptr_game -> matrix[i][j] == 'E')                            /*Salvo la posizione del'uscita*/
				set_tile_location(ptr_game, 'E', i, j);

			else if (ptr_game -> matrix[i][j] == 'C') 
				set_tile_location(ptr_game, 'C', i, j);
			
			else if (ptr_game -> matrix[i][j] == 'N') 
				set_tile_location(ptr_game, 'N', i, j);		
		} 
	}
	return (1);
}
/*_________________________________________________________________________________________________________________________________*/







/*FUNZIONE PER GENERARE LA MATRICE DAL FILE:__________________________________________________________________________
  - Legge una linea per volta dal file e riempie la matrice 
  
  PARAMETRI:
  1) percorso mappa 
  2) puntatore alla variabile struct t_game che gli passero' 
  
  RETURN
  1 se la mappa è stata generata, 0 altrimenti*/
int matrix_generator(t_game *ptr_game, char *m_path)
{
    int     fd;
    char    *map_line;
    int     i;

    if(!check_mapsize(ptr_game, m_path))
        return(0);
    ptr_game->matrix = (char **)malloc(sizeof(char *) * ptr_game->map.heigth); /*Alloco memoria per la matrice (Oss: il numero esatto di righe senza spazio per il NULL)*/
    if(!ptr_game->matrix)
        return(quit_and_free("Matrix allocation failed", 1, ptr_game));

    fd = open(m_path, O_RDONLY);                      /*Apro il file della mappa*/
    if(!fd)
        return(quit_and_free("File non found", 1, ptr_game));

    map_line = get_next_line(fd);                     /*Estraggo la prima linea dal file*/
    if(!map_line)
       return(quit_and_free("Function get_next_line failure", 1, ptr_game)); 

    i = -1;

    /*CICLO WHILE: - La condiznione sarà sull'esistenza della linea estratta.
                     Con g_n_l continuo ad estrarre righe dal file fino a che 
                     non estrarrò piu' nulla (avengo cosi come lettura un "\0"
                     ed il ciclo terminerà)*/
    while(map_line)
    {
        map_line[ptr_game->map.width] = '\0';        /*Termino la stringa estratta con \0:
                                                         G_n_l estra stringhe terminate con \n.
                                                         Andrò quindi ad inserire nella posizione
                                                         [ptr_game -> map.width], calcolata in precedeza
                                                         come la lunghezza della riga del file rimossa
                                                         la new line, il terminatore nullo */
        
        ptr_game->matrix[++i] = map_line;           /* Inserisco la stringa nella matricd*/

        map_line = get_next_line(fd);                   /*Estraggo una nuova linea dal file*/                                                  
    }

    //ptr_game -> matrix[i] = 0;                          /*Termino la matrice*/
	close(fd);
	return(matrix_complete_checker(ptr_game));            /*NOTA: Questa funzione avrà come output 0 o 1 a seconda
	     													   che l'allaocazione della matrice sia riuscita o meno
															   In caso restiuisse "0" saprei che la deallocazione
															   è stata eseguita dalle varie funzioni di controllo
															   chiamate, una alla volta, nella funzione 
															   "matrix_complete_checker" */
}
/*____________________________________________________________________________________________________________________*/