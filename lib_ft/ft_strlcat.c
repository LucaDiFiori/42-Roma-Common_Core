/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldi-fior <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 17:16:54 by ldi-fior          #+#    #+#             */
/*   Updated: 2024/01/13 14:18:16 by ldi-fior         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	len_dst;

	i = 0;
	if (dstsize == 0)
		return (ft_strlen(src));
	if (dstsize < ft_strlen(dst))
		return (dstsize + ft_strlen(src));
	len_dst = ft_strlen(dst);
	while (len_dst + i + 1 < dstsize && src[i])
	{
		dst[i + len_dst] = src[i];
		i++;
	}
	dst[i + len_dst] = '\0';
	return (len_dst + ft_strlen(src));
}
