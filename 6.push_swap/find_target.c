/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_target.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldi-fior <ldi-fior@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 12:17:32 by ldi-fior          #+#    #+#             */
/*   Updated: 2024/02/26 12:17:32 by ldi-fior         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*Funzione che trova il target in b sopra al quale pushare l'elemento a.
  Restituisce l'indice di tale eleento*/
void    get_target_a(t_stack *s, int i)
{
    int j;
    
    s->trgt.tmp_where = 0;            /*posizione del target da associare ad a[i] da trovato in b*/                   
    s->trgt.tmp_which = i;             /*poisizione del target in b*/

    /* If the number you push from STACK_A to STACK_B is going to be the 
       new biggest or the smallest number, you should place it just above 
       the old biggest number in the STACK_B.*/
    if (s->stk_a[i] < s->stk_b[s->mm.min_idx_b] ||
        s->stk_a[i] > s->stk_b[s->mm.max_idx_b])
        s->trgt.tmp_where = s->mm.max_idx_b;     
    j = -1;
    while (++j < s->len_b - 1)
    {
        if (s->stk_a[i] < s->stk_b[j] && s->stk_a[i] > s->stk_b[j + 1])
            s->trgt.tmp_where = j + 1;
    }
}

/*Funzione che trova il target in a sopra al quale pushare l'elemento b*/
void    get_target_b(t_stack *s, int i)
{
    int j;
    /*NOTA: Se un elemento non soddisfa nessuna condizione verra' posizionato in cima*/
    s->trgt.tmp_which = 0;
    s->trgt.tmp_where = i;
    if (s->stk_b[i] < s->stk_a[s->mm.min_idx_a] ||
         s->stk_b[i] > s->stk_a[s->mm.max_idx_a])
         s->trgt.tmp_which = s->mm.min_idx_a;
    j = -1;
    while (++j < s->len_a - 1)
    {
        if (s->stk_b[i] > s->stk_a[j] && s->stk_b[i] < s->stk_a[j + 1])
             s->trgt.tmp_which = j + 1;
    }
}

static void move(t_stack *s, char stk)
{
    if (stk == 'a')
    {
        if(s->trgt.tmp_which == 0 || s->trgt.tmp_moves < s->trgt.moves)
        {
            s->trgt.which = s->trgt.tmp_which;
            s->trgt.where = s->trgt.tmp_where;
            s->trgt.moves = s->trgt.tmp_moves;
        }
    }
    else if (stk == 'b')
    {
        if(s->trgt.tmp_where == 0 || s->trgt.tmp_moves < s->trgt.moves)
        {
            s->trgt.which = s->trgt.tmp_which;
            s->trgt.where = s->trgt.tmp_where;
            s->trgt.moves = s->trgt.tmp_moves;
        }
    }
}

void    count_moves_a(t_stack *s)
{
    find_half(s, 'a');
    find_half(s, 'b');

    /*Entrambi sopra la meta'*/
    if (s->trgt.tmp_which < s->half.half_a
        && s->trgt.tmp_where < s->half.half_b)
        upper_half(s);
    /*Entrambi sotto la meta'*/
    else if (s->trgt.tmp_which >= s->half.half_a
        && s->trgt.tmp_where >= s->half.half_b)
        lower_half(s);
    /*Uno sopra e uno sotto*/
    else
        one_up_one_down(s);
    move(s, 'a');
}

void    count_moves_b(t_stack *s)
{
    find_half(s, 'a');
    find_half(s, 'b');

    /*Entrambi sopra la meta'*/
    if (s->trgt.tmp_which < s->half.half_a
        && s->trgt.tmp_where < s->half.half_b)
        upper_half(s);
    /*Entrambi sotto la meta'*/
    else if (s->trgt.tmp_which >= s->half.half_a
        && s->trgt.tmp_where >= s->half.half_b)
        lower_half(s);
    /*Uno sopra e uno sotto*/
    else
        one_up_one_down(s);
    move(s, 'b');
}