#include <stdio.h>
#include <stdlib.h>

/*-------------------------------------NODO-------------------------------*/
typedef struct      s_list
{
    void            *content;
    struct s_list   *next;    /*-> struttura autoreferenziale*/
}                   t_list;
/*------------------------------------------------------------------------*/


t_list  *ft_lstnew(void *content)
{
       
    t_list  *new_node;

    new_node = (t_list *)malloc(sizeof(t_list));
    if (!new_node)
        return (NULL);
    new_node -> content = content;
    new_node -> next = NULL;
    return (new_node);
}


/*------------------------------------------------------------------------
Iterates the list ’lst’ and applies the function
’f’ on the content of each node. Creates a new
list resulting of the successive applications of
the function ’f’. The ’del’ function is used to
delete the content of a node if needed.

lst: The address of a pointer to a node.
f: The address of the function used to iterate on the list.
del: The address of the function used to delete
the content of a node if needed.
-------------------------------------------------------------------------*/
t_list *ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
    t_list  *new_lst_node;
    t_list  *head_node;

    if (!lst || !f || !del)
		return (NULL);

    /*------------------------------------------------------------------------
    NUOVO NODO TESTA
      assegno al puntatore new_lst_node un nuovo puntatore con il content
      modificato che rappresenterà la testa della mia nuova lista.
      -----------------------------------------------------------------------*/
    new_lst_node = ft_lstnew(f(lst -> content)); 
    if (!new_lst_node)
			return (NULL);

    /*CONSERVO LA TESTA DELLA NUOVA LISTA
      Lo faccio assegnando al puntatore head_node il puntatore
      new_lst nodecosi da poter conservare la posizione dell'inizio della lista
      per poi restituirla nel return*/
    head_node = new_lst_node;  
    
    /* Mi serva come verifica condizione del while "lst->next" perche se avessi usato solo lst (probabilmente) avrebbe fatto un passaggio in piu. Cosi io verifico direttamente se il nodo successivo esiste o no ed in caso procedo */
    while (lst -> next)
    {
        /*PASSO AL NODO SUCCESSIVO DELLA VECCHIA LISTA*/  
        lst = lst -> next;

        /*CANCELLO IL CONTENUTO DEL NODO VECCHIO SE ESISTE*/
        if (!(lst -> content))
            del(lst -> content);
                
        /*-----------------------------------------------------------------------
        CREO UN NUOVO NODO CON IL CONTENUTO MAPPATO
        Al membro next (che ricordiamo essere un puntatore "struct s_list *next")
        del nuovo nodo assegno un nuovo nodo che creo con la funzione lstnew
        OSS: Considerando che la funzione f mi restituisce il "content" modificato
             lo uso direttamente come argomento di lstnew.
         ---------------------------------------------------------------------*/
        new_lst_node -> next = ft_lstnew(f(lst -> content));

          /*------------------------------------------------------------------
          VERIFICO L'ALLOCAZIONE
          Se la creazione del nodo non ha avuto usccesso (cioè non ho messo
          niente all'interno di new_lst_node -> next) allora
          libero la memoria allocata fino ad ora con la funzione lstclear
          ed esco con NULL

          OSS: Devo liberare "head_note" perchè è questo il puntatore che punta
               alla testa della lista.
               Andando a modificare new_lst_node, esso potrebbe non star piu
               puntando li, ma aall'ultimo membre della nuova lista che stava
               provando a creare
          ------------------------------------------------------------------*/
          if (!new_lst_node -> next)
          {
              ft_lstclear(&head_node, del);
              return (NULL);
          }
        
        /*--------------------------------------------------------------
        AGGIUNGO IL NUOVO NODA ALLA FINE DELLA NUOVA LISTA
        Assegno al puntatore "new_lst_node" la posizione di memoria del nuovo
        nodo creato, così da poterne generare di nuovi
          OSS: L'elemento "new_list_node -> next" contiente NULL
               (perchè la funzione per creare nuovi nodi funziona cosi)
               Ma, ad ogni ciclo questo NULL verrà sostituito con
               l'indirizzo del nuovo nodo che verrà generato
        ----------------------------------------------------------------*/
        new_lst_node = new_lst_node -> next;
    }
    return (head_node);
}
