/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base_up_f.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldi-fior <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 16:55:33 by ldi-fior          #+#    #+#             */
/*   Updated: 2024/01/18 10:35:22 by ldi-fior         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr_base_up_f(long nbr)
{
	unsigned int	nlong;
	char			*symbols;
	int				count;

	symbols = "0123456789ABCDEF";
	nlong = (unsigned int)nbr;
	count = 0;
	if (nbr == 0)
		return (ft_putchar_f(48));
	if (nlong >= 16)
		count += ft_putnbr_base_up_f(nlong / 16);
	count += ft_putchar_f(symbols[nlong % 16]);
	return (count);
}
