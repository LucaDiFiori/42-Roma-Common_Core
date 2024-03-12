/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldi-fior <ldi-fior@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 17:22:56 by ldi-fior          #+#    #+#             */
/*   Updated: 2024/02/29 14:01:06 by ldi-fior         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKER_H
# define CHECKER_H

#include "../ft_printf/ft_printf.h"
#include "../push_swap.h"
#include "get_next_line/get_next_line.h"
#include <limits.h> /*????????????????????*/

void	rra_bns(t_stack *stk);
void	rrb_bns(t_stack *stk);
void	rrr_bns(t_stack *stk);
void	pa_bns(t_stack *stk);
void	pb_bns(t_stack *stk);
void	ra_bns(t_stack *stk);
void	rb_bns(t_stack *stk);
void	rr_bns(t_stack *stk);
void	sa_bonus(t_stack *stk);
void	sb_bonus(t_stack *stk);
void	ss_bonus(t_stack *stk);
void	init_and_check(t_stack *stk, int n_arg, int argc, char **argv);
void	inputs(t_stack *s);
int		input_check(char *input);
void	make_moves(char *inp, t_stack *s);
int		ft_strncmp(char *s1, char *s2, size_t n);
#endif
