#include <stdio.h>
#include <stdlib.h>

/*-------------------------------------NODO-------------------------------*/
typedef struct      s_list
{
    void            *content;
    struct s_list   *next;    /*-> struttura autoreferenziale*/
}                   t_list;
/*------------------------------------------------------------------------*/

/* *lst puntatore all'inizio della lista*/
t_list  *ft_lstlast(t_list *lst)
{
    t_list  *last_node;
    
    if (!lst)
        return (NULL);
    
    /* Inizializzo last_node all'inizio della lista lst*/
    last_node = lst;    
    
    /* Usiamo "last_node -> next" come condizione booleana 
       nel while: Fino a che non incontrerà NULL entra nel ciclo*/
    while (last_node -> next)
        last_node = last_node -> next;
    return (last_node);    
}