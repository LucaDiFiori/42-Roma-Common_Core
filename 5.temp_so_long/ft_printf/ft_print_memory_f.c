/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_memory_f.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldi-fior <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 16:57:10 by ldi-fior          #+#    #+#             */
/*   Updated: 2024/01/18 15:46:10 by ldi-fior         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

static int	ft_reverse(const char *s)
{
	int	i;

	i = ft_strlen(s);
	while (--i >= 0)
		ft_putchar_f(s[i]);
	return (ft_strlen(s));
}

int	ft_print_memory_f(void *s)
{
	char		*base;
	char		*ptr;
	int			count;
	int			i;
	uintptr_t	p_int;

	if (!s)
		return (ft_putchar_f(48));
	p_int = (uintptr_t)s;
	base = "0123456789abcdef";
	ptr = (char *)malloc((sizeof(void *) * 2 + 1) * sizeof(char));
	if (!ptr)
		return (0);
	i = 0;
	while (p_int)
	{
		ptr[i] = base[p_int % 16];
		p_int /= 16;
		i++;
	}
	ptr[i] = '\0';
	count = ft_reverse(ptr);
	free (ptr);
	return (count);
}
