/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldi-fior <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 12:32:08 by ldi-fior          #+#    #+#             */
/*   Updated: 2024/01/09 11:41:02 by ldi-fior         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
    size_t i;
    unsigned char *ptr_dest;
    const unsigned char *ptr_src;

    ptr_dest = (unsigned char *)dest;
    ptr_src = (const unsigned char *)src;
    i = 0;
    while (i < n) {
        ptr_dest[i] = ptr_src[i];
        i++;
    }
    return dest;
}
