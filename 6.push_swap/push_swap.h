#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <stdio.h>
# include "ft_printf/ft_printf.h"

typedef struct s_trgt
{
	int		tmp_where; /*temporanei*/
	int		tmp_which;
	int		where;   /*finali*/
	int		which;
	int		tmp_moves;     /*numero di mosse temporaneo*/
	int		moves;     /* numero di mosse di migliore trovato*/
}	t_trgt;

typedef struct s_hlf
{
	int		half_a;
	int		half_b;
}	t_hlf;

typedef struct s_mm
{
	int		max_idx_a;
	int		min_idx_a;
	int		max_idx_b;
	int		min_idx_b;
}	t_mm;

typedef struct s_stack
{
	int		*stk_a;
	int		len_a;
	int		*stk_b;
	int		len_b;
	t_trgt	trgt;
	t_hlf	half;
 	t_mm	mm;
}	t_stack;

/*init*/
void	init(t_stack *stk);
int		init_stack(t_stack *stk, int argc, char **argv);
int		alloc_stack(t_stack *stk);

/*li*/
char	**ft_split(char *str, char c);
int		ft_atoi(const char *nptr);

/*lib_2*/
int		ft_strlen(char *s);
char	*ft_substr(char *s, int start, int len);
char	*ft_strdup(char *src);
void	*ft_memcpy(void *dest, void *src, int n);

/*clode utils*/
int		quit_and_free(t_stack *stk, int error);
int		free_matrix(char **mat);

/*checks*/
int		check_arg(int argc, char **argv);
int		ch_nbr(char	*str);
int		ch_double(t_stack *stk);

/*s_move.c*/
void	sa(t_stack *stk);
void	sb(t_stack *stk);
void	ss(t_stack *stk);

/*p_move.c*/
void	pa(t_stack *stk);
void	pb(t_stack *stk);

/*r_move.c*/
void	ra(t_stack *stk);
void	rb(t_stack *stk);
void	rr(t_stack *stk);
 
/*r_move.c*/
void	rra(t_stack *stk);
void	rrb(t_stack *stk);
void	rrr(t_stack *stk);

/*max_min*/
void    get_max_min(t_stack *stk);

/*sorting_utils*/
int		is_sorted(t_stack *stk);
void    sort_trhee(t_stack *stk);
void	find_half(t_stack *stk, char stack);

/*find_target*/
void    get_target_a(t_stack *stk, int i);
void    get_target_b(t_stack *stk, int i);
void    count_moves_a(t_stack *s);
void    count_moves_b(t_stack *s);

/*utils_target*/
void	upper_half(t_stack *s);
void	lower_half(t_stack *s);
void	one_up_one_down(t_stack *s);

/*push_swap.c*/
void	push_swap(t_stack *stk, int n_arg, int argc, char **argv);
void    best_move_a(t_stack *s);
void    best_move_b(t_stack *s);
void    sort(t_stack *stk);
void    final_move(t_stack *s);

/*sort.c*/
void	both_up(t_stack *s);
void	both_down(t_stack *s);
void	down_up(t_stack *s);
void	up_down(t_stack *s);
void	sort_and_push(t_stack *s, char str);

#endif