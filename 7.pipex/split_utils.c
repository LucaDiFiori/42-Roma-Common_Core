/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldi-fior <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 10:36:06 by ldi-fior          #+#    #+#             */
/*   Updated: 2024/03/19 10:36:06 by ldi-fior         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	count_quote(char const *str)
{
	int	dquote;
	int	i;

	dquote = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] == 34 || str[i] == 39)
			dquote++;
	}
	return (dquote);
}

int	skip_quote(const char *str, int i, int flag, int *end_word)
{
	int	dquote;

	dquote = count_quote(str);
	if (flag == 0)
	{
		while (dquote != 0 && str[i])
		{
			if ((str[i] == 34 || str[i] == 39))
				dquote--;
			i++;
		}
	}
	else if (flag == 1)
	{
		while (dquote != 0 && str[i])
		{
			*end_word = *end_word + 1;
			if ((str[i] == 34 || str[i] == 39))
				dquote--;
			i++;
		}
	}
	return (i);
}
