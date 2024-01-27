#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;
	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

/*returns a pointer to the first occurrence of the character c in the string s*/
char	*ft_strchr(const char *s, int c)
{
	char	*temp;

	if (!s)
		return (0);
	if (c == '\0')
		return ((char *)&s[ft_strlen(s)]);
	temp = (char *)s;
	while (*temp != (char)c)
	{
		if (*temp == '\0')
			return (NULL);
		temp++;
	}
	return (temp);
}

/*returns a pointer to a new string which is a duplicate of the string s. 
Memory for the new string is obtained with malloc*/
char	*ft_strdup(const char *src)
{
	char	*dest;
	int		i;

	i = 0;
	dest = (char *)malloc((sizeof(char)) * (ft_strlen(src) + 1));
	if (!dest)
		return (0);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

/* Returns a string which is the result of concatenating
   the elements of s1 & s2*/ /*MODIFICATO*/
char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;

	/*Al primo giro del while nella funzione find_line, la stringa stc_backup
	  (qui la s1) e' vuota. Devo quindi iserire una condizione per !s1:
	  Se s1 non esiste, alloca una stringa vuota (cosi' poi nella funzione
	  che la chiama avro' qualcosa da concatenare. */
	if (!s1)
	{
		s1 = (char *)malloc(sizeof(char) * 1);
		s1[0] = '\0';
	}
	if (!s2)
		return (NULL);
	str = (char *)malloc(sizeof(char) * ft_strlen(s1) + ft_strlen(s2) + 1);
	if (str == NULL)
		return (NULL);
	while (s1[i])
		str[j++] = s1[i++];
	i = 0;
	while (s2[i])
	{
		str[j] = s2[i];
		i++;
		j++;
	}
	str[j] = '\0';
	/*Dopo aver usato s1 ne faccio il free.
	  La s2 sara' "buffer" nella funzione g_n_l e verra'
	  liberato in quella funzione */
	free(s1);
	return (str);
}