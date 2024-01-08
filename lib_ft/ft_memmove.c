/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldi-fior <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 14:05:05 by ldi-fior          #+#    #+#             */
/*   Updated: 2024/01/08 16:33:18 by ldi-fior         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_rev_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*ptr_dest;
	unsigned char	*ptr_src;

	ptr_dest = (unsigned char *)dest;
	ptr_dest = (unsigned char *)src;
	while (n)
		ptr_dest[n] = ptr_src[n--];
	return (dest);
}

void	*memmove(void *dst, const void *src, size_t len)
{
	if (src == dst || n == 0)
		return (dst);
	if (dst > src && dst - src < len)
		ft_rev_memcpy(dst, src, len);
	if (src > dst && src - dst < len)
		ft_memcpy(dst, src, len);
	return (dst);
}
