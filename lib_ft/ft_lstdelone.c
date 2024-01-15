#include <stdio.h>
#include <stdlib.h>

/*-------------------------------------NODO-------------------------------*/
typedef struct      s_list
{
    void            *content;
    struct s_list   *next;    /*-> struttura autoreferenziale*/
}                   t_list;
/*------------------------------------------------------------------------*/

/*lst: The node to free.
  del: The address of the function used to delete the content*/
void    ft_lstdelone(t_list *lst, void (*del)(void *))
{
    if (!lst || !del)
		return ;
    /*al puntatore alla funzione passo l'argomento che richiede
      cioè la posizione di memoria di elemento (il membro dati
      del nodo lst). 
      Passandolo by reference (essendo posizioni di memoria) mi basta
      scrivere questa riga senza riassegnazioni.*/
    (*del)(lst -> content);    

    /* La funzione del concella solo il membro "content" di un nodo
       La funzione lstdelone deve anche deallocare il nodo:*/
    free(lst);   
}