/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldi-fior <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:10:04 by ldi-fior          #+#    #+#             */
/*   Updated: 2024/01/15 20:12:22 by ldi-fior         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*----------------------------------F. DI STAMPA-------------------------------*/
/* Questa funzione chiamera', a seconda del carattere che segue il "%"
   una funzione che stampi a schermo l'output desiderato.
   Deve ritornare un int perche' restituira' il numero di caratteri stampati
   
   ARGOMENTI: - puntatore a puntatore al tipo va_list:
                Oss: Qunado dichiaro una variabile va_list (ad esempio "va_list ptr")
				     "ptr" e' in realta' un puntatore. Non serve farlo precedere 
					 da "*" perche' il puntatore viene dichiarato nella libreria che
					 lo contiene.
                Oss2: Il primo argomento di questa funzione (va_list *ptr_ap) e'
				      quindi un puntatore a puntatore di tipo va_list che conterra'
					  la posizione di memoria del puntatore dichiarato nella funzione
					  ft_printf.
			  - carattere: il carattere che segue "%"  	
   
    VA_ARG:	 La funzione va_arg è utilizzata per accedere a successivi argomenti 
	         della lista di argomenti. 
			 
			 Viene utilizzata in combinazione con l'oggetto va_list 
			 e consente di ottenere il valore dell'argomento corrente nella lista.

			 Dopo essere stata chiamata (ed aver retituito la posizione corrente)
			 spostera' il puntatore degli argomenti all'argomento successivo

             
			 
			 type va_arg(va_list ap, type);
               ap: L'oggetto di tipo va_list che rappresenta la lista di argomenti.
               type: Il tipo di dato dell'argomento che si vuole ottenere (estrarre dagli argomenti).
               
               es: mettiamo ad esempio che voglia stampare, fra gli argomenti, un 
				   elemento stringa. Va_arg andra' a dire "entra nella lista 
				   puntata in quella posizione, l'elemento che  sartrarrai sara'
				   di tipo puntatore a stringa"
*/			 


static int	print_arg(va_list *ptr_ap, char c)
{
	/*STAMPA UN CARATTERE ------------------------------------------------*/
    if (c == 'c')
      /* va_list vuole come primo argomento un puntatore a va_list.
         considerando che ptr_ap contiene la posizione di memoria di un
         puntatore a va_list, dovro' applicare "*"
         
         NOTA: Come secondo argomento devo mettere int invece di char
               perche' va_arg promuovve automanticamente i type piccoli
               come char ad int
         */
      return (ft_putcharf(va_arg(*ptr_ap, int)));
	
	/* STAMPA UN STRINGA--------------------------------------------------*/
    else if (c == 's')
        return (ft_putstr_f(va_arg(*ptr_ap, char *)));
    
	/*STAMPA UNA POSIZIONE DI MEMORIA-------------------------------------*/
    else if (c == 'p')
        return (ft_putstr_f("Ox") + ft_print_memory_f(va_arg(*ptr_ap, void *)));

	/*STAMPA UN DECIMALE IN BASE 10---------------------------------------*/
    else if (c == 'i' || c == 'd')
        return (ft_putnbr_f(va_arg(*ptr_ap, int)));

	/*STAMPA UNSIGNED INT--------------------------------------------------*/
    else if (c == 'u')
        return (ft_putnbr_u_f(va_arg(*ptr_ap, unsigned int)));

	/*STAMPA IN ESADECIMALE minuscolo--------------------------------------*/
    else if (c == 'x')
       return (ft_putnbr_base_low_f(va_arg(*ptr_ap, long)));

	/*STAMPA IN ESADECIMALE Maiuscolo--------------------------------------*/
    else if (c == 'X')
        return (ft_putnbr_base_up_f(va_arg(*ptr_ap, long)));

	/*QUALSIASI ALTRO CARATTERE DOPO "%" (diverso dagli specificati) LO STAMPO*/
    else
        return (ft_putchar_f(c));
}
/*------------------------------------------------------------------------------*/

/*------------------------------------FT_PRINTF---------------------------------*/
int	ft_printf(const char *format, ...)
{
	/* 
	creo il puntatore "ap" (argument pointers). Puntatore al type va_list
	che punta al primo argomento cioe' "format"
	 */
	va_list	ap;

	/*
	 dichiaro una variabile int per contare quanti argomenti sto passando 
	 alla funzione (perche' printf ritorna il numero di caratteri stampati
	*/
	int	count;

	/*
	 Ora dovro' inizializzare il mio puntatore. Lo faro' con va_start che 
	 (per definizione) inizializza ap al secondo argomento che passero'
	 (perche' il primo rappresenta il numero di variabili)
	 */
	 int i;

	 va_start(ap, format);
	 count = 0;
	 i = 0;

	 /*
	  Per sapere quanti argomenti sto passando alla mia funzione, andro'
	  a ciclare sulla stringa "format". Ogni volta che incontro "%" significa
	  che ho incontrato un parametro
	 */
	 while (format[i])
	 {
		 /* Se incontro un "%" chiamo per stampare in accordo con lo specifier
		 --------------------------------------------------------------------*/
		 if (format[i] == '%')
		 {
			 /* Se incontra un "%" chiamo la funzione che controllera' quale
			    specificatore lo segue (per questo i++) e stampa conseguentemente.*/
				i++;

			 /*	alla fun. passero' l'indirizzo di memoria del mio puntatore "ap"
				(cioe' il puntatore alla lista che contiene le mie variabili */
			 count += print_arg(&ap, format[i]);
		 }
		 /*-------------------------------------------------------------------*/
		 /* altrimenti stampa il carattere il cui mi trovo */ 
		 else
			 count+= ft_putchar(format[i]);
         i++;
	 }

	 /* Una volta terminato il ciclo chiamo la macro "va_end" che distrugge
	    la variabile va_list puntata da ap*/
	 va_end(ap);
	 return (count);
}