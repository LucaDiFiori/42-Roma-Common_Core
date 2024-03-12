/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldi-fior <ldi-fior@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 10:31:30 by ldi-fior          #+#    #+#             */
/*   Updated: 2024/02/29 14:18:43 by ldi-fior         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

void	inputs(t_stack *s)
{
	char	*istruction;

	istruction = NULL;
	while (1)
	{
		istruction = get_next_line(0);
		if (!istruction)
			break;
		if (!input_check(istruction))
			quit_and_free(s, 1);
		make_moves(istruction, s);
		free(istruction);
	}
}

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
	if (n_arg <= 1)
	{
		if (!n_arg)
			ft_printf("Error\n");
		exit (1);
	}
	init_and_check(&stk, n_arg, argc, argv);
	inputs(&stk);
	if (is_sorted(&stk))
		ft_printf("OK\n");
	else
		ft_printf("KO\n");
	free(stk.stk_a);
	free(stk.stk_b);
}
