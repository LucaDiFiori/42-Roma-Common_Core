# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <limits.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>

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

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*end_word_dest;
	const unsigned char	*end_word_src;

	end_word_dest = (unsigned char *)dest;
	end_word_src = (const unsigned char *)src;
	i = 0;
	if (!dest && !src)
		return (0);
	while (i < n)
	{
		end_word_dest[i] = end_word_src[i];
		i++;
	}
	return (dest);
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

static char	*ft_substr(char const *s, int start, int len)
{
	char	*end_word;

	if (!s)
		return (NULL);
	if (len > s_len(s))
		len = s_len(s);
	if (start >= s_len(s))
		return (ft_strdup(""));
	end_word = (char *)malloc((len + 1) * sizeof(char));
	if (end_word == NULL)
		return (NULL);
	ft_memcpy(end_word, s + start, len);
	end_word[len] = '\0';
	return (end_word);
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


/**************************IN SPLIT.C****************************************/

/*
Questo split restituisce tutto cio che viene inserito fra apici come unico
elemento. Anche se ho elementi attaccati alle virgolette 
(ad esempio: 'ciao come'sti) Mi restituira' separatamente ciao come e poi stai*/
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

int	skip_quote(const char *str, int i, int flag, int *end_word, char c)
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
int	normal_count(char const *str, char c)
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
int	with_quote_count(const char *str, char c)
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
				i = skip_quote(str, i, 0, NULL, c);
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
	printf ("count = %d", count);
	return (count);
}


/*char	**dquote_split(char const *str, char c)
{
	int	end_wrd;
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
			if ((str[j] == 34 || str[j] == 39) && count_quote(str) != 1
				&& (str[j - 1] == c || str[j + 1] == c))
			{
				end_wrd = 0;
				j = skip_quote(str, j, 1, &end_wrd, c);
				ret[i++] = ft_substr(str + ((j - end_wrd) + 1), 0, end_wrd - 2);
			}
			else
			{
				end_wrd = 0;
				while (str[j] && str[j] != c && ++end_wrd)
					j++;
				ret[i++] = ft_substr(str + (j - end_wrd), 0, end_wrd);
			}
		}
	}
	ret[i] = NULL;
	return (ret);
}*/

void	ft_ret(char **ret, const char *str, int *i, int *j, char c)
{
	int end_wrd;

	if ((str[*j] == 34 || str[*j] == 39) && count_quote(str) != 1
		&& (str[*j - 1] == c || str[*j + 1] == c))
	{
		end_wrd = 0;
		*j = skip_quote(str, *j, 1, &end_wrd, c);
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


/******************************************************************************/

int main(int argc, char **argv)
{
    if (argc == 2)
    {
        int i;
        char **matrice;

        i = -1;
		printf ("||argv[1] = %s||\n", argv[1]);
        matrice = dquote_split(argv[1], ' ');
		printf("\nDopo lo split: \n");
        while (matrice[++i])
            printf("%s\n", matrice[i]);
    }
    else 
        printf("NO\n");
}