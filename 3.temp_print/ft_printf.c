/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldi-fior <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 17:21:24 by ldi-fior          #+#    #+#             */
/*   Updated: 2024/01/18 15:46:29 by ldi-fior         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	print_arg(va_list *ptr_ap, char c)
{
	if (c == 'c')
		return (ft_putchar_f(va_arg(*ptr_ap, int)));
	else if (c == 's')
		return (ft_putstr_f(va_arg(*ptr_ap, char *)));
	else if (c == 'p')
		return (ft_putstr_f("0x") + ft_print_memory_f(va_arg(*ptr_ap, void *)));
	else if (c == 'i' || c == 'd')
		return (ft_putnbr_f(va_arg(*ptr_ap, int)));
	else if (c == 'u')
		return (ft_print_u_f(va_arg(*ptr_ap, unsigned int)));
	else if (c == 'x')
		return (ft_putnbr_base_low_f(va_arg(*ptr_ap, long)));
	else if (c == 'X')
		return (ft_putnbr_base_up_f(va_arg(*ptr_ap, long)));
	else
		return (ft_putchar_f(c));
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		count;
	int		i;

	va_start(ap, format);
	count = 0;
	i = 0;
	while (format[i])
	{
		if (format[i] == '%')
		{
			i++;
			count += print_arg(&ap, format[i]);
		}
		else
			count += ft_putchar_f(format[i]);
		i++;
	}
	va_end(ap);
	return (count);
}
