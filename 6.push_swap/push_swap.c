/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldi-fior <ldi-fior@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 09:54:21 by ldi-fior          #+#    #+#             */
/*   Updated: 2024/02/27 09:54:21 by ldi-fior         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void    best_move_a(t_stack *s)
{
    int i;

    i = -1;
    while (++i < s->len_a)
    {
        get_target_a(s, i);
        count_moves_a(s);
    }
}

void    best_move_b(t_stack *s)
{
    int i;

    i = -1;
    while (++i < s->len_b)
    {
        get_target_b(s, i);
        count_moves_b(s);
    }
}

void    sort(t_stack *stk)
{
    int len;
    
    pb(stk);
    pb(stk);
    len = stk->len_a;
    while (len > 3)
    {
        //get_max_min(stk);
        best_move_a(stk);
        sort_and_push(stk, 'a');
        len--;
    }      
    sort_trhee(stk);      
    len = stk->len_b;
    while (len > 0)
    {
        best_move_b(stk);
        sort_and_push(stk, 'b');
        len--;
    }
    final_move(stk);
}

void    final_move(t_stack *s)
{
    int i;

    i = -1;
    if (s->mm.min_idx_a < s->len_a / 2)
    {
        while (++i < s->mm.min_idx_a)
            ra(s);
    }
    else
    {
        while (++i < s->len_a - s->mm.min_idx_a)
            rra(s);
    }
}

void	push_swap(t_stack *stk, int n_arg, int argc, char **argv)
{
	init(stk);
	stk->len_a = n_arg;
	if (!alloc_stack(stk))
		quit_and_free(stk, 0);
	if (!init_stack(stk, argc, argv))
		quit_and_free(stk, 1);
	if (is_sorted(stk))
		return ;
    else if (stk->len_a == 2)
        sa(stk);
    else if (stk->len_a == 3)
        sort_trhee(stk);
    else if (stk->len_a > 3)
        sort(stk);
}