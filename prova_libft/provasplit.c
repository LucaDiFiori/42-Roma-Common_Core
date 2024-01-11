#include <stdlib.h>
#include <unistd.h>
#include<stdio.h>

size_t	ft_strlen(const char *s)
{
	size_t	i;

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
	while (i < n)
	{
		ptr_dest[i] = ptr_src[i];
		i++;
	}
	return (dest);
}

char    *ft_substr(char const *s, unsigned int start, size_t len)
{
    char *ptr;
    /*Controllo se la stringa s esiste*/
    if (!s)
        return (NULL);
    /*Controllo se len è > della lunghezza della stringa. Se inserisco un valore di len troppo di grandezza eccessiva lo riporta a alla lunghezza massima della stringa s*/
    if (len > ft_strlen(s))
        len = ft_strlen(s);

    /*Nel caso in cui si inserisca uno start >= la lunghezza di len
      esco*/
    if (start >= ft_strlen(s))
		return (NULL);


    ptr = (char *)malloc((len + 1) * sizeof(char));
    if (ptr == NULL)
        return (NULL);
    ft_memcpy(ptr, s + start, len);
    ptr[len] = '\0';
    return (ptr);
}
//------------------------------------SPLIT-------------------------------------------
static int	count_words(char const *str, char c)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] == c && str[i])
			i++;
		if(str[i] != '\0')
			count++;
		while (str[i] != c && str[i])
			i++;
	}
	return (count);
}

char	**ft_split(char const *str, char c)
{
	size_t	end_wrd;
	size_t	index;
	char	**ptr_ret;

	
	ptr_ret = malloc(sizeof(char *) * (count_words(str, c) + 1));
	if (ptr_ret == NULL)
		return (NULL);
	index = 0;
	while (*str)
	{
		/* se trovo separatori vado avanti col puntatore*/
		if (*str == c)
			str++;
		
		/* se non trovo separatori*/
		else
		{
			/* contatore per la fine della parola*/
			end_wrd = 0;

			/* fino a che non ho separatori aumento il count e mi sposto sulla stringa*/
			while (*str && *str != c)
			{
				end_wrd++;
				str++;
			}
			/* creo i sotto array con substr passando la stringa nella posizioone del 
			 * primo carattere della parola, start = 0 e len = end_word*/
			ptr_ret[index] = ft_substr(str - end_wrd, 0, end_wrd);
			if (ptr_ret[index] == NULL)
				return (NULL);
			index++;
		}
	}
	ptr_ret[index] = NULL;
	return (ptr_ret);
}
//-----------------------------------------------------------------------------------

int main()
{
    char *str = "c,,cu,lo,,";
    char c = ',';
    char **ptr = ft_split(str, c);
    
    char **temp = ptr;  // Puntatore temporaneo
    
    while (*temp)
    {
        printf("%s\n", *temp);
        free(*temp);  // Libera la memoria per ciascuna sottostringa
        temp++;
    }
    
    free(ptr);  // Libera la memoria per l'array di puntatori
    
    return 0;
}
