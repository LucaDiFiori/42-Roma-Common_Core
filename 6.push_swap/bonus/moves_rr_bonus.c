/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves_rr_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldi-fior <ldi-fior@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 17:22:25 by ldi-fior          #+#    #+#             */
/*   Updated: 2024/02/29 11:49:51 by ldi-fior         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

static void	rev_rot_bns(int	*stk, int len)
{
	int	i;
	int	tmp;

	i = len - 1;
	tmp = stk[i];
	while (i > 0)
	{
		stk[i] = stk[i - 1];
		i--;
	}
	if (i == 0)
		stk[i] = tmp;
}

void	rra_bns(t_stack *stk)
{
	rev_rot_bns(stk->stk_a, stk->len_a);
}

void	rrb_bns(t_stack *stk)
{
	rev_rot_bns(stk->stk_b, stk->len_b);
}

void	rrr_bns(t_stack *stk)
{
	rev_rot_bns(stk->stk_a, stk->len_a);
	rev_rot_bns(stk->stk_b, stk->len_b);
}
