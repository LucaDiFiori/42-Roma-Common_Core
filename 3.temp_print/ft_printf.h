/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldi-fior <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 08:08:22 by ldi-fior          #+#    #+#             */
/*   Updated: 2024/01/18 13:03:00 by ldi-fior         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <limits.h>
# include <stdio.h>

int	ft_printf(const char *format, ...);
int	ft_print_memory_f(void *s);
int	ft_putchar_f(char c);
int	ft_putnbr_base_low_f(long nbr);
int	ft_putnbr_f(int n);
int	ft_print_u_f(unsigned int n);
int	ft_putnbr_base_up_f(long nbr);
int	ft_putstr_f(char *s);

#endif
