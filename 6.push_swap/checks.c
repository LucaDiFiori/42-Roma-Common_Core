/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldi-fior <ldi-fior@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 14:24:03 by ldi-fior          #+#    #+#             */
/*   Updated: 2024/02/28 12:50:37 by ldi-fior         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*CH_NBR________________________________________________________________________
  - Restituisce 1 se il valore passato e un numero, 0 altrimenti              */
int	ch_nbr(char	*str)
{
	int	i;

	i = 0;
	if (str[0] == '-' || str[0] == '+')
		i++;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (0);
		i++;
	}
	/*se il numero ha piu di 11 cifre ritorno 0*/
	if (((str[0] == '-' || str[0] == '+') && i > 11) || 
		((str[0] >= '0' && str[0] <= '9') && i > 10))
		return (0);
	return (1);
}

/*CHECK_ARG___________________________________________________________________
👾  controlla che gli argomenti inseriti siano validi 

- alloco la matrice temporanea che conterra tutte le stringhe immese dall utente
- chiama la funzione di controllo sui valori
- se un qualsiasi valore non risulta valido libero la matrice tmp e ritorno 0
- altrimenti restituisce il numero di argomenti inseriti dall' utente
*/
int	check_arg(int argc, char **argv)
{
	int		i;
	int		j;
	char	**tmp;
	int		count;

	i = 0;
	count = 0;
	while (++i < argc)
	{
		/*Eseguo lo split per ogni elemento di argv*/
		tmp = ft_split(argv[i], 32);
		if (!tmp)
			return (0);
		j = -1;
		while (tmp[++j])
		{
			/*Per ogni elemento estratto con split controllo se e'un numero*/
			if (!ch_nbr(tmp[j]))
				return (free_matrix(tmp));
			count++;
		}
		free_matrix(tmp);
	}
	return (count);
}

int	ch_double(t_stack *stk)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < stk->len_a - 1)
	{
		j = i + 1;
		while (j < stk->len_a && stk->stk_a[i] != stk->stk_a[j])
			j++;
		if (j < stk->len_a) // Se abbiamo trovato un duplicato consecutivo
			return (0);
		i++;
	}
	return (1);
}