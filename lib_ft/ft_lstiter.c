#include <stdio.h>
#include <stdlib.h>

/*-------------------------------------NODO-------------------------------*/
typedef struct      s_list
{
    void            *content;
    struct s_list   *next;    /*-> struttura autoreferenziale*/
}                   t_list;
/*------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
Iterates the list ’lst’ and applies the function’f’ on the content of each node.

lst: The address of a pointer to a node.
f: The address of the function used to iterate on the list.
-------------------------------------------------------------------------------*/
void ft_lstiter(t_list *lst, void (*f)(void *))
{
    while(lst)
    {
        (*f)(lst -> content);
        
        /*inizializzo il puntatore al nodo con l'indirizzo 
          del nodo successivo*/
        lst = lst -> next; 
    }
}