/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldi-fior <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 18:37:30 by ldi-fior          #+#    #+#             */
/*   Updated: 2024/01/08 18:46:14 by ldi-fior         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *source, const char *to_find, size_t len)
{
	size_t	len2;

	if (*to_find == '\0')
		return (source);
	len2 = ft_strlen(to_find);
	while (*source && n >= len2)
	{
		if (*source == *to_find && ft_memcmp(source, to_find, len2) == 0)
			return (source);
		source++;
	}
	return (0);
}
