/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prova_itoa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldi-fior <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 07:28:56 by ldi-fior          #+#    #+#             */
/*   Updated: 2024/01/11 08:32:17 by ldi-fior         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include<stdio.h>

//-----------------------------F1: lunghezza numero-----------------------------
/* Conta il numero di cifre + 1 per far posto al terminatore*/
static int	nbstr_len(int n)
{
	int	len;
/*len = 1 per tener posto al terminatore nella stringa*/
	len = 1;

/* > Se n = 0 --> avro una stringa di lunghezza 2
   > Se la n e'<0 faccio spazio nella stringa per il "-"*/
	if (n <= 0)
		len++;
	while(n && ++len)
		n /= 10;
	return (len);
}

//------------------------------------ITOA-------------------------------------

/*Uso il modulo per estrarre le cifre ed usarle come indice 
  per della stringa base*/
char	*ft_itoa(int n)
{
	char	*base;
	char	*n_str;
	int		len;

	base = "0123456789";

	/* Sottraggo uno per non sovrascrivere il terminatore*/
	len = nbstr_len(n) - 1;

	/*allocazione- - - - - - - - - - - - - - - - - - - - - - - */
	n_str = (char *)malloc(sizeof(char) * nbstr_len(n));
	if (n_str == NULL)
		return (NULL);
	/* Se malloc riesce inserisco il terminatore alla stringa*/
	else
		n_str[nbstr_len(n)] = '\0';
	/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

	/* Se n < 0 il primo elemento della str sara'-"*/
	if (n < 0)
		n_str[0] = '-';
	if (n == 0)
		n_str[len] = '0';

	while (n)
	{
		if (n > 0)
			n_str[--len] = base[n % 10];
		else
			n_str[--len] = base[(n % 10) * -1];
		n /= 10;
	}
	return (n_str);
}


//--------------------------------------MAIN----------------------------------
int main()
{
printf("%s\n", ft_itoa(-2147483648));
}
