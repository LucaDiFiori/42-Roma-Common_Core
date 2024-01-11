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


/*-------------------Funzione di prova da passare: ft_tolowerm modificata------------*/
char	ft_tolower(unsigned int i, char c)
{
	if (c >= 'A' && c <= 'Z')
		return (c + i);
	else
		return (c);
}

/*--------------------------------strmapi----------------------------------------*/
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*str;
	int		i;
	
	i = 0;
	
	/*- - - - - - - - - - - allocazione - - - - - - - - - - - -*/
	str = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (str == NULL)
		return (NULL);
	/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

	while (s[i])
	{
		str[i] = (*f)(32,s[i]);
		i++;
	}
	str[i] = '\0';
	return (str);
}

/*-------------------------------MAIN-------------------------------------------*/
int main()
{
	char *str = "CIAO";
	char *result = ft_strmapi(str,&ft_tolower);
	printf("%s", result);
}
