#include <stdio.h>
#include <stdlib.h>

/*-------------------------------------NODO-------------------------------*/
typedef struct      s_list
{
    void            *content;
    struct s_list   *next;    /*-> struttura autoreferenziale*/
}                   t_list;
/*------------------------------------------------------------------------*/

/* ° **lst = puntatore al puntatore al primo nodo 
             (contiene l'indirizzo di memoria del puntatore
              che punta al primo nodo).
     
     *new  = puntatore al nodo da aggiungere */

/*OSS: Con questa funzione sto cercando di aggiungere un nodo all'inizio
       cambiando direttamente il valore contenuto del puntatore.
       
       Avrei potuto fare lo stesso con una funzione fatta cosi:
       ft_lstadd_front(t_list *lst, t_list *new){
        new->next = lst->next;
        lst->next = new;
       }
       */ 
void    ft_lstadd_front(t_list **lst, t_list *new)
{
        if (!lst || !new)
        return ;    
    /* Al membro link del nuovo nodo assegno il valore contenuto
       nel puntatore che punta alla testa della lista (cioè
       la posizione di memopria della prima lista)*/
    new -> next = *lst;

    /*Considerando che lst e' un puntatore che punta al primo
     elemento della lista (per def da esercizio) ora devo
     assegnargli il valore della nuova lista head*/
    *lst = new;

}
