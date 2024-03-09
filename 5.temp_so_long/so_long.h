/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldi-fior <ldi-fior@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 11:16:40 by ldi-fior          #+#    #+#             */
/*   Updated: 2024/02/15 13:03:52 by ldi-fior         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

#include <stdio.h>
#include <mlx.h>
#include <stdlib.h> /*Forse da rimuovere perche in altri file.h*/
#include <time.h>
# include <sys/time.h>
/*Se il file e'in un altra cartella devo includerne il path*/
#include "ft_printf/ft_printf.h"
#include "get_next_line/get_next_line.h"
#include "so_long_struct.h"

/*CLOSE_UTILS*/
void	print_error(char *s);
void	free_map_matrix(char **ptr_map, t_game *ptr_game);
int	    quit_and_free(char *error, int err_type, t_game *ptr_game);
void	ft_destroy(t_game *ptr_game);
int 	ft_close_x(t_game *ptr_game);

/*MAP_CHECKS*/
int     check_mapsize(t_game *ptr_game, char *m_path);
int     matrix_generator(t_game *ptr_game, char *m_path);
int	    p_e_c_n_count(t_game *game);
int	    check_map_and_set_tyle (t_game *ptr_game);
/*MAP_UTILS*/
int	    check_char(char c);
int		check_ber_file(char *path, t_game *ptr_game);
int		ft_strncmp(const char *s1, const char *s2);
int     matrix_complete_checker (t_game *ptr_game);
int		random_n(int min, int max);
/*LAUNCH*/
int	    set_var_to_zero(t_game *ptr_t_game);
int	    launch_game(t_game *ptr_t_game);
/*TILE*/
void     set_tile_location(t_game *ptr_game, char asset, int x, int y);
/*PATH_CHECK*/
char	**matrix_duplicator(t_game *ptr_game);
void	trace_all_path(t_game *ptr_game, int x, int y, char **traced_path);
int		check_path(t_game *ptr_game);

/*TEMPORANEIIII*/
void 	print_matrix(t_game *ptr_game);

/*HOOK_PLAYER*/
int		inputs(int key, t_game *ptr_game);
int     check_and_move(t_game *p_g, int key, int pos_x, int pos_y);

/*HOOK_PLAYER*/
int is_alive(t_game *p_g);

/*LOOP*/
int	loop_enemy(t_game *p_g);
int loop_coin(t_game *g);

/*IMAGE.C*/
int		init_images(t_game *p_g);
int 	on_screen (t_game *p_g);
void	d_score(t_game *g);

#endif