/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldi-fior <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 19:31:07 by ldi-fior          #+#    #+#             */
/*   Updated: 2024/03/16 19:31:07 by ldi-fior         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*Questo split restituisce tutto cio che viene inserito fra apici come unico
elemento. Anche se ho elementi attaccati alle virgolette 
(ad esempio: 'ciao come'sti) Mi restituira' separatamente ciao come e poi stai*/

static int	normal_count(char const *str, char c)
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

static int	with_quote_count(const char *str, char c)
{
	int	count;

	int	i;

	count = 0;
	i = 0;
	while (str[i])
		{
			while (str[i] == c && str[i])
				i++;
			if (((str[i] == 34 || str[i] == 39)
				&& (ft_strchar((str + i + 1), 39) != NULL)) && count++)
				i = skip_quote(str, i, 0, NULL);
			else
			{
				if (str[i] != '\0')
					count++;
				while (str[i] != c && str[i] && (str[i] != 39 && str[i] != 34))
					i++;
			}
		}
	return (count);
}

static int	count_words(char const *str, char c)
{
	int	count;
	
	count = 0;
	if (count_quote(str) == 1)
		count = normal_count(str, c);
	else 
		count = with_quote_count(str, c);
	return (count);
}

static void	ft_ret(char **ret, const char *str, int *i, int *j, char c)
{
	int end_wrd;

	if ((str[*j] == 34 || str[*j] == 39) && count_quote(str) != 1
		&& (str[*j - 1] == c || str[*j + 1] == c))
	{
		end_wrd = 0;
		*j = skip_quote(str, *j, 1, &end_wrd);
		ret[*i] = ft_substr(str + ((*j - end_wrd) + 1), 0, end_wrd - 2);
		*i = *i + 1;

	}
	else
	{
		end_wrd = 0;
		while (str[*j] && str[*j] != c && ++end_wrd)
			*j = *j + 1;
		ret[*i] = ft_substr(str + (*j - end_wrd), 0, end_wrd);
		*i = *i + 1;
	}
}

char	**dquote_split(char const *str, char c)
{
	int	i;
	int	j;
	char	**ret;

	if (!str)
		return (NULL);
	ret = malloc(sizeof(char *) * (count_words(str, c) + 1));
	if (ret == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (str[j])
	{
		if (str[j] == c)
			j++;
		else
		{
			ft_ret(ret, str, &i, &j, c);
		}
	}
	ret[i] = NULL;
	return (ret);
}

