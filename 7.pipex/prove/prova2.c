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







/*
➜  prove man stdarg
➜  prove man 2 open */

/******************************************************************************/

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
		{
			/***************************************************/
			/*Qui mi trovo sullo spazio e guardo se il carattere dopo e uno degli apici*/
			if ((str[i + 1] == 34 || str[i + 1] == 39) && str[i + 1])
			{
				count++;
				while ()
					printf("culo%d\n", i);
				/*
				Come gestire ad esempio: "grep 'un'altra insieme un'altra'"
				o "grep 'un'altra insieme"
				*/
			}
			/***********************************************************/
			i++;
		}
	}
    printf("%d\n", count);
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





int main(int argc, char **argv)
{
    if (argc == 2)
    {
        int i;
        char **matrice;

        i = -1;
        matrice = ft_split(argv[1], ' ');
        while (matrice[++i])
            printf("%s\n", matrice[i]);
    }
    else 
        printf("NO\n");
}