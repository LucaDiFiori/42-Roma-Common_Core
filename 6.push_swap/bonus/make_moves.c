/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_moves.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldi-fior <ldi-fior@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 12:50:49 by ldi-fior          #+#    #+#             */
/*   Updated: 2024/02/29 13:55:54 by ldi-fior         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

void	make_moves(char *inp, t_stack *s)
{
	if (!ft_strncmp(inp, "pa\n", 3))
		pa_bns(s);
	if (!ft_strncmp(inp, "pb\n", 3))
		pb_bns(s);
	if (!ft_strncmp(inp, "sa\n", 3))
		sa_bonus(s);
	if (!ft_strncmp(inp, "sb\n", 3))
		sb_bonus(s);
	if (!ft_strncmp(inp, "ss\n", 3))
		ss_bonus(s);
	if (!ft_strncmp(inp, "ra\n", 3))
		ra_bns(s);
	if (!ft_strncmp(inp, "rb\n", 3))
		rb_bns(s);
	if (!ft_strncmp(inp, "rr\n", 3))
		rr_bns(s);
	if (!ft_strncmp(inp, "rra\n", 4))
		rra_bns(s);
	if (!ft_strncmp(inp, "rrb\n", 4))
		rrb_bns(s);
	if (!ft_strncmp(inp, "rrr\n", 4))
		rrr_bns(s);
}