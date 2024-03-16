/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldi-fior <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 14:09:14 by ldi-fior          #+#    #+#             */
/*   Updated: 2024/03/13 14:09:14 by ldi-fior         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <limits.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>

//# include "get_next_line/get_next_line.h"

/*pipex_utils.c*/
int quit_free(const char *error, char *str, char **mat, int err_type);

/*minilib.c*/
int     s_len(const char *s);
char    **ft_split(char const *str, char c);

/*minilib_2*/
char	*ft_strdup(const char *src);
void	*ft_memcpy(void *dest, const void *src, size_t n);
char	*ft_strnstr(const char *source, const char *to_find, size_t len);
void	ft_putstr_fd(char *s, int fd);

/*command.c*/
void    command(char *argv, char **envp);

#endif