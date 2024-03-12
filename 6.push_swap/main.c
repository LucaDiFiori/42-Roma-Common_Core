/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldi-fior <ldi-fior@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 12:15:15 by ldi-fior          #+#    #+#             */
/*   Updated: 2024/02/28 12:08:50 by ldi-fior         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	main(int argc, char **argv)
{
	t_stack	stk;
	int		n_arg;

	if (argc < 2)
	{
		quit_and_free(&stk, 0);
		exit (0);
	}
	n_arg = check_arg(argc, argv);
	/*n_arg rappresenta il numero di argomenti inseriti. Se saranno 0 -> Errore
	  se saranno 1 semplicemente esco (perche non dovro ordinare nulla)*/
	if (n_arg <= 1)
	{
		if (!n_arg)
			ft_printf("Error\n");
		exit (1);
	}
	push_swap(&stk, n_arg, argc, argv);
	free (stk.stk_a);
	free (stk.stk_b);
}