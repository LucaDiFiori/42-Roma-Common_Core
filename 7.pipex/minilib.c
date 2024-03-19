/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minilib.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldi-fior <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 17:26:30 by ldi-fior          #+#    #+#             */
/*   Updated: 2024/03/19 12:29:57 by ldi-fior         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"


char	*ft_substr(char const *s, int start, int len)
{
	char	*ptr;

	if (!s)
		return (NULL);
	if (len > s_len(s))
		len = s_len(s);
	if (start >= s_len(s))
		return (ft_strdup(""));
	ptr = (char *)malloc((len + 1) * sizeof(char));
	if (ptr == NULL)
		return (NULL);
	ft_memcpy(ptr, s + start, len);
	ptr[len] = '\0';
	return (ptr);
}

const char *ft_strchar(const char *str, const char c)
{
	while(str)
	{
		if(*str == c)
				return(str);
		str++;
	}
	return (NULL);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len_s1;
	size_t	len_s2;
	char	*ptr;

	if (s1 && s2)
	{
		len_s1 = s_len(s1);
		len_s2 = s_len(s2);
		ptr = (char *)malloc(len_s1 + len_s2 + 1);
		if (ptr == NULL)
			return (NULL);
		ft_memcpy(ptr, s1, len_s1);
		ft_memcpy(ptr + len_s1, s2, len_s2 + 1);
		ptr[len_s1 + len_s2] = '\0';
		return ((char *)ptr);
	}
	return (NULL);
}