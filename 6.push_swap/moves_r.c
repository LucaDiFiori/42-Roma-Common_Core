/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves_r.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldi-fior <ldi-fior@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 16:10:24 by ldi-fior          #+#    #+#             */
/*   Updated: 2024/02/27 17:29:15 by ldi-fior         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	rotate(int *stk, int len)
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

void	ra(t_stack *stk)
{
	rotate(stk->stk_a, stk->len_a);
	ft_printf("ra\n");
}

void	rb(t_stack *stk)
{
	rotate(stk->stk_b, stk->len_b);
	ft_printf("rb\n");
}

void	rr(t_stack *stk)
{
	rotate(stk->stk_a, stk->len_a);
	rotate(stk->stk_b, stk->len_b);
	ft_printf("rr\n");
}