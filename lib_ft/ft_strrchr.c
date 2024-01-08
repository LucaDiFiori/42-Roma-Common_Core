/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldi-fior <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 19:17:08 by ldi-fior          #+#    #+#             */
/*   Updated: 2024/01/08 19:19:05 by ldi-fior         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*temp;
	int		size;
	
	size = ft_strlen(s);
	temp = (char *)s + size;
	while (*temp != c)
	{
		if (*temp == s)
			return (0);
		temp--;
	}
	return (temp);
}
