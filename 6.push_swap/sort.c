/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldi-fior <ldi-fior@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 10:18:09 by ldi-fior          #+#    #+#             */
/*   Updated: 2024/02/28 12:32:15 by ldi-fior         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*Se entrambi sono sopra la meta' faccio rr e decremento l'indice di entrambi*/
void	both_up(t_stack *s)
{
	while (s->trgt.which != 0 && s->trgt.where != 0)
	{
		rr(s);
		s->trgt.which--;
		s->trgt.where--;
	}
	while (s->trgt.which != 0)
	{
		ra(s);
		s->trgt.which--;
	}
	while (s->trgt.where != 0)
	{
		rb(s);
		s->trgt.where--;
	}
}
/*Se l'elemento in a e' sopra la meta mentra l'elemento in b si trova sotto*/
void	up_down(t_stack *s)
{
	while (s->trgt.which != 0)
	{
		ra(s);
		s->trgt.which--;
	}

	/*Supponiamo che where sia l'indice 2 su una stack di 4. Con questa confizione */
	/*eseguo rrb altre due volte (2+1 = 3. 3+1 =4) e lo porto in cima*/
	while (s->trgt.where < s->len_b)
	{
		rrb(s);
		s->trgt.where++;
	}
}							  

void	down_up(t_stack *s)
{
	while (s->trgt.which < s->len_a)
	{
		rra(s);
		s->trgt.which++;
	}
	while (s->trgt.where != 0)
	{
		rb(s);
		s->trgt.where--;
	}
}

void	both_down(t_stack *s)
{
	int	i;
	/*NOTA: "s->len_a - s->trgt.which" Mi da il numero di mosse necessarie a 
			 portare l'elemento di a.
			 Quindi s questo valore e' moggiore del corrispettivo in b significa
			 che e' "piu lontano dalla cima". In questo caso eseguiro
			 rrr per muovere entrambi e poi rra per portare l elemento di a sopra */
			 
	i = -1; /*i rappresenta il numero di mosse*/
	if(s->len_a - s->trgt.which > s->len_b - s->trgt.where)
	{
		while (++i < (s->len_b - s->trgt.where)) /*s->len_b - s->trgt.where Questo e' il numero di mosse che mancano a b per arrivare sopra*/
			rrr(s);
		i = -1;
		while (++i < (s->len_a - s->trgt.which) - (s->len_b -s->trgt.where)) /*numero di mosse rimaste da fare al'elemento a*/
			rra(s);
	}
	else
	{
		i = -1;
		while (++i < (s->len_a - s->trgt.which))
			rrr(s);
		i = -1;
		while (++i < (s->len_b - s->trgt.where) - (s->len_a -s->trgt.which))
			rrb(s);
	}
}

void	sort_and_push(t_stack *s, char str)
{	
	/*find_half(s, 'a');
	find_half(s, 'b');*/

	
	if (s->trgt.which < s->half.half_a && s->trgt.where < s->half.half_b)
		both_up(s);
	else if(s->trgt.which < s->half.half_a && s->trgt.where >= s->half.half_b)
		up_down(s);
	else if(s->trgt.which >= s->half.half_a && s->trgt.where < s->half.half_b)
		down_up(s);
	else if(s->trgt.which >= s->half.half_a && s->trgt.where >= s->half.half_b)
		both_down(s);
	if (str == 'a')
		pb(s);
	else
		pa(s);
		
}