/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_memory_f.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldi-fior <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 16:57:10 by ldi-fior          #+#    #+#             */
/*   Updated: 2024/01/18 15:41:12 by ldi-fior         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

#include <stdio.h>
#include <unistd.h>



static size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

static int	ft_reverse(const char *s)
{
	int	i;

	i = ft_strlen(s);
	while (--i >= 0)
		ft_putchar_f(s[i]);
	return (ft_strlen(s));
}

int	ft_print_memory_f(void *s)
{
	char		*base;

	/*Dichiaro un puntatore a char (che puo' rappresentare 
	  valori positivi fino a 127, cioe' tutti i valori ASCII)
	  per poi andare a stampare, un byte alla volta, tutti i byte
	  che compongono il mio valore di memoria*/
	char		*ptr;
	int			count;
	int			i;
	int			len;

	/*Dichiaro una variabile in cui inseriro' il valore di memoria
	  uintptr_t: è un tipo di dato INT definito in C che è garantito 
	             essere abbastanza grande da contenere il valore di un puntatore. 
				 fornisce una rappresentazione senza segno della lunghezza 
				 dell'indirizzo di memoria di tipo INT.*/
	uintptr_t	p_int;
				 

	/*CONTROLLO SU S-------------------------------------------------*/
	if (!s)
		return (ft_putchar_f(48));

	/*INSERISCO IL VALORE DI MEMORIA CASTATO AD "INTERO" IN P_INT---*/
	p_int = (uintptr_t)s;
	base = "0123456789abcdef";

	/*CALCOLCOLO LEN--------------------------------------------------
	  mi serve sapere la lunghezza che andro'ad allocare. considerando
	  che un puntatore e' composto da 8 byte, ed ogni byte puo' contenere
	  un valore rappresentabile da due caratteri in esadecimale, allochero'
	  8*2 byte (+1) per il terminatore */
	len = sizeof(void *) * 2 + 1;

	/*ALLOCO LA STRINGA-----------------------------------------------
	  Alloco len byte di spazio che conterranno (in formato charatteri)
	  il mio indirizzo di memoria*/
	ptr = (char *)malloc(len * sizeof(char));
	if (!ptr)
		return (0);

	/*POPOLO LA STRINGA CON I VALORI CONVERTITI IN HEXA------------*/
	i = 0;
	while (p_int)
	{
		ptr[i] = base[p_int % 16];
		p_int /= 16;
		i++;
	}
	ptr[i] = '\0'; //termino la stringa

	/*STAMPO L'INDIRIZZO AL CONTRARIO-------------------------------
	  Avendo salvatop nell'array l'indirizzo al contrario devo ora 
	  stamparlo nel modo giusto*/
	count = ft_reverse(ptr);
	free (ptr);
	return (count);
}
