#include <stdio.h>
#include <stdlib.h>

/*-------------------------------------NODO-------------------------------*/
typedef struct      s_list
{
    void            *content;
    struct s_list   *next;    /*-> struttura autoreferenziale*/
}                   t_list;
/*------------------------------------------------------------------------
Crea un nuovo nodo di una lista.
Per farlo bisogna allocare uno spazio di memoria di dimensione t_list.
-----------------------------------FUNZIONE-----------------------------*/
t_list  *ft_lstnew(void *content)
{
    /* Creo un puntatore di tipo "t_list" (cioe' "struct s_list")
       che punterà ad un nuovo nodo.
       
       OSS1: Un "nuovo nodo" è una nuova variabile s_list che risulterà
            collegata alla prima grazie al membro "struct s_list *next"
            Che è un puntatore alla "struttura stessa, cioè allo stesso 
            tipo "struct s_list" da me creato che identifica la struct */

    /* OSS2: Per questo ho dato due nomi a questo type. Avrei potuto anche
             usare solamente "s_list", ma per chiarezza rinomino tutto
             "t_list": intendendo una struct s_list composta da un puntatore
                       a void ed un puntatore a struct s_list*/        
    t_list  *new_node;


    /* Attraverso questo puntatore alloco memoria per il nuovo nodo*/
    new_node = (t_list *)malloc(sizeof(t_list));
    if (!new_node)
        return (NULL);

    /*Al membro "content" del nuovo nodo assegno il valore del membro "content"
      del nodo precedente*/
    new_node -> content = content;

    /*termino la lista assegnando NULL al membro next (il puntatore che dovrebbe
       contenere l'indirizzo del nodo successivo)*/
    new_node -> next = NULL;
    return (new_node);
}
