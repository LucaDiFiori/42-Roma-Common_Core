/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minilib.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldi-fior <ldi-fior@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 17:26:30 by ldi-fior          #+#    #+#             */
/*   Updated: 2024/03/15 10:23:54 by ldi-fior         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	s_len(const char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

static char	*ft_substr(char const *s, int start, int len)
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

static int	count_words(char const *str, char c)
{
	int	count;
	int		i;

	count = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] == c && str[i])
			i++;
		if (str[i] != '\0')
			count++;
		while (str[i] != c && str[i])
			i++;
	}
	return (count);
}

char	**ft_split(char const *str, char c)
{
	int	end_wrd;
	int	index;
	char	**ptr_ret;

	if (!str)
		return (NULL);
	ptr_ret = malloc(sizeof(char *) * (count_words(str, c) + 1));
	if (ptr_ret == NULL)
		return (NULL);
	index = 0;
	while (*str)
	{
		if (*str == c)
			str++;
		else
		{
			end_wrd = 0;
			while (*str && *str != c && ++end_wrd)
				str++;
			ptr_ret[index++] = ft_substr(str - end_wrd, 0, end_wrd);
		}
	}
	ptr_ret[index] = NULL;
	return (ptr_ret);
}