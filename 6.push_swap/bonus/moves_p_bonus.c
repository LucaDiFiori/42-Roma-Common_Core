/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves_p_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldi-fior <ldi-fior@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 17:34:53 by ldi-fior          #+#    #+#             */
/*   Updated: 2024/02/29 14:15:23 by ldi-fior         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

static void	push_bns(int *to_remove, int *to_add, int len_to_add, int l_t_r)
{
	int	i;

	if (!l_t_r)
		return ;
	i = len_to_add;
	while (i > 0)
	{
		to_add[i] = to_add[i - 1];
		i--;
	}
	to_add[0] = to_remove[0];
	while (i < l_t_r)
	{
		to_remove[i] = to_remove[i + 1];
		i++;
	}
}

void	pa_bns(t_stack *stk)
{
	push_bns(stk->stk_b, stk->stk_a, stk->len_a, stk->len_b);
	stk->len_a++;
	stk->len_b--;
}

void	pb_bns(t_stack *stk)
{
	push_bns(stk->stk_a, stk->stk_b, stk->len_b, stk->len_a);
	stk->len_a--;
	stk->len_b++;
}
