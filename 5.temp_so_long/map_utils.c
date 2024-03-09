/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldi-fior <ldi-fior@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 15:52:27 by ldi-fior          #+#    #+#             */
/*   Updated: 2024/02/13 14:33:50 by ldi-fior         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*FUNZIONE CHE VERIFICA SE I FILE MAPPA ABBIANO L'ESTENSIONE .BER___________________________________________________*/
int	check_ber_file(char *path, t_game *ptr_game)
{
	int	len;

	len = ft_strlen(path);
	if (path[len - 1] == 'r' && path[len - 2] == 'e'
		&& path[len - 3] == 'b' && path[len - 4] == '.')
		{
			ptr_game->map.map_path = path;
			return (1);
		}
	else
		return (quit_and_free("Invalid file extension", 1, ptr_game));
}
/*____________________________________________________________________________________________________________________*/


/*CHECK_CHAR______________________________________________________________________________
  Questa funzione controlla: - se il carattere della matrice passatole è valido  
  
  PARAMETRO: Matrice
  RETURN: 1 se valido, 0 se non valido*/
  int	check_char(char c)
  {
	if (c == '0' || c == '1' || c == 'P' || c == 'E' || c == 'C' || c == 'N')
		return (1);
	return (0);	
  }
  /*____________________________________________________________________________________________________________________*/


  /*QUESTA FUNZIONE RACCOGLIE LE ALTRE FUNZIONI DI CONTROLLO E RESTITUISCE 1 SOLO IN CASO DI SUCCESSO____________________
  NOTA: Ho implementato questa funzione cosi chè, al primo controllo non valido, gli step successivi alla generazione
        della matrici vengano interrotti
		- Parte dal controllare il numero di elementi P, E e C. 
		- Solo nel caso in cui questi valori siano validi procederà chiamando la funzione "check_map_and_set_tyle"
		- E solo se anche questo controllo viene superato chiamerà la funzione per il controllo del percorso. 
*/
int	matrix_complete_checker(t_game *ptr_game)
{
	if (!p_e_c_n_count(ptr_game))
		return (0);
	else if(!check_map_and_set_tyle(ptr_game))
		return (0);
	else if (!check_path(ptr_game))
		return (0);
	else 
		return (1);	
}
 /*____________________________________________________________________________________________________________________*/



int	ft_strncmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (*s1 && *s2 && (*s1 == *s2))
	{
		s1++;
		s2++;
		i++;
	}
	return ((unsigned char)(*s1) - (unsigned char)(*s2));
}



/*RANDOM_N____________________________________________________________-
  - Restituisce un numero casuale nel range (min, max)
*/
int random_n(int min, int max) 
{
    return (min + rand() % (max - min + 1));
}