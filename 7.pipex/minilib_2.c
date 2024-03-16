/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minilib_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldi-fior <ldi-fior@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 10:25:35 by ldi-fior          #+#    #+#             */
/*   Updated: 2024/03/15 14:44:08 by ldi-fior         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i] || fd < 0)
	{
		write(fd, &s[i], 1);
		i++;
	}
}

char	*ft_strdup(const char *src)
{
	char	*dest;
	int		i;

	i = 0;
	dest = (char *)malloc((sizeof(char)) * (s_len(src) + 1));
	if (dest == NULL)
		return (0);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*ptr_dest;
	const unsigned char	*ptr_src;

	ptr_dest = (unsigned char *)dest;
	ptr_src = (const unsigned char *)src;
	i = 0;
	if (!dest && !src)
		return (0);
	while (i < n)
	{
		ptr_dest[i] = ptr_src[i];
		i++;
	}
	return (dest);
}

char	*ft_strnstr(const char *source, const char *to_find, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!(*to_find))
		return ((char *)source);
	if (!len || !(*source))
		return (NULL);
	while (source[i] && len)
	{
		while ((j < len && to_find[j] && to_find[j] == source[i + j]))
			j++;
		if (to_find[j] == '\0')
			return ((char *)&source[i]);
		i++;
		j = 0;
		len--;
	}
	return (NULL);
}