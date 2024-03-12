#include <stdio.h>
#include <stdlib.h>

typedef struct  node {
    int x;
    struct node *next;
} node;



NOTA: Tutte le funzioni scritte implementano un controllo sull allocazione. In particalare se uno dei 
      nodi non venisse allocato otterrei la stampa "bad node allocation" e la funzione restituirebbe 
      "(0)".
      Potrò quindi usara questa caratteristica per deallocare l intera lista in caso di mancata 
      allocazione di un nodo.
      ES:
      /*(...)*/
      if(!add_front(...))
      {
        deallocate(...);
        return();   or   exit();
      }


NOTA: Le funzioni di aggiunta nodi funzionano anche se la nostra lista nel main è vuota. Cioè se 
      node *root = NULL;


/*________________________________________LINKED LIST___________________________________________________
________________________________________________________________________________________________________*/
                                    CAPITOLO 1: INTRODUZIONE
                                    ________________________

- Una linked liste è un insieme di nodi costituiti da strutture dello stesso tipo colelgate fra loro:
Es:
    
int main(){
    /*dichiaro il mio nodo madre*/
    node root;
    
    /*Inserisco un valore denna variabile x*/
    root.x = 15,
    
    /*Alloco dinamicamente memoria del nodo successivo nella posizione di memoria
      puntata da next*/
    root.next = malloc(sizeof(node));
    if(!root.next)
        exit (1);

    /*Riempio il nuovo, ed ultimo, nodo*/
    root.next->x = 4;
    root.next->next = NULL;

    printf("%d", root.next->x);

    /*Non dimentico di fare il free dei nodi diversi dal primo*/
    free(root.next);
}










-------------------------------------------------------------------------------------------------------
                                        CAPITODO 2: ITERARE UNA LISTA
                                        ______________________________

- Consideriamo gli step necessare per l iterazione, rispettivamente, negli array e nelle liste.
  Come noteremo, per entrambe, saranno 3 
  
  ARRAY: (if loop)
  1) Inizializzazione del counter  :   i = 0;
  2) Exit condition                :   i < n;
  3) istruction step               :   i++;

  LINKED LIST
  1) /*Negli array dire "i = 0" significa dire "parti dalla prima posizione". In una link list il primo 
     elemento è la nostra root. Se per gli array l elemento che indica la prima posizione è un indice
     qui sarà un puntatore di tipo "node" (struct definita precedentemente). 
     Quindi la nostra */ "INIZIALIZZAZIONE" /*sarà*/: 

                                       node *current = &root;

  2) /*Come detto, l'ultima elemento di una lista dovrà essere sempre NULL. Quindi la nostra
      */ "CONDIZIONE D'USCITA" /*sarà*/

                                       current != NULL

  3) /*Quanto in un array scrivo i++ quello che sto facendo è passare da un elemento a quello successivo
       In una link list lo farò assegnando al nostro puntatore l'indirizzo successivo:*/

                                       current = current->next;

/*ES:*/
int main(){
    node root;
    root.x = 15,
    root.next = malloc(sizeof(node));
    if(!root.next)
        exit (1);
    root.next->x = 4;
    /*Aggiunto un nuovo elemento*/
    root.next->next = malloc(sizeof(node));
    if(!root.next->next)
        exit (1);
    root.next->next = 5;
    root.next->next->next = NULL;

   /*inizializzazione*/
   node *current = &root;
   /*Ciclo*/
   while (current!= NULL) {
    /*instruzioni...*/
    current = current->next;
   }
    /*NOTA: E' importante l'ordine in cui libero la memoria:
            DOVRO SEMPRE PARTIRE DALL'ULTIMO*/
    free(root.next->next);
    free(root.next);
}







-------------------------------------------------------------------------------------------------------
                        CAPITODO 3: AGGIUNGERE ELEMENTI (ALLA FINE DELLA LISTA)
                        ________________________________________________________

/*Creeremo una funzione che inserirà un elemento all'interno della link list.
  Nota: Decideremo anche dove inserirlo*/

"AGGIUNGERE UN NODO ALLA FINE DELLA LISTA:"
 L idea è quella di arrivare all ultimo nodo (che sarà NULL) e cambiarlo con il link al nostro 
   nuovo nodo che andremo a creare

Questa funzione avrà come argomendi:
  - Doppio puntatore al nodo madre
  - il valore che voglio inserire nella sezione dati del nodo

NOTA: perchè "node **root" ?
      Cosa è un doppio puntatore nodo ?
      Possiamo immaginarla come una fraccia  che, se dereferenziata, punta ad un altra freccia
      (cioè un altro puntatore). A sua volta questa freccia punta al nostro nodo madre.
      Quindi dereferenziando due volte ottengo il vero nodo madre.
      Mi serve come doppio puntatore perchè avrò bisogno della posizione di memoria del nodo 
      madre per poi assegnarlo al puntatore "curr" 



/*________________________________________________________________________________________________________
_____________________________________FUNZIONE: INSERIRE NODO ALLA FINE__________________________________*/

int add_end(node **root, int x) {
    /*Dichiaro un puntatore a nodo che mi servità nel ciclo while*/
    node *curr;
    
    /*Creo un nuovo nodo*/
    node *new_node = malloc(sizeof(node));
    if(!new_node)
    {
        ft_printf("Bad node allocaziorn")
        return (0);
    }
    
    /*Assegno all'elemento next di questo nodo "NULL". Perchè sara lui a diventare l'ultimo nodo */
    new_node->next = NULL;

    /*Aggiungo il valore passato alla funzione nella sezione dati di questo nuovo nodo*/
    new_node->x = x;

    /*Controllo se il nodo passato (madre) esiste. In caso cosi non fosse rendo "new_node" il nodo madre*/
    if (*root == NULL)
    {
        *root = new_node;
        return ;
    }

    /*Attraverso un ciclo itero fino alla fine della lista*/
    /*Inizializzo il puntatore a nodo creato con l'indirizzo del nodo madre 
     (*root è un indirizzo perchè passato come doppio puntatore)*/
    curr = *root;
    
    while (curr->next != NULL) /*NOTA: Non ho messo "curr != NULL" perchè altrimenti avrei iterato */
          curr = curr->next;         /*fino ad avere NULL. Io invece voglio che il mio nodo sia l'ultimo
                                       prima del NULL. Mi sto fermando un passo prima del NULL in sostanza*/
                   


     /*Usciti da questo loop "curr" sarà esattamente l'ultimo nodo, in quando il suo elemento 
       next conterrà NULL. 
       Per aggiungere il nuovo nodo alla coda della lista non dovrò far altro che modificare il 
       valore puntato dall'elemento "next" di "curr", facendolo passare da "NULL" a l'indirizzo di 
       "nex_node"*/
    curr->next = new_node;
    return (1); 
}
/*_________________________________________________________________________________________________________
__________________________________________________________________________________________________________*/




/******************************************************************************************************/
/*ES:*/ Come usare questa funzione nel "MAIN"                                                         //
                                                                                                      //
int main(){                                                                                           //
    /*Considerando che dovrò passare un doppio puntatore alla funzione non potrò scrivere             //
      "node root" ma avrò bisogno di un puntatore alla struttura.                                     //
      Questo perchè dovrò passare alla funzione l'indirizzo di memoria di root e non root stessa*/    //
    node *root;                                                                                       //
    node *curr;                                                                                       //
                                                                                                      //
    /*Alloco dinamicamente questo puntatore e gli assegno i valori. Avrò cosi creato il primo ed      //
      unico node della mia lista*/                                                                    //
    root = malloc(sizeof(node));                                                                      //
    if (root == NULL)                                                                                 //
    {
        ft_printf("Bad node allocaziorn")
        return (0);
    }                                                                                    //
    root->x = 15,                                                                                     //
    root->next = NULL;                                                                                //
                                                                                                      //
    /*Uso la funzione e aggiungo 2 nodi */                                                            //
    insert_end(&root, -2);                                                                            //
    insert_end(&root, 152);                                                                           //
                                                                                                      //
    /*Eseguo un ciclo che farà qualcosa*/                                                             //
    current = root;                                                                                   //
                                                                                                      //
    while (curr!= NULL) {                                                                             //
    /*instruzioni...*/                                                                                //
    current = current->next;                                                                          //
    }                                                                                                 //
}                                                                                                     //
/******************************************************************************************************/


NOTA: Considerando che la funzione ha il controllo di sicurezza sull assenza del nodo madre io posso 
      anche non assegnare il puntatore a root nel main. Posso cioè 
      "AGGIUNGERE UN ELEMENTO ALLA LISTA ANCHE SE NON CI SONO NODI ESISTENTI"

int main(){                                                                                           
    node *root                                                                                                                                                                             //
                                                                                                      
    /*senza popolare nel main il nodo madre, vado a farlo attraverso la mia funzione*/                
    root = NULL;                                                                                                                                                  //
    insert_end(&root, -2);                                                                            
                                                                                                      
    /* (...)  */                                                                                      
}                                                                                                     








-------------------------------------------------------------------------------------------------------
                                    CAPITODO 4: ELIMINARE ELEMENTI
                                    _______________________________

Nell esempio precedenti abbiamo aggiunto nodi alla lista, ma non abbiamo visto come deallocarli.
Lo faremo creando una funzione:
Supponiamo avere una lista composta da diversi nodi. 


NOTA 1) Anche qui userò un doppio puntatore perchè farò si che, alla fine della leallocazione, il mio 
        nodo base sarà il NULL pointer.
     
     2) Per liberare la nostra lista avremo bisogno di due variabili (puntatori), 
        i)  Una che punti al nodo che vogliamo liberare (temp che punta a curr)
        ii) Una che punti al nodo successivo.  (curr che verrà spostato su curr->next)
        Altrimenti, se dovessi distruggere semplicemente un nodo, non avrei modo di accedere allo spazio
        di memoria successivo che voglio deallocare

     3) Alla fine del ciclo entrambi i puntatori dovrò solo assegnare a root la posizione NULL:
        supponiamo di avere una lista composta da un solo nodo:
        - tem = curr -> temp conterrà la posizione del primo ed unico nodo 
        - curr = curr->next  --> curr sarà = NULL (perchè il nodo era solo 1) 
        - free (temp) -> libero temp 

        L unica cosa che mi rimane da fare, visto che il vero root, contiene ancora informazioni, 
        sarà assegnare a root la posizione di NULL; 
/*________________________________________________________________________________________________________
_____________________________________FUNZIONE: DEALLOCARE NODI__________________________________________*/
void dealloc(node **root){
    node *curr 
    /* Dichiaro il mio puntatore ausiliario in cui metterò la posizione di curr prima di spostarlo
       cosi da poterlo deallocare */
    node *temp;
    
    /*Inizializzo curr al nodo madre*/
    curr = *root;

    /*Fino a che la lista non è completamente finita (curr != NULL) mi sposto al suo interno*/
    while (curr != NULL){
        temp = curr;
        curr = curr->next;
        free (temp);
    }
    *root = NULL;
}
/*_____________________________________________________________________________________________________
________________________________________________________________________________________________________*/

/*______________________________________________________________________________________________________
__________________________________________VERSIONE RICORSIVA____________________________________________*/
void recursive_dalloc(Node** root) {

    node *curr;
    node *temp;

    cur = *root;
    temp = curr;
    curr = curr->next;
    free(temp);
    if(curr != NULL)
        recursive_dalloc(&curr);
    *root = NULL;
}
/*_____________________________________________________________________________________________________
________________________________________________________________________________________________________*/




/********************************NOTA IMPORTANTE: FUNZIONE PER CONTROLLARE LEAKS***************************/
Devo aggiungere:

#define _CRTDBG_MAP_ALLOC
#include <crtdgb.h>
#include <stdlib.h>

E poi, alla fine del mio codice:

int main(){
/*(....)*/


_CrtDumpMemoryLeaks();
return (0);
}
/********************************POTREBBE NON FUNZIONARE CON GCC*******************************************/











-------------------------------------------------------------------------------------------------------
                                CAPITODO 5: AGGIUNGERE ALL INIZIO DELLA LISTA
                                _____________________________________________
Supponiamo di avere una lista (anche vuota) e di voler aggiungere un nodo all inizio  

Il concetto è semplice: La nostra lista inizia sempre da roo, quindi non faremo altro che rimpiazzare 
il nodo madre con quello che vogliamo aggiungere e poi, a questo nodo, 
linkare la lista (linkando il precedentenodo madre)


/*______________________________________________________________________________________________________
__________________________________________FUNZIONE: ADD FRONT___________________________________________*/
int add_front(Node** root, int value) {
    node *new_node;

    new_node = malloc(sizeof(node));
        if (!nex_node)
        {
            ft_printf("Bad node allocaziorn")
            return (0);
        }
            
    new_node->x = value;
    new_node->next = *root;

    /*Arrivati a questo punto new_node è l'inkato al resto della lista ma la nostra root, nel main,
      rimarrebbe invariata. Dobbiamo quindi rimpiazzare il nodo madre assegnando al puntatore che 
      punta alla posizione nel nodo madre il nostro nuovo nodo */
    *root = new_node;
    return (1);
}
/*_____________________________________________________________________________________________________
________________________________________________________________________________________________________*/










-------------------------------------------------------------------------------------------------------
                      CAPITODO 6: AGGIUNGERE UN ELEMENTO DOPO UNO SPECIFICO NODO
                      __________________________________________________________

Supponiamo di avere una lista composta da tre nodi, la cui sezione dati contiene i valori 2, 3 e 5 
e di volerne aggiungere uno con il valore 7 fra i nodi contenenti i volori 2 e 4

1) La prima cosa da fare sarà creare un nodo con il valore 7 
2) Copierò poi il valore contenuto nella sezione dati del noto contenente il valore 2 in questo nuovo 
   elemento
3) Cambierò in fine puntatore presente nel nodo "2" per farlo puntare a questo nuovo nodo

NOTE: i) Questa volta, invece di passare il nodo madre passeremo il nodo al quale voglio concatenare
         il nuovo elemento
/*______________________________________________________________________________________________________
__________________________________________FUNZIONE: ADD AFTER___________________________________________*/
int add_after(node* node, int value) {
    /*Creiamo il nostro nuovo nodo*/
    node *new_node;

    node = malloc(sizeof(node));
    if (!nex_node)
    {
            ft_printf("Bad node allocaziorn")
            return (0);
    }
    new_node->x = value;
    new_node->next = node->next;

    /*Ora questi due nodi puntanto allo stesso nodo. Andrò quindi a modificare la sezione link 
      del noto passato*/
    node->next = new_node;
    return (1)
}
/*_____________________________________________________________________________________________________
________________________________________________________________________________________________________*/

ES:

int main()
{
    node *root = NULL;
    add_end(&root, 2);
    add_end(&root, 4);

    /*Così inserisco un nodo contenente 7 dopo il nodo contenente 2*/
    add_after(root, 7);
    /*Così inserisco un nodo contenente 5 dopo il nodo contenente 4*/
    add_after(root->next->next, 7);
}








-------------------------------------------------------------------------------------------------------
                            CAPITODO 7: AGGIUNGERE UN NODO IN MODO ORDINATO
                            _______________________________________________
Supponiamo di avere una lista contenente i valori 2, 7, 9 e di voler aggiungere un nodo con il valore 8
in modo ordinato.
Per farlo dovrò iterare nella lista finchè il valore contenuto in uno dei nodi non risulta <= a quello
contenuto nel nuovo nodo.
In questo ragionamento c è un caso particolare da tenere in considerazione, quando il valore contenuto
nel nuovo nodo è <= del nodo madre 

NOTA: Questo algoritmo "funziona solo se ho già una lista ordinata"

NOTA: Se voglio aggiungere elementi in "ordine discendente" basterà invertire >= con "<="

/*______________________________________________________________________________________________________
__________________________________________FUNZIONE:ADD_SORTED __________________________________________*/
int add_sorted(node **root, value)
{
    node *curr;
    
    /*Considero prima i casi speciali compreso di controllo */
    if (*root == NULL || (*root)->next >= value)
    {
        if (!add_front(root, value))
            return (0);
        return (1);    
    }
    curr = root;
    while (curr->next != NULL)
    {
        /*Verifico la sezione dati del nodo successivo e, se risulta >= a value, inserisco il nodo 
          dopo di lui. OSS: mi basta scrivere break perchè ho add_last in fonto*/
        if (curr->next->x >= value)
            break;
        curr = curr->next;       
    }
    /*Infine, se il valore che voglio inserire è maggiore di tutti gli elementi presenti nella lista
      (e quindi non si verifica mai la condizione elemento del vecchio nodo >= value),
      dovrò inserire questo nuovo nodo alla fine */
    if (!add_after(curr, value))
        return (0);
    return (1);
}
/*_____________________________________________________________________________________________________
________________________________________________________________________________________________________*/








-------------------------------------------------------------------------------------------------------
                            CAPITODO 8: ELIMINARE UN ELEMENTO DALLA LISTA
                            _____________________________________________
Supponiamo di avere 3 nodi e di voler eliminare quello mediano. Per farlo dovrò far puntare il primo al 
terzo (copiando l elemento next del secondo in quello del primo).
Dovrò poi eseguire il free dell elemento eliminato.

NOTA: Questa funzione "elimina SOLO il primo nodo che presenta il valore VALUE".
      

/*______________________________________________________________________________________________________
__________________________________________FUNZIONE: remove_node_________________________________________*/
void remove_node(node **root, int value)
{
    node *curr;
    node *to_remove;

    /*controllo su una lista vuota*/
    if (*root == NULL)
        return ;
    /*Nel caso in cui stia cercando di rimuovere il nodo madre*/
    if ((*root)->x = value)
    {
        to_remove = *root;
        /*root diventa il "prossimo elemento" della linked list*/
        *root = (*root)->next
        free(to_remove);
        return ;
    }   
    curr = *root;
    
    
    /*NOTA: Se, nel tantivo di rimuovere l'ultimo nodo della lista la funziona da SEGFAULT, provare con
            while (curr != NULL && curr->next != NULL)*/
    while (curr->next != NULL)
    {
        /*Controlliamo se il valore contenuto nel nodo successivo  a curr è quello che cerchiamo*/
        if (curr->next->x == value)
        {
            /*salvo la posozione del nodo che voglio eliminare in una variabile*/
            to_remove = curr->next;
            /*skippo il nodo che voglio eliminare ed assegno a curr->next la posizione nel nodo successivo*/
            curr->next = curr->next->next;
            /*libero il nodo da eliminare*/
            free(to_remove);
            return ;
        }
        curr = cur->next;
    }
}
/*_____________________________________________________________________________________________________
________________________________________________________________________________________________________*/





















-------------------------------------------------------------------------------------------------------
                                    CAPITODO 12: DOUBLY LINKED LIST
                                    ________________________________
A differenza delle linked list, le doubly linked list hanno al loro interno due puntatori a node: 
1) Puntatore al nodo successivo 
2) puntatore al nodo precedente

NOTA: 
- Il nodo madre della nostra d.l.l avra un puntatore a NULL come nodo precedente
- Possiamo considerarle come due liste uno sopra l altra in cui possiamo andare da sinistra a destra
  o da destra a sinistra.
  Quindi, per chiarezza, chiamero:
  "il primo nodo a sinistra" = "tail" = nodo madre
  "il primo nodo a destra" = "head"

/*______________________________________________________________________________________________________
_________________________________________________ES: STRUCT_____________________________________________*/
typedef struct node {
    int x;
    struct node *next;
    struct node *prev;
} node;
/*_____________________________________________________________________________________________________
________________________________________________________________________________________________________*/


Vediamo un esempio di come creare una doubly link list
/*______________________________________________________________________________________________________
_________________________________________________ES: IMPLEMENTAZ________________________________________*/
int main(){
    node *tail;
    
    /*Alloco il nodo madre tail*/
    tail = malloc(sizeof(node));
        if(!tail)
            return (0);
    /*popolo il primo nodo*/
    tail->x = 1;
    tail->prev = NULL;
    tail->next = malloc(sizeof(node)); /*creo il nodo successivo*/
        if (!tail->next)
            return (0);
    
    /*popolo il nuovo nodo*/
    tail->next->x = 3;
    tail->next->prev = tail;  /*puntatore al nodo precedente*/
    tail->next->next = malloc(sizeof(node)); /*creo il nodo successivo*/
        if(!tail->next->next)
            return (0);

    /*popolo il terzo nodo*/
    tail->next->next->x = 7;
    tail->next->next->prev =  tail->next;
    tail->next->next->next =  NULL;
}


FINIRE VIDEO MINUTO 9.06
/*_____________________________________________________________________________________________________
________________________________________________________________________________________________________*/