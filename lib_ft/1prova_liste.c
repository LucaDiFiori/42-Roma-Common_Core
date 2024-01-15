#include <stdio.h>
#include <stdlib.h>

/*-------------------------------------NODO-------------------------------*/
typedef struct      s_list
{
    int             content;
    struct s_list   *next;    /*-> struttura autoreferenziale*/
}                   t_list;
/*------------------------------------------------------------------------*/

/*-----------------------------------FUNZIONE-----------------------------*/
t_list  *ft_lstnew()
{
    /* Creo un puntatore di tipo "t_list" (cioe' "struct s_list")
       che punterà ad un nuovo nodo.
       
       OSS1: Un "nuovo nodo" è una nuova variabile s_list che risulterà
            collegata alla prima grazie al membro "struct s_list *next"
            Che è un puntatore alla "struttura stessa, cioè allo stesso 
            tipo "struct s_list" da me creato che identifica la struct */

    /* OSS2: Per questo ho dato due nomi a questo type. Avrei potuto anche
             usare solamente "s_list", ma per chiarezza rinomino tutto
             "t_list": intendendo una struct s_list composta da un int
                       ed un puntatore a struct s_list*/        
    t_list  *new_node;


    /* Attraverso questo puntatore alloco memoria per il nuovo nodo*/
    new_node = (t_list *)malloc(sizeof(t_list));

    /*Al membro "content" del nuovo nodo assegno il valore 5*/
    new_node -> content = 5;

    /*termino la lista assegnando NULL al membro next (il puntatore che dovrebbe
       contenere l'indirizzo del nodo successivo)*/
    new_node -> next = NULL;
    return (new_node);
}

/*--------------------------------------MAIN-------------------------------*/
int main()
{
    t_list *head_nodo_1;
    int     nb = 3;

    /*Creo il primo nodo allocando memoria*/
    head_nodo_1 = (t_list *)malloc(sizeof(t_list));

    /* Riempio il primo nodo. Nell'esempio assegno 3 al membro dati*/
    head_nodo_1 -> content = nb;
    /* Al membro link assegno l'output della funzione*/
    head_nodo_1 -> next = ft_lstnew();


    /*Stampo il valore contenuto nel membro dati del secondo nodo
      (al quale è stato assegnato 5 nella funzione)*/

    /*  OSS: Per stamparlo devo usare questa notazione
             
             °"head_nodo_1 -> next" 
               mi restituisce il valore di memoria
               contenuto nel campo "next" del primo nodo, cioè la posizione
               di memoria del secondo nodo.
              
             ° Applicando di nuovo "->" 
               ottengo il valore contenuto nel membro successivo (alias dell'operatore (*)):
               "-> content" mi da il valore contenuto nel membro content del secondo membro
    */
    printf("%d", head_nodo_1 -> next -> content);

}
