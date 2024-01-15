#include <stdio.h>
#include <stdlib.h>

/*-------------------------------------NODO-------------------------------*/
typedef struct      s_list
{
    void            *content;
    struct s_list   *next;    /*-> struttura autoreferenziale*/
}                   t_list;
/*------------------------------------------------------------------------*/

/*Deletes and frees the given node and every successor of that node*/
/*lst: The address of a pointer to a node.
del: The address of the function used to delete the content of the node.
*/

void    ft_lstclear(t_list **lst, void (*del)(void *))
{
    t_list	*temp_node;

	if (!lst || !del)
		return ;

    /*--------------------------------------------------------------------
      Finchè il puntatore **lst non punta a NULL
    ---------------------------------------------------------------------*/  
    while(*lst)
    {
        /*----------------------------------------------------------------------
          nel nodo temporaneo metto l'indirizzo nel nodo successivo a lst
          (*lst) = indirizzo di memoria di lst  
          (*lst) = -> next elemento next della variabile struct puntata da **lst
        -----------------------------------------------------------------------*/
        temp_node = (*lst) -> next;

        /*applico la funzione lstdelone che cancella un nodo e libera la memoria
          OSS: passo solo "del" perche lstdelone ha gia al suo interno la del    stessa, alla quale passa il membro content della lista passata */
        ft_lstdelone((*lst), del);
        
        /*----------------------------------------------------------------------
          all'interno del doppio puntatore **lst metto il valore di memoria
          del puntatore al membro successivo (assegnato precedentemente a temp_node).
        -----------------------------------------------------------------------*/
        *lst = temp_node;
    }
}
