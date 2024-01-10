/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldi-fior <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 08:12:54 by ldi-fior          #+#    #+#             */
/*   Updated: 2024/01/10 11:49:20 by ldi-fior         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char    *ft_substr(char const *s, unsigned int start, size_t len)
{
    char *ptr;
    /*Controllo se la stringa s esiste*/
    if (!s)
        return (NULL);
    /*Controllo se len è > della lunghezza della stringa. Se inserisco un valore di len troppo di grandezza eccessiva lo riporta a alla lunghezza massima della stringa s*/
    if (len > ft_strlen(s))
        len = ft_strlen(s);

    /*Nel caso in cui si inserisca uno start >= la lunghezza di len
      esco*/
    if (start >= ft_strlen(s))
		return (NULL);


    ptr = (char *)malloc((len + 1) * sizeof(char));
    if (ptr == NULL)
        return (NULL);
    ft_memcpy(ptr, s + start, len);
    ptr[len] = '\0';
    return (ptr);
}
