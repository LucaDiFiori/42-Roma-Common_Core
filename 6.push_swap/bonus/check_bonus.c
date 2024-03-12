/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldi-fior <ldi-fior@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 10:45:00 by ldi-fior          #+#    #+#             */
/*   Updated: 2024/02/29 14:28:19 by ldi-fior         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

void	init_and_check(t_stack *stk, int n_arg, int argc, char **argv)
{
	init(stk);
	stk->len_a = n_arg;
	if (!alloc_stack(stk))
		quit_and_free(stk, 0);
	if (!init_stack(stk, argc, argv))
		quit_and_free(stk, 1);
	if (is_sorted(stk))
	{
		free(stk->stk_a);
		free(stk->stk_b);
		exit (0);
	}
	return ;
}
int	ft_strncmp(char *s1, char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (*s1 && *s2 && i < (n - 1) && *s1 == *s2)
	{
		s1++;
		s2++;
		i++;
	}
	return ((unsigned char)(*s1) - (unsigned char)(*s2));
}

int	input_check(char *input)
{
	if (!(ft_strncmp(input, "pa\n", 3)) || !(ft_strncmp(input, "pb\n", 3))
		|| !(ft_strncmp(input, "ra\n", 3)) || !(ft_strncmp(input, "rb\n", 3))
		|| !(ft_strncmp(input, "rr\n", 3)) || !(ft_strncmp(input, "sa\n", 3))
		|| !(ft_strncmp(input, "sb\n", 3)) || !(ft_strncmp(input, "ss\n", 3))
		|| !(ft_strncmp(input, "rra\n", 4)) || !(ft_strncmp(input, "rrb\n", 4))
		|| !(ft_strncmp(input, "rrr\n", 4)))
		return (1);
	else
		return (0);
}