/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldi-fior <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 12:32:08 by ldi-fior          #+#    #+#             */
/*   Updated: 2024/01/08 16:33:21 by ldi-fior         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*ptr_dest;
	unsigned char	*ptr_src;

	prt_dest = (unsigned char *)dest;
	ptr_dest = (unsigned char *)src;
	i = 0;
	while (i < n && src[i])
		ptr_dest[i] = ptr_src[i++];
	return (dest);
}
