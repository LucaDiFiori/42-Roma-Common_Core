/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_f.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldi-fior <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 16:14:16 by ldi-fior          #+#    #+#             */
/*   Updated: 2024/01/18 08:27:52 by ldi-fior         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr_f(int n)
{
	int	count;

	count = 0;
	if (n == 0)
		count++;
	if (n < 0)
	{
		ft_putchar_f('-');
		if (n < -9)
			ft_putnbr_f((- (n / 10)));
		ft_putnbr_f((- (n % 10)));
		count++;
	}
	else if (n > 9)
	{
		ft_putnbr_f((n / 10));
		ft_putnbr_f((n % 10));
	}
	else
		ft_putchar_f(n + '0');
	while (n != 0 && ++count)
		n = n / 10;
	return (count);
}
