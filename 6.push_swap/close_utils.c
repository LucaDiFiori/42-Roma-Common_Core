/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldi-fior <ldi-fior@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 12:46:27 by ldi-fior          #+#    #+#             */
/*   Updated: 2024/02/21 15:40:32 by ldi-fior         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	free_matrix(char **mat)
{
	int	i;

	i = -1;
	while (mat[++i])
		free(mat[i]);
	free(mat);
	return (0);
}

int	quit_and_free(t_stack *stk, int error)
{
	if (error == 0)
		ft_printf("Error\n");
	else if (error == 1)
	{
		ft_printf("Error\n");
		free(stk->stk_a);
		free(stk->stk_b);
	}
	exit (0);
}