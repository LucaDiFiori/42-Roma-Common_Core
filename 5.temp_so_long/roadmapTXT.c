LEGGENDA:
* aggiornate e uguali
+ aggiunti al file .h o al Makefile se file.c

NOTE------------------------------------------------------------------------------------------------------------------------------------
- Non devo fare free sul puntatore inizializzato a mlx_init() perche  questa 
  funzione alloca cose e le libera solo quando faccio close. Se lo freeo prima 
  le lascerei aperte ed avrei leaks

- Liberare tutti i puntatori (qualsiasi puntatore)  

-Perche conto gli zeri con n_count: Per la logica di piazzamento del nemico 
                                    pPer posizionarlo in maniera corretta devo sapere
                                    la posizione di ogni zero, cosi che, quando selezionero 
                                    una posizione casuale per il nemico, potro 
                                    verificare se intorno a lui ci sono zeri (e quindi
                                    spazio per far passare il personaggio)

FUNZIONI (di matteo)--------------------------------------------------------------------------------------------------------------------
CLOSE.c
- 1) clean_matric -> fa free sulla matrice
- 2) ft_closse -> a seconda del type passato fa un free diverso o 
     un errore diverso  
- 16) print_error -> stampa un messagio d errore  // print_error(utils.c)

23) ft_destroy -->  (chiama mlx_destroy_image) (Distrugge il puntatore dell immagine)
24) ft_xclose  -->  (richiama ft_close) mi serve per la funzione mlx_loop per chiudere 
                                       (vedi la funzionegame_init nel file game.c)
                                       Questo perche credo la funzione hook necessiti di 
                                       un puntatore ad una funzione come argomento 



ENEMY.c
25) aux_enemy  --> verifica che la posizione del nemico sia valida (es se alla sua destra c e  uno zero, sotto anche etc)
                    (prima devo generare randomicamente la posizione del nemico)
                    (se la posizione va bene mette la flag = 1 (forse non serve))
                    - Setta sulla mappa una X nlla posizione in cui metto il personaggio
                    - riaumento npath (visto che lo avevo azzerato in path.c)

26) enemy      --> Continua a ciclare finche  c e  spazio per i nemici
                  (NOTA: npath rappresenta il numero di zeri nella matrice)
                  - WHILE: fino a che aux_rand (copia del numero di zeri) e  diverso da npath (valore che viene aumentato 
                                    ad ogni firo del while dalla funzione aux_enemi), genera randomicamente un valore 
                                    compreso fra zero ed il numero di zeri presente in pamma.
                                    Chiama la funzione aux_enemy passandogli questo valore e la funzione aux_enemy accedera  a quella
                                    posizione dellárray (che contiene le coordinate di uno zero presente in mappa) e verifica se ci puo 
                                    piazzare un nemico.
                                    (cioe : supponiamo di aver contato 10 zeri. Ne ho salvatgo le posizione nell array
                                            Questa funzione scorre l array e prende la posizione do qiello zerop. Controlla 
                                            se intorno a lui ci sono le condizione per mettere un nemico con la funzioone 
                                            aux_enemy. Se ce  lo mette altrimenti no e passa al prossimo elemento dell array.
                                            Questo array e grande quanti zeri ci sono sulla mappa, quindi questo ciclo 
                                            adra avanti per numro_di_zero-volte)



GAME.c
- 3)set_game --> inizializza tutto a zero // set_var_to_zero(launch.c)

26) aux_map  --> (chiamaimg_win) controlla la posizione della matrice in cui si trova e, a seconda di che lettera e 
                                assegna l immagine corrispondente (con la funzione img_win)
27) draw_map --> "disegna la mappa" chiamando la funzione aux_map in un ciclo per ogni posizione della matricde.
                  dopodiche  chiama mlax_string_put per stampare le mosse a schermo

- 4)game_init -> inizializza l ambiente e lancia la finestra(launch.c)                            
                 - Carica le immagine (le assegna della sezione puntatore della struct tile corrisondente)
                 - chiama drow map per disegnare la mappa (con le immagini precedentemente caricate da image_load)
                 
                - mlx_loop_hook(game->mlx, *loop, game)
                Questa riga imposta una funzione di callback denominata loop che verrà chiamata durante 
                ogni iterazione del ciclo di eventi di MiniLibX. La funzione loop e   responsabile di 
                aggiornare lo stato del gioco, gestendo il conteggio dei loop, la raccolta di monete e il disegno 
                della mappa.
                (Posso vedere mlx_loop_hook e mlx_key_hook come complementari:
                Quando c e  un comando esegue mlx_key.. quando non c e  un comando esegue questo)
                ()
                
               - mlx_key_hook(game->win, *input_key, game)
                Questa riga imposta una funzione di callback denominata input_key che verrà chiamata quando 
                si verificano eventi di pressione di tasti nella finestra specificata (game->win). 
                La funzione input_key e  responsabile di gestire gli input da tastiera.
                (resta in attesa che un tasto venga premuto e, quando viene premuto esegue input key(funzione che
                 controlla che tasto e  e, a seconda del tasto che ho premuto, fa qualcosa))
                
                - mlx_hook(game->win, 17, 0, *ft_xclose, game)
                Questa riga imposta una funzione di callback denominata ft_xclose che verrà chiamata 
                quando si verifica l evento di chiusura della finestra (17 rappresenta l evento di chiusura). 
                La funzione ft_xclose sembra essere responsabile di gestire l evento di chiusura della finestra.
                (Questa riga fa chiudere il programma quando premi esc. Resta in attesa della pressione di esc, 
                 quando viene fatto esegue la funzione ft_xclose)
                
                - mlx_loop(game->mlx)
                Questa riga avvia il ciclo principale degli eventi di MiniLibX. 
                Il programma rimarrà all interno di questo ciclo, attendendo e gestendo gli eventi 
                finché l applicazione non viene chiusa.                                 *****AGGIUNGERE*******************************

                perche in questo ordine ? forse perche il primo giro lo fa fare mlx_init (funzione di mlx)
                 
28) loop  -->(chiama loop_coin, mlx_xpm_file_to_image, draw_pam)
             -Il primo if decide la velocita  del loop (fino a che loop ++ non e arrivato a mille chiude la funzione
             per rallentarlo) (loop e  una variabile che serve solo a questo)
             NOTA: Al posto di quel ciclo posso usare la funzione di time stamp: mfabbriconi -> time -> frame.c 
                  Oss: devo inizializzarla a zero nella funzione che setta tutto a zero (vedi il suo git)
             
             - setto la variabile loop a zero  cosi quando richiamo la funzione ricomincia a rallentare il programma
               con il primo if 
             - chiamo la funzuione loop coin
             - se il numero coin e  diventato zero sostituisce l immagine della porta con quello della frutta
             - ad ogni chiamata ridisegna la mappa (modificata) (DFORSE QUESTA E  SPOSTATA IN HOOKS)



             NOTA: Le funzioni di loop funzionano solo una concatenata all altra. Devo quindi inizializzare 
                   l ambiente di gioco, la finestra etc
HOOKS.c
29) ch  -->  controlla e stampa a schermo quello che accade nella partita 
30) check_exit  --> (chiama ft_xclose)  (se premo esc chiude)
31) imput_key  --> (chiama move_pg, mlx_destroy_image, check_exit, mlx_clear_windows, draw_map)
                   In base al tasto inserito modifica l ememnto cortdinata x ed y nella struct del personaggio
                   (se la funzione move_pg ha restituito 1)
                   OSS: Se premo destra o sinistra cambia immagine 
                   - verifica 

32) move_pg  --> sposta il personaggio (a seconda del tasto premuto scrive 0 dove era il personaggio e mette
                                        la P nella casella selezionata con i tasti direzionali)



MAPS.c (valid matrix e chech matrix da sistemare)
- 5) check_name_game -> controlla se le mappe hanno .ber
- 6) set_dim_map -> Questa funzione restituisce 1 se la mappa 
                    e  valida -1 se non lo e 
                    - riempie i parametri altezza e lunghezza della variabile 
                      struct map
- 7) set_matrix -> legge una line per volta con get_next_line 
                   e alloca le righe nella matrice 
- 8) valid_matric -> controlla la validita  della matrice 
                    (es se c e  piu di un personaggio etc))
- 9) check_matrix -> esegue altri controlli 
                   (es che i muri siano tutti composti da 1 o che 
                   non ci siano lettere non accettate) 
                   e posiziona le "piastrelle"     



PATH.c (floadfil per verificare il percorso della mappa)
- 33) dup_matrix
- 19) aux_check_path -> controlla che maoppa sia valida 
                      (ricorsivamente riempie tutto di  "1")  
                    
                    ultimo if: Se la posizione in cui mi trovo e 
                     0  allora diminuisco "npath" (che uso
                    come indice dell arry) e salvo nella casella
                    npath-- dellárray di tile la posizione x ed y dello
                    zero che ho appena incontrato

- 20) check_path ->  Questa e  la funzione che usa le altre due: 
                      controlla che l uscita sia diventata 1
                      e che le coin siano diventate 1 
                      in piu  qui alloco l array di struct tile che
                      conterra  la posizione degli zeri
                                                                          

- 21) check_coin -> controlla che le posizione in cui c erano le 
                  coin siano diventate 1



STRUCTURES.h 
- 10) s_image (puntatore all immagine, altezza in pxl e spessore in pxl)
- 11) s_tile
- 12) s_map
- 13) s_game



TILE.c
- 14) check_tile -> controlla che il valore passatole sia uno dei caratteri 
                  validi (es 0, 1 P etc) (questa viene usata in check_matrix)
- 15) set_tile -> a seconda di che lettera e  riempie la struct corrispondente 
                  (es se la lettera e  P riempira  gli elementi della struct 
                  personaggio)

34)image_load  --> (chiama mlx_xpm_file_to_image) prende il puntatore di mlx, path della texture etc 
                   e carica l immagine nel puntatore all immagine della variabile corrispondete al personaggio, coin etc
                                                   
35) img_win  --> (chiama mlx_xpm_file_to_image) chiama la funzione mlx_put_image_to_window 
36) loop_coin  --> -inizia cancellando l immagine della coin gia  presente 
                   - la variabile movcoin va da 0 a 4. Mi serve per "costruire il path" dell immagine 
                     (SPIEGAZIONE: nella cartella delle immagine ho 5 immogini della moneta per farla muovere.
                                   Il percorso sara : .../../star"numero".
                                   L idea e  quella di costruire il percorso con struop e stjoin mandando avanti
                                   il contatore movcoin.
                                   Ad ogni giro avro : .../../star1.
                                                      .../../star2. etc
                                   quando movcoin arriva a 5 la resetta )
                   - costruisce il nome del percorso
                   - nell elemento immagine della coin mette l immagine corrispondente a quel frame (da 0 a 4)                                    
                   - chiama mlx_put_immage_to_window
                   - aumenta movcoin++


NON SONO FINITE LE FUNZIONI
_____________________________________________________________________________________________________________________________________
_____________________________________________________________________________________________________________________________________




FUNZIONI (mie)----------------------------------------------------------
map_utils.c +
14) check_char -> controlla che il valore passatole sia uno dei 
                  caratteri validi (es 0, 1 P etc)                   (+/) 

5) check_ber_file -> controlla se le mappe hanno .ber                (+/*)                  

close_utils.c
16) print_error    -> stampa un messagio d errore                      (+/)
1) free_map_matrix -> fa free sulla matrice                         (+/)
2) quit_and_free   -> a seconda del type passato fa un free 
                      diverso o un errore diverso                     (+/)
ft_destroy         -> chiude quando non ci sono errori 
                      chiama le funzioni destroy   


structures.h +
10) map 
11) skin 
12) asset 
13) gioco 

map_checks.c +
6) check_mapsize -> controlla se la dimensione della mappa e  giusta (+/)
7) matrix_generator -> legge una line per volta con get_next_line 
                       e alloca le righe nella matrice               (+/)
8) p_e_c_count -> controlla la che la P e la E siano solo 2  
                  in tutta la mappa e che il numero massimo
                  di collezionabili non dumeri N_COLLECTABLE          (+/)
9) check_map_and_set_tile -> esegue altri controlli 
                                (es che i muri siano tutti composti 
                                da 1 o che 
                                non ci siano lettere non accettate
                                attraverso la funzione "tile_check) 
                                e posiziona le "piastrelle" (attraverso
                                la funzione set_tile)                 (+/)
22) matrix complete checker -> Chiama una alla volta le funzionei di 
                               controllo. Quando uno di questi test 
                               fallisce, la funzione restituisce 0    (+/)

launch.c +
3) set_var_to_zero -> inizializza tutto a zero                        (+/)
4) launch_windows -> inizializza l ambiente 
                     e lancia la finestra                             (+/)

maps.c +

tile.c +
15) set_tile_location -> a seconda di che lettera e  riempie la struct corrispondente 
                         (es se la lettera e  P riempira  gli elementi della struct 
                         personaggio)                                 (+/)
 
 path_check.c +
 18) matrix_duplicator -> duplica la matrice                          (+/)
 19) trace_all_path    -> controlla che maoppa sia valida 
                          (ricorsivamente riempie tutto di  "1")      (+/)
 20) check_path ->  Questa e  la funzione che usa le altre due:       (+/)
                    controlla che l uscita sia diventata 1
                    e che le coin siano diventate 1                         

hook_player
int		inputs(int key, t_game *ptr_game)       -> legge gli imput e chiama altre funioni 
                                                 per verificare se puo spostare i personaggio
                                                 in caso di riuscita lo sposta 

static int	check(t_game *p_g, int x, int y)  ->  - Verifica cosa c è nella casella in cui 
                                                    voglio spostarmi e, a seconda del contenuto,
                                                    esegue un azione.
                                                  - restituisce 1 se lo spostamento è valido, 
                                                    0 se non lo è 

static void	move(t_game *p_g, int n_x, int n_y/*, int fr_bk*/) -> cambia i valori nella matrice e 
                                                                  modifica le immagini  

int	check_and_move(t_game *p_g, int key, int x, int y)     -> chiama chech e move                                                                                                                    



 /*____________ORDINE DELLE FUNZIONI__________________________________________________________
1) check_mapsize: Legge il file, esegue controlli preliminari e riempie i parametri di altezza 
				  e lunghezza della matrice
2) matrix_generator: genera la matrice
3) matrix_complete_checker: Chiamata nel "return" di "matrix_generator". Questa funzione 
							chiamerà in ordine le successive
4) p_e_c_count
5) check_map_and_set_tyle
6) check_path (contenuta in path.c)
_______________________________________________________________________________________________________*/ 





________________________________________________________________________________________________________
______________________________________________FUNZIONI MLX______________________________________________
                                              .SH SEE ALSO
                         mlx(3), mlx_new_window(3), mlx_pixel_put(3), mlx_new_image(3)
                                                   or
              https://harm-smits.github.io/42docs/libs/minilibx/prototypes.html#mlx_xpm_file_to_image

-----------------------------------------AMBIENTE GRAFICO E FINESTRA-------------------------------------
MLX_INIT:
______________
> PROTOTIPO:      void *mlx_init();


> DESCRIZIONE:    mlx_init: Questa funzione inizializza l ambiente MinilibX e restituisce un puntatore 
                  (void) a un istanza di questa libreria che può essere utilizzato per accedere alle 
                  funzionalità offerte da MinilibX.

> UTILIZZO:       #include <mlx.h>

                  int main() {
                  // Inizializzazione dell ambiente MinilibX
                  void *mlx_ptr = mlx_init();

                  // Altre inizializzazioni e utilizzo dell istanza MinilibX
                  return 0;
                  }    


                                      *************************************


_______________________________________________________________________________________________________________
MLX_NEW_WINDO:
_______________________________________________________________________________________________________________
> PROTOTIPO:      void *mlx_new_window(void *mlx_ptr, int width, int height, char *title);

                  CON:
                  - mlx_ptr: è un puntatore all istanza di MinilibX utilizzata nell applicazione, 
                    ottenuta tramite la funzione mlx_init.
                  - width e height: sono le dimensioni della finestra in pixel.
                  - title: è il titolo della finestra, che verrà visualizzato nella barra del titolo.

                     Restituisce un puntatore (void *) alla finestra grafica appena creata


> DESCRIZIONE:    mlx_new_window: Questa funzione viene utilizzata per creare una nuova finestra 
                  grafica all interno dell ambiente MinilibX e restituisce un puntatore alla 
                  finestra appena creata.

> UTILIZZO:       #include <mlx.h>

int main() {
    // Inizializzazione dell ambiente MinilibX
    void *mlx_ptr = mlx_init();

    // Creazione di una nuova finestra grafica
    int width = 800;
    int height = 600;
    char *title = "My Window";
    void *win_ptr = mlx_new_window(mlx_ptr, width, height, title);

    // Altre inizializzazioni e utilizzo della finestra

    return 0;
}

                   In questo esempio, mlx_new_window viene chiamato per creare una nuova finestra 
                   grafica all interno dell ambiente MinilibX, utilizzando le dimensioni specificate 
                   (width e height) e il titolo specificato (title). Viene restituito un puntatore 
                   (win_ptr) alla finestra grafica appena creata, che può essere successivamente 
                   utilizzato per interagire con la finestra, ad esempio disegnando su di essa o 
                   impostando gestori per gli eventi.

                   In breve, mlx_new_window è utilizzata per creare una nuova finestra grafica 
                   all interno dell ambiente MinilibX e restituisce un puntatore alla finestra appena 
                   creata, che può quindi essere utilizzato per accedere e gestire la finestra  



                                      *************************************


MLX_DESTROY_WINDOWS:
___________________________________________________________________________________________________________________
> PROTOTIPO:      int mlx_destroy_window(void *mlx_ptr, void *win_ptr);

                  Con:
                  - mlx_ptr: è un puntatore all istanza di MinilibX utilizzata nell applicazione, 
                             ottenuta tramite la funzione mlx_init.

                  - win_ptr: è un puntatore alla finestra grafica che si desidera distruggere.

                  Restituisce un valore intero che indica lo stato dell operazione. Di solito, 
                  il valore restituito è 0 se la finestra è stata distrutta con successo, 
                  e -1 se si è verificato un errore.         


> DESCRIZIONE:    Questa funzione viene utilizzata per distruggere una finestra grafica 
                  all interno dell ambiente MinilibX.

> UTILIZZO:       
int main() {
    // Inizializzazione dell ambiente MinilibX
    void *mlx_ptr = mlx_init();

    // Creazione di una nuova finestra grafica
    void *win_ptr = mlx_new_window(mlx_ptr, 800, 600, "My Window");

    // Operazioni sulla finestra...

    // Distruzione della finestra grafica
    mlx_destroy_window(mlx_ptr, win_ptr);

    // Altre operazioni e terminazione

    return 0;
}

                    In questo esempio, mlx_destroy_window viene chiamata per distruggere la 
                    finestra grafica specificata (win_ptr) all interno dell ambiente MinilibX. 
                    Dopo questa chiamata, la finestra non sarà più disponibile e verrà rimossa 
                    dallo schermo.

                    È importante notare che la distruzione di una finestra con mlx_destroy_window 
                    non influisce sull istanza di MinilibX stessa (mlx_ptr). Se necessario, 
                    è possibile creare e distruggere più finestre all interno dello stesso 
                    ambiente MinilibX.

                    In breve, mlx_destroy_window è utilizzata per distruggere una finestra 
                    grafica all interno dell ambiente MinilibX, liberando le risorse associate 
                    ad essa e rimuovendola dallo schermo.
---------------------------------------------------------------------------------------------------------




---------------------------------------------------LOOP------------------------------------------------
MLX_LOOP:
__________________________________________________________________________________________________________
> PROTOTIPO:      void mlx_loop(void *mlx_ptr);

                  Con:
                  - mlx_ptr: è un puntatore all istanza di MinilibX utilizzata nell applicazione, 
                            ottenuta tramite la funzione mlx_init.
                  - non restituisce alcun valore          


> DESCRIZIONE:    è utilizzata per avviare il ciclo principale degli eventi, il quale gestisce 
                  gli input dell utente e le operazioni di rendering all interno delle finestre 
                  grafiche create con MinilibX. Ecco una spiegazione dettagliata di come funziona

                  mlx_loop: Questa funzione avvia il ciclo principale degli eventi all interno 
                  dell ambiente MinilibX. Una volta chiamata, il programma entra in uno stato 
                  di attesa e inizia a ricevere e gestire gli eventi del sistema, come gli eventi 
                  della tastiera, del mouse e gli eventi di esposizione della finestra.

> UTILIZZO:       
#include <mlx.h>

int main() {
    // Inizializzazione dell ambiente MinilibX
    void *mlx_ptr = mlx_init();

    // Altre inizializzazioni

    // Avvio del ciclo principale degli eventi
    mlx_loop(mlx_ptr);

    return 0;
}

                  In questo esempio, mlx_loop viene chiamato per avviare il ciclo principale 
                  degli eventi all interno dell ambiente MinilibX. Dopo questa chiamata, 
                  il programma entra in uno stato di attesa e inizia a gestire gli eventi del sistema.

                  Durante il ciclo di esecuzione di mlx_loop, è possibile che l utente interagisca 
                  con le finestre grafiche create, ad esempio premendo tasti sulla tastiera, 
                  cliccando con il mouse o ridimensionando le finestre. 
                  Ogni volta che si verifica un evento, MinilibX chiama i gestori degli eventi 
                  appropriati per gestire l evento e aggiornare di conseguenza la visualizzazione 
                  all interno delle finestre.

                  In breve, mlx_loop è utilizzata per avviare il ciclo principale degli eventi 
                  all interno dell ambiente MinilibX, il quale gestisce gli input dell utente e 
                  le operazioni di rendering all interno delle finestre grafiche create con MinilibX.
----------------------------------------------------------------------------------------------------------







---------------------------------------------------HOOK--------------------------------------------------
MLX_LOOP_HOOK:
______________________________________________________________________________________________________________
> PROTOTIPO:      int mlx_loop_hook(void *mlx_ptr, int (*funct_ptr)(), void *param);
                  
                  Con: 
                  - mlx_ptr: è un puntatore all istanza della libreria MinilibX utilizzata nell applicazione.
                  - funct_ptr: è un puntatore a una funzione definita dall utente che verrà eseguita ad ogni iterazione del ciclo degli eventi.
                  - param: è un parametro opzionale che può essere passato alla funzione definita dall utente.

> DESCRIZIONE:    mlx_loop_hook: Questa funzione viene utilizzata per impostare una funzione di callback che 
                  verrà eseguita ad ogni iterazione del ciclo principale degli eventi (mlx_loop). 
                  È utile quando si desidera eseguire del codice specifico ad ogni iterazione del ciclo 
                  degli eventi, ad esempio per aggiornare l interfaccia grafica, controllare lo stato di 
                  alcuni elementi, o eseguire altre operazioni periodiche.
                  (Es: aggiornare lo stato del gioco, gestendo il conteggio dei loop, la raccolta di monete e il disegno 
                       della mappa.)
                  (Posso vedere mlx_loop_hook e mlx_key_hook come complementari:
                   Quando c e  un comando esegue mlx_key.. quando non c e  un comando esegue questo)

> UTILIZZO:       #include <mlx.h>

                  int update_graphics(void *param) {
                  // Codice per aggiornare l interfaccia grafica
                  return 0;
                  }

                  int main() {
                  void *mlx_ptr = mlx_init();  // Altre inizializzazioni

                  mlx_loop_hook(mlx_ptr, &update_graphics, NULL); // Impostazione della funzione di aggiornamento dell interfaccia grafica

                  mlx_loop(mlx_ptr); // Avvio del ciclo principale degli eventi
                  return 0;
                  }

                  In questo esempio, la funzione update_graphics viene chiamata ad ogni iterazione del ciclo principale degli eventi 
                  (mlx_loop). Questa funzione può essere utilizzata per aggiornare l interfaccia grafica in base alle 
                  esigenze dell applicazione.



                                      *************************************


_______________________________________________________________________________________________________________
MLX_KEY_HOOK:
_______________________________________________________________________________________________________________
> PROTOTIPO:      int mlx_key_hook(void *mlx_ptr, int (*funct_ptr)(), void *param);
                  
                  Con: 
                  - mlx_ptr: è un puntatore all istanza della libreria MinilibX utilizzata nell applicazione.
                  - funct_ptr: è un puntatore a una funzione definita dall utente che verrà chiamata ogni 
                               volta che viene premuto un tasto sulla tastiera.
                  - param: è un parametro opzionale che può essere passato alla funzione definita dall utente.

> DESCRIZIONE:    La funzione mlx_key_hook è una funzione della libreria grafica MinilibX, utilizzata per gestire 
                  gli eventi della tastiera in un applicazione grafica.

                  Quando viene chiamata mlx_key_hook, essa imposta la funzione definita dall utente come 
                  gestore degli eventi della tastiera per la finestra grafica corrente. Ciò significa che 
                  ogni volta che viene premuto un tasto sulla tastiera mentre la finestra grafica è attiva, l
                  a funzione definita dall utente verrà chiamata e riceverà come parametro il codice del tasto premuto

> UTILIZZO:      int my_key_press(int keycode, void *param) {
                 // Gestione degli eventi della tastiera
                 }

                  int main() {
                  
                  void *mlx_ptr = mlx_init(); // Inizializzazione di MinilibX

                  void *win_ptr = mlx_new_window(mlx_ptr, ...); // Creazione della finestra grafica

                  mlx_key_hook(win_ptr, &my_key_press, NULL); // Impostazione del gestore degli eventi della tastiera

                  mlx_loop(mlx_ptr);   // Avvio del ciclo principale degli eventi
                  return 0;
                  }

                  In questo esempio, my_key_press è la funzione definita dall utente che gestisce gli eventi della tastiera. 
                  Viene passata come argomento a mlx_key_hook insieme al puntatore alla finestra grafica (win_ptr). 
                  Ogni volta che viene premuto un tasto sulla tastiera mentre la finestra grafica è attiva, 
                  my_key_press verrà chiamata e riceverà come parametro il codice del tasto premuto.
                  
                  In sintesi, mlx_key_hook è utilizzata per impostare il gestore degli eventi della tastiera in un applicazione 
                  grafica utilizzando MinilibX, consentendo all utente di definire e gestire il comportamento dell applicazione i
                  n risposta ai tasti premuti sulla tastiera.



                                      *************************************


_________________________________________________________________________________________________________
MLX_HOOK:
__________________________________________________________________________________________________________
> PROTOTIPO:      int mlx_hook(void *win_ptr, int event, int event_mask, int (*funct_ptr)(), void *param);

                  Con:
                  - win_ptr: è un puntatore alla finestra grafica alla quale si desidera associare il gestore degli eventi.
                  - event: è il tipo di evento a cui si desidera associare il gestore.
                  - event_mask: è un mascheramento che specifica i tipi di eventi che si desidera monitorare. 
                                È possibile combinare più tipi di eventi utilizzando operatori bitwise (ad esempio, OR logico |).
                  - funct_ptr: è un puntatore a una funzione definita dall utente che verrà chiamata quando si verifica l evento specificato.
                  - param: è un parametro opzionale che può essere passato alla funzione definita dall utente.

> DESCRIZIONE:    La funzione mlx_hook è una funzione della libreria grafica MinilibX, utilizzata per associare il gestore degli e
                  venti a una finestra grafica specifica. Questo può essere utilizzato per gestire una varietà di eventi, 
                  inclusi gli eventi della tastiera, del mouse e altri eventi di input o di sistem

                  Quando viene chiamata mlx_hook, essa associa la funzione definita dall utente come gestore per l evento specificato 
                  (event) per la finestra grafica specificata (win_ptr). Il gestore verrà chiamato ogni volta che si verifica l evento 
                  specificato, se il mascheramento di eventi (event_mask) corrisponde all evento effettivamente verificatosi.


> UTILIZZO:       int my_key_press(int keycode, void *param) {
                  // Gestione degli eventi della tastiera
                  }

                  int main() {
                  void *mlx_ptr = mlx_init();  // Inizializzazione di MinilibX

                  void *win_ptr = mlx_new_window(mlx_ptr, ...);  // Creazione della finestra grafica

                  // Impostazione del gestore degli eventi della tastiera
                  mlx_hook(win_ptr, KeyPress, KeyPressMask, &my_key_press, NULL); 
                  
                  mlx_loop(mlx_ptr);  // Avvio del ciclo principale degli eventi
                  return 0;
                   }
                  
                  In questo esempio, my_key_press è la funzione definita dall utente 
                  che gestisce gli eventi della tastiera. Viene passata come argomento 
                  a mlx_hook insieme al tipo di evento (KeyPress), al mascheramento di eventi 
                  (KeyPressMask) e al puntatore alla finestra grafica (win_ptr). 
                  Ogni volta che viene premuto un tasto sulla tastiera mentre la 
                  finestra grafica è attiva, my_key_press verrà chiamata e riceverà come parametro 
                  il codice del tasto premuto.
                  
                  In sintesi, mlx_hook è utilizzata per associare il gestore degli eventi 
                  a una finestra grafica in un applicazione utilizzando MinilibX, 
                  consentendo all utente di definire e gestire il comportamento 
                  dell applicazione in risposta a una varietà di eventi, 
                  tra cui eventi della tastiera, 
                  del mouse e altri eventi di input o di sistema.  



> DIFFERENZA MLX_KEY_HOO e MLX_HOOK: 
  In sostanza, mlx_key_hook è specificamente per la gestione degli eventi della tastiera, 
  mentre mlx_hook è più generale e può essere utilizzato per gestire una vasta gamma di 
  eventi diversi. Se si desidera solo gestire gli eventi della tastiera, 
  è preferibile utilizzare mlx_key_hook, mentre se si desidera gestire altri 
  tipi di eventi oltre a quelli della tastiera, 
  è necessario utilizzare mlx_hook specificando il tipo di evento desiderato.

------------------------------------------------------------------------------------------------------







-----------------------------------------------------IMAGE------------------------------------------------
_________________________________________________________________________________________________________
MLX_XPM_FILE_TO_IMMAGE:
_________________________________________________________________________________________________________
> PROTOTIPO:      void *mlx_xpm_file_to_image(void *mlx_ptr, char *filename, int *width, int *height);

                  Con:
                  - mlx_ptr: Puntatore a una struttura di contesto grafico MiniLibX, 
                             ottenuto tipicamente con mlx_init().
                  - filename: Stringa rappresentante il percorso del file XPM da caricare.
                  - width: Puntatore a un intero in cui la funzione memorizzerà la larghezza 
                           dell immagine caricata.
                  - height: Puntatore a un intero in cui la funzione memorizzerà l altezza 
                            dell immagine caricata.         


> DESCRIZIONE:    La funzione mlx_xpm_file_to_image viene utilizzata per caricare un immagine 
                  XPM (X PixMap) da un file e creare un immagine utilizzabile all interno di 
                  un applicazione grafica

                  La funzione restituisce un puntatore all immagine appena creata.

> UTILIZZO:       
int main() {
    void *mlx_ptr;
    void *mlx_win;
    void *image_ptr;
    int width, height;

    // Inizializza il contesto grafico MiniLibX
    mlx_ptr = mlx_init();
    if (mlx_ptr == NULL) {
        printf("Errore durante l inizializzazione di MiniLibX\n");
        return 1;
    }

    // Crea una finestra grafica
    mlx_win = mlx_new_window(mlx_ptr, 800, 600, "Esempio MiniLibX");

    // Carica un immagine XPM da un file
    image_ptr = mlx_xpm_file_to_image(mlx_ptr, "immagine.xpm", &width, &height);
    if (image_ptr == NULL) {
        printf("Errore durante il caricamento dell immagine\n");
        return 1;
    }

    // Disegna l immagine nella finestra
    mlx_put_image_to_window(mlx_ptr, mlx_win, image_ptr, 0, 0);

    // Attendi che l utente prema un tasto prima di chiudere la finestra
    mlx_loop(mlx_ptr);

    return 0;
}


                                            **************************


_________________________________________________________________________________________________________
MLX_PUT_IMAGE_TO_WINDOW:
_________________________________________________________________________________________________________
> PROTOTIPO:      int mlx_put_image_to_window(void *mlx_ptr, void *win_ptr, void *img_ptr, int x, int y);

                  Con:
                  - mlx_ptr: Puntatore a una struttura di contesto grafico MiniLibX, 
                             ottenuto tipicamente con mlx_init().
                  - win_ptr: Puntatore alla finestra grafica in cui disegnare l immagine.
                  - img_ptr: Puntatore all immagine da disegnare nella finestra.
                  - x: Coordinata x all interno della finestra in cui posizionare 
                       l angolo in alto a sinistra dell immagine 
                       (dato dalla funzione precedente).
                  - y: Coordinata y all interno della finestra in cui posizionare 
                       l angolo in alto a sinistra dell immagine.        


> DESCRIZIONE:    La funzione mlx_put_image_to_window viene utilizzata per disegnare un immagine 
                  all interno di una finestra MiniLibX. Prende come argomenti il puntatore al 
                  contesto grafico MiniLibX (mlx_ptr), il puntatore alla finestra in cui disegnare 
                  l immagine (win_ptr), il puntatore all immagine da disegnare (img_ptr), 
                  e le coordinate (x, y) all interno della finestra in cui posizionare 
                  l angolo in alto a sinistra dell immagine.

                  In sostanza, quando chiami questa funzione, MiniLibX disegnerà l immagine specificata 
                  all interno della finestra specificata, posizionandola secondo le coordinate (x, y) 
                  fornite

> UTILIZZO:       (vedi esempio precedente)      


                                            **************************

________________________________________________________________________________________________________
MLX_STRING_PUT:
________________________________________________________________________________________________________
> PROTOTIPO:      int mlx_string_put(void *mlx_ptr, void *win_ptr, int x, int y, int color, char *string);

                  Con:
                  - mlx_ptr: Puntatore a una struttura di contesto grafico MiniLibX, 
                             ottenuto tipicamente con mlx_init().
                  - win_ptr: Puntatore alla finestra grafica in cui disegnare l immagine.
                  - x: Coordinata x all interno della finestra in cui posizionare l angolo in alto a 
                       sinistra del testo.
                  - y: Coordinata y all interno della finestra in cui posizionare l angolo in alto a 
                       sinistra del testo.
                  - color: Colore del testo. Può essere specificato come un valore RGB o come un 
                           indice di colore nella palette di colori MiniLibX.
                  - string: La stringa di testo da disegnare       


> DESCRIZIONE:    La funzione mlx_string_put della libreria MiniLibX viene utilizzata per disegnare una 
                  stringa di testo all interno di una finestra MiniLibX

> UTILIZZO:
int main() {
    void *mlx_ptr;
    void *mlx_win;

    // Inizializza il contesto grafico MiniLibX
    mlx_ptr = mlx_init();
    if (mlx_ptr == NULL) {
        printf("Errore durante l inizializzazione di MiniLibX\n");
        return 1;
    }

    // Crea una finestra grafica
    mlx_win = mlx_new_window(mlx_ptr, 800, 600, "Esempio MiniLibX");

    // Disegna una stringa di testo nella finestra
    mlx_string_put(mlx_ptr, mlx_win, 100, 100, 0xFFFFFF, "Ciao, mondo!");

    // Attendi che l utente prema un tasto prima di chiudere la finestra
    mlx_loop(mlx_ptr);

    return 0;
}

                    In questo esempio, mlx_string_put viene utilizzata per disegnare la stringa 
                    "Ciao, mondo!" nella finestra MiniLibX alle coordinate (100, 100) con il 
                    colore bianco (0xFFFFFF). La funzione mlx_loop viene utilizzata per mantenere 
                    la finestra aperta fino a quando l utente non chiude la finestra manualmente.


                                            **************************

________________________________________________________________________________________________________
MLX_DESTROY_IMAGE:
________________________________________________________________________________________________________
> PROTOTIPO:      int mlx_destroy_image(void *mlx_ptr, void *img_ptr);

                  Con:
                  - mlx_ptr: Puntatore a una struttura di contesto grafico MiniLibX, 
                             ottenuto tipicamente con mlx_init().
                  - img_ptr: Puntatore all immagine che si desidera distruggere.
    

> DESCRIZIONE:    Quando hai finito di utilizzare un immagine all interno della tua applicazione MiniLibX, 
                  è buona pratica deallocare la memoria occupata da quella specifica immagine chiamando 
                  mlx_destroy_image. Questo aiuta a prevenire perdite di memoria e a mantenere efficiente 
                  l utilizzo della memoria nel tuo programma. 
                  La funzione mlx_destroy_image, infatti, viene utilizzata per liberare la memoria occupata 
                  da un immagine precedentemente creata con la funzione mlx_xpm_file_to_image

> UTILIZZO:
int main() {
    void *mlx_ptr;
    void *mlx_win;
    void *image_ptr;
    int width, height;

    // Inizializza il contesto grafico MiniLibX
    mlx_ptr = mlx_init();
    if (mlx_ptr == NULL) {
        printf("Errore durante l'inizializzazione di MiniLibX\n");
        return 1;
    }

    // Crea una finestra grafica
    mlx_win = mlx_new_window(mlx_ptr, 800, 600, "Esempio MiniLibX");

    // Carica un'immagine XPM da un file
    image_ptr = mlx_xpm_file_to_image(mlx_ptr, "immagine.xpm", &width, &height);
    if (image_ptr == NULL) {
        printf("Errore durante il caricamento dell'immagine\n");
        return 1;
    }

    // Utilizza l'immagine...

    // Distrugge l'immagine quando non è più necessaria
    mlx_destroy_image(mlx_ptr, image_ptr);

    // Attendi che l'utente prema un tasto prima di chiudere la finestra
    mlx_loop(mlx_ptr);

    return 0;
}















******************************************************************************************************
_______________________________________________________________________________________________________
                                          FUNCIONT MAP
_______________________________________________________________________________________________________

-VALIDAZIONE DELLA MAPPA-------------------------------------------------------------------------------

MATRIX_GENERATOR
|
|--> CHECK_MAPSIZE --> CHECK_BER_SIZE
|
|--> (return)
       |
       |--> P_E_C_COUNT (map_checks)
       |    - verifica il numero di P,E,
       |    - Conta c
       |    
       |
       |--> CHECK_MAP_AND_SET_TYLE   -->   SET_CHAR        -----------> SET_TILE_LOCATION 
       |    - controlla la validità       (maps_utils.c)                (tile.c)
       |                                  - Controlla se i caratteri    - salva la posizione di P,E e C
       |                                    presente sulla mappa 
       |                                    sono validi
       |
       |--> CHECK_PATH (path_check.c): - Controlla se il percorso e  valido 
                 |                     
                 |
                 |--> MATRIX_DUPLICATOR 
                 |
                 |--> TRACE_ALL_PATH -setta tutte le posizioni delle caselle in cui
                 |                    riesce ad arrivare a  1 
                 |                   
                 |
                 |--> check_coin - controlla se le monete sono state raggiunte

-------------------------------------------------------------------------------------------------------