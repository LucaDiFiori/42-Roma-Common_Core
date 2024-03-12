/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldi-fior <ldi-fior@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 11:10:39 by ldi-fior          #+#    #+#             */
/*   Updated: 2024/02/26 11:10:39 by ldi-fior         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int is_sorted(t_stack *stk)
{
    int i;
    int j;

    i = -1;
    while (++i < stk->len_a - 1)
    {
        j = i + 1;
        if (stk->stk_a[i] > stk->stk_a[j])
            return (0);
    }
    return (1);
}

void    sort_trhee(t_stack *stk)
{
    get_max_min(stk);
    if (stk->mm.max_idx_a == 0)
    {
        ra(stk);
    }
    if (stk->mm.max_idx_a == 1)
    {
        rra(stk);
    }
    if (stk->stk_a[0] > stk->stk_a[1])
    {
        sa(stk);
    }  
    get_max_min(stk); ////////??????
}

void    find_half(t_stack *stk, char stack)
{
    if (stack == 'a')
    {
        if (stk->len_a % 2 == 0)
            stk->half.half_a = stk->len_a / 2;
        else
            stk->half.half_a = (stk->len_a / 2) + 1;
    }
    else if (stack == 'b')
    {
        if (stk->len_b % 2 == 0)
            stk->half.half_b = stk->len_b / 2;
        else
            stk->half.half_b = (stk->len_b / 2) + 1;
    }
}