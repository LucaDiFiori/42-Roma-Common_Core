/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldi-fior <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 14:48:31 by ldi-fior          #+#    #+#             */
/*   Updated: 2024/01/17 10:20:03 by ldi-fior         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const *str, char c)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] == c && str[i])
			i++;
		if(str[i] != '\0')
			count++;
		while (str[i] != c && str[i])
			i++;
	}
	return (count);
}

char	**ft_split(char const *str, char c)
{
	size_t	end_wrd;
	size_t	index;
	char	**ptr_ret;
	
	if (!str)
		return (NULL);
	ptr_ret = malloc(sizeof(char *) * (count_words(str, c) + 1));
	if (ptr_ret == NULL)
		return (NULL);
	index = 0;
	while (*str)
	{
		/* se trovo separatori vado avanti col puntatore*/
		if (*str == c)
			str++;

		/* se non trovo separatori*/
		else
		{
			/* contatore per la fine della parola*/
			end_wrd = 0;

			/* fino a che non ho separatori aumento il count e mi sposto sulla stringa*/
			while (*str && *str != c)
			{
				end_wrd++;
				str++;
			}
			/* creo i sotto array con substr passando la stringa nella posizioone del
			 * primo carattere della parola, start = 0 e len = end_word
			 * Oss: non posso passare str (ma str-wrd) perche, dopro líncremento
			 * str punta alla fine della parola e non all nizio 
			 * quindi (str-word) rappresenta proprio la posizione di memoria della 
			 * prima lettera della parola trovata*/
			ptr_ret[index] = ft_substr(str - end_wrd, 0, end_wrd);
			if (ptr_ret[index] == NULL)
				return (NULL);
			index++;
		}
	}
	ptr_ret[index] = NULL;
	return (ptr_ret);
}
