/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves_s_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldi-fior <ldi-fior@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 17:59:09 by ldi-fior          #+#    #+#             */
/*   Updated: 2024/02/28 18:01:23 by ldi-fior         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

static void	sa_sb_bonus(int *stk)
{
	int	tmp;

	tmp = stk[0];
	stk[0] = stk[1];
	stk[1] = tmp;
}

void	sa_bonus(t_stack *stk)
{
	sa_sb_bonus(stk->stk_a);
}

void	sb_bonus(t_stack *stk)
{
	sa_sb_bonus(stk->stk_b);
}

void	ss_bonus(t_stack *stk)
{
	sa_sb_bonus(stk->stk_a);
	sa_sb_bonus(stk->stk_b);
}
