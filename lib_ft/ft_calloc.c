/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldi-fior <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 12:47:28 by ldi-fior          #+#    #+#             */
/*   Updated: 2024/01/15 11:34:57 by ldi-fior         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;
	size_t	len;

	len = count * size;

	/* controllo che count e size non siano 0 e che (almeno uno dei due, in questo caso uso count) 
	 * sia minore nel massimo valore assunto da un size_t:
	 * - 4294... e' il max size_t
	 * - lo divide per size perhe : a seconda del size (cioe del tipo di variabile che passo
	 *   avro un numero massino di posizioni che potro allocare. Se ho un char potro allocare 
	 *  piu posti di un int etc)
	 *  */
	if (count && size && count > (4294967295U / size))
		return (NULL);
	ptr = (void *)malloc(len);
	if (ptr == NULL)
		return (NULL);
	ft_bzero(ptr, len);
	return (ptr);
}
