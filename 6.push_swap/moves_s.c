/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves_s.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldi-fior <ldi-fior@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 12:36:55 by ldi-fior          #+#    #+#             */
/*   Updated: 2024/02/27 17:48:53 by ldi-fior         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*Inverte il primo elemento ed il secondo della stack passata*/
static void	sa_sb(int *stk)
{
	int	tmp;

	tmp = stk[0];
	stk[0] = stk[1];
	stk[1] = tmp;
}

void	sa(t_stack *stk)
{
	sa_sb(stk->stk_a);
	ft_printf("sa\n");
}

void	sb(t_stack *stk)
{
	sa_sb(stk->stk_b);
	ft_printf("sb\n");
}

/*Inverte il primo elemento di entrambi le stack*/
void	ss(t_stack *stk)
{
	sa_sb(stk->stk_a);
	sa_sb(stk->stk_b);
	ft_printf ("ss\n");
}