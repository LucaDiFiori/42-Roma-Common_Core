/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_target.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldi-fior <ldi-fior@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 16:26:55 by ldi-fior          #+#    #+#             */
/*   Updated: 2024/02/27 15:54:01 by ldi-fior         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	upper_half(t_stack *s)
{
        if (s->trgt.tmp_which < s->trgt.tmp_where)
                s->trgt.tmp_moves = s->trgt.tmp_where;
	else
                s->trgt.tmp_moves = s->trgt.tmp_which;
}

void	lower_half(t_stack *s)
{
        if (s->len_a - s->trgt.tmp_which > s->len_b - s->trgt.tmp_where)
                s->trgt.tmp_moves = (s->len_a) - (s->trgt.tmp_which);
        else
                s->trgt.tmp_moves = (s->len_b) - (s->trgt.tmp_where);
}

void	one_up_one_down(t_stack *s)
{
        if (s->trgt.tmp_which < s->half.half_a
                && s->trgt.tmp_where >= s->half.half_b)
                s->trgt.tmp_moves = s->trgt.tmp_which 
                + (s->len_b - s->trgt.tmp_where);
        else
                s->trgt.tmp_moves = s->trgt.tmp_where
                + (s->len_a - s->trgt.tmp_which);
}