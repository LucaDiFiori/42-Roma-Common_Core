/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_u_f.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldi-fior <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 16:16:17 by ldi-fior          #+#    #+#             */
/*   Updated: 2024/01/18 10:20:49 by ldi-fior         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	nbstr_len(long n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len++;
	while (n && ++len)
		n /= 10;
	return (len);
}

static char	*ft_itoa(long n)
{
	char	*base;
	char	*n_str;
	int		len;

	base = "0123456789";
	len = nbstr_len(n);
	n_str = (char *)malloc(sizeof(char) * len + 1);
	if (n_str == NULL)
		return (NULL);
	n_str[len] = '\0';
	if (n < 0)
		n_str[0] = '-';
	if (n == 0)
		n_str[0] = '0';
	while (n)
	{
		if (n > 0)
			n_str[--len] = base[n % 10];
		else
			n_str[--len] = base[(n % 10) * -1];
		n /= 10;
	}
	return (n_str);
}

int	ft_print_u_f(unsigned int n)
{
	char	*ptr;
	int		i;

	ptr = ft_itoa(n);
	i = 0;
	while (ptr[i])
	{
		write(1, &ptr[i], 1);
		i++;
	}
	free(ptr);
	return (i);
}
