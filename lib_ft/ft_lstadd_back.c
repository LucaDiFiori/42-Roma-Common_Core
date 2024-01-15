#include <stdio.h>
#include <stdlib.h>

/*-------------------------------------NODO-------------------------------*/
typedef struct      s_list
{
    void            *content;
    struct s_list   *next;    /*-> struttura autoreferenziale*/
}                   t_list;
/*------------------------------------------------------------------------*/

/* 
lst = indirizzo del puntatore al primo elemento della lista
new = indirizzo al nuovo elemento
*/
void  *ft_lstadd_back(t_list **lst, t_list *new)
{
    t_list  *last_node;

    /*Se il puntatore a puntatore non punta a niente esco*/
    if(!lst)
        return;
    
    if (*lst)
    {
        /*Alla funzione lstlast passo il valore di memoria contenuto
         nel puntatore all'inizio della lista. Ora last_node contiene l'ultimo nodo.*/
        last_node = ft_lstlast(*lst);
        
        /* in coda a last node aggiungo new*/
        last_node -> next = new;
    }
    
    /*se il puntatore a puntatore lst non contiene nulla (quindi lst e' vuota)
     inserisco new come primo/ultimo elemento*/
    else
        *lst = new;
}




