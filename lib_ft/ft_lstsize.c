#include <stdio.h>
#include <stdlib.h>

/*-------------------------------------NODO-------------------------------*/
typedef struct      s_list
{
    void            *content;
    struct s_list   *next;    /*-> struttura autoreferenziale*/
}                   t_list;
/*------------------------------------------------------------------------*/

/* lst = inizio della lista*/
int ft_lstsize(t_list *lst)
{
    int     count;
    t_list  *head_lst;

    count = 0;
    head_lst = lst;
    while (head_lst && ++count)
        head_lst = head_lst -> next;
    return (count);    
}