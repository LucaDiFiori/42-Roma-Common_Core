/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldi-fior <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 19:17:08 by ldi-fior          #+#    #+#             */
/*   Updated: 2024/01/10 11:20:22 by ldi-fior         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*temp;

	temp = (char *)s + ft_strlen(s);
	if (c == '\0')
		return (temp);
	while (temp >= s)
	{
		if (*temp == c)
			return (temp);
		temp--;
	}
	return (NULL);
}
