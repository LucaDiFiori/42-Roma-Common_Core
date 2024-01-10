/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldi-fior <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 14:05:05 by ldi-fior          #+#    #+#             */
/*   Updated: 2024/01/10 12:29:26 by ldi-fior         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*ft_rev_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*ptr_dest;
	unsigned char	*ptr_src;

	ptr_dest = (unsigned char *)dest;
	ptr_src = (unsigned char *)src;
	while (n)
	{
		n--;
		ptr_dest[n] = ptr_src[n];
	}
	return (dest);
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	if (src == dst || len == 0)
		return (dst);
	if (dst > src && (size_t)(dst - src) < len)
		return (ft_rev_memcpy(dst, src, len));
	else
		return (ft_memcpy(dst, src, len));
}
