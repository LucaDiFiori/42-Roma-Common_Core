/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldi-fior <ldi-fior@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 13:46:11 by ldi-fior          #+#    #+#             */
/*   Updated: 2024/02/28 12:03:05 by ldi-fior         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	init(t_stack *stk)
{
	stk->stk_a = NULL;
	stk->stk_b = NULL;
	stk->len_b = 0;
}

int	alloc_stack(t_stack *stk)
{
	stk->stk_a = (int *)malloc(sizeof(int) * stk->len_a);
	if (!stk->stk_a)
		quit_and_free(stk, 0);
	stk->stk_b = (int *)malloc(sizeof(int) * stk->len_a);
	if (!stk->stk_b)
	{
		if (stk->stk_a != NULL)
			free (stk->stk_a);
		quit_and_free(stk, 0);
	}
	return (1);
}

/*INIT_STACK____________________________________________________________________
  - inizializza le stack con i valori convertiti in interi e controlla che
    non ci siano doppioni. 
*/
int	init_stack(t_stack *stk, int argc, char **argv)
{
	int		i;
	int		j;
	int		k;
	char	**tmp;

	i = 0;
	k = 0;
	while (++k < argc)
	{
		tmp = ft_split(argv[k], 32);
		if (!tmp)
			return (0);
		j = -1;
		while (tmp[++j])
		{
			stk->stk_a[i++] = ft_atoi(tmp[j]);
		}
		free_matrix(tmp);
	}
	if (!ch_double(stk))
		return (0);
	return (1);
}