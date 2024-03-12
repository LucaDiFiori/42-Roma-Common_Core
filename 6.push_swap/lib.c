/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldi-fior <ldi-fior@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 17:11:03 by ldi-fior          #+#    #+#             */
/*   Updated: 2024/02/21 11:06:58 by ldi-fior         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	count_words(char *str, char c)
{
	int	count;
	int	i;

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

char	**ft_split(char *str, char c)
{
	int		end_wrd;
	int		index;
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

int	ft_atoi(const char *nptr)
{
	int	result;
	int	sign;

	result = 0;
	sign = 1;
	while (*nptr == ' ' || (*nptr >= 9 && *nptr <= 13))
		nptr++;
	if (*nptr == '-')
	{
		sign *= -1;
		nptr++;
	}
	else if (*nptr == '+')
		nptr++;
	while (*nptr && *nptr >= '0' && *nptr <= '9')
	{
		result = result * 10 + (*nptr - '0');
		nptr++;
	}
	return (result * sign);
}