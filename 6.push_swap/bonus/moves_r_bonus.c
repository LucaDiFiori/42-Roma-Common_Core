/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves_r_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldi-fior <ldi-fior@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 17:42:01 by ldi-fior          #+#    #+#             */
/*   Updated: 2024/02/28 17:44:25 by ldi-fior         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

static void	rotate_bns(int *stk, int len)
{
	int	i;
	int	tmp;

	i = 0;
	tmp = stk[0];
	while (i < len)
	{
		stk[i] = stk[i + 1];
		i++;
	}
	stk[len - 1] = tmp;
}

void	ra_bns(t_stack *stk)
{
	rotate_bns(stk->stk_a, stk->len_a);
}

void	rb_bns(t_stack *stk)
{
	rotate_bns(stk->stk_b, stk->len_b);
}

void	rr_bns(t_stack *stk)
{
	rotate_bns(stk->stk_a, stk->len_a);
	rotate_bns(stk->stk_b, stk->len_b);
}
