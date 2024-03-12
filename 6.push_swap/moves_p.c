/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves_p.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldi-fior <ldi-fior@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 14:23:30 by ldi-fior          #+#    #+#             */
/*   Updated: 2024/02/28 10:02:25 by ldi-fior         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	push(int *to_remove, int *to_add, int len_to_add, int len_to_remove)
{
	int	i;

	if (!len_to_remove)
		return ;
	i = len_to_add;
	while (i > 0)
	{
		to_add[i] = to_add[i - 1];
		i--;
	}
	to_add[0] = to_remove[0];
	while (i < len_to_remove)
	{
		to_remove[i] = to_remove[i + 1];
		i++;
	}
}
void	pa(t_stack *stk)
{
	push(stk->stk_b, stk->stk_a, stk->len_a, stk->len_b);
	stk->len_a++;
	stk->len_b--;
	get_max_min(stk);
	ft_printf("pa\n");
}

void	pb(t_stack *stk)
{
	push(stk->stk_a, stk->stk_b, stk->len_b, stk->len_a);
	stk->len_a--;
	stk->len_b++;
	get_max_min(stk);
	ft_printf("pb\n");
}