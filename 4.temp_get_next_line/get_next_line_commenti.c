#include "get_next_line.h"

/*__________________________DESCRIZIONE__________________________
FIND LINE:
Legge i dati dal file descriptor (fd) in un buffer fino a quando 
viene trovato un carattere di nuova riga.
Utilizza una variabile statica stc_backup per tenere traccia 
dei dati rimanenti dalla lettura precedente.
Restituisce una stringa allocata dinamicamente contenente 
la riga (compreso il carattere di nuova riga).

EXTRACT_LINE:
Estrae una riga dalla stringa di input (stc_backup) fino a quando 
viene trovato un carattere di nuova riga o alla fine della stringa.
Restituisce una stringa allocata dinamicamente contenente la riga estratta.

UPDATE STC LINE:
Aggiorna la stringa stc_backup, rimuovendo la prima riga 
(compreso il carattere di nuova riga) dalla stringa corrente.
Restituisce la stringa aggiornata.

GET NEXT LINE:
Funzione principale per ottenere la prossima riga da un file descriptor.
Chiama le funzioni find_line, extract_line e update_stc_string 
per ottenere e manipolare la prossima riga.
Restituisce la riga estratta
______________________________________________________________________*/

/*---------------------------NOTE---------------------------------
 - Il prefisso "STC" indica le variabili statiche
 
 * BUFFER     = stringa usata nel read (va in find_line) 
                ha dimensione BUFFER_SIZE, 
 * STC_BACKUP = stringa statica (va in get_next_line,
 * LINE       = stringa non statica che contiene la linea letta 
                e verrà restituita da get_next line
                (va in get next e sarà il suo return) 

 - Non mi serve allocare spazio per nessuna stringa ad eccezione 
   di "buffer". Questo perchè userò funzioni che già usano 
   malloc internamente  
 - SSIZE_T: È una versione estesa di size_t e può rappresentare 
            valori negativi, zero o valori positivi.
            La scelta di ssize_t è particolarmente appropriata quando 
            si lavora con funzioni come read, poiché può essere 
            utilizzato per rappresentare la quantità di dati 
            effettivamente letta o scritta. Il valore restituito 
            da read è di tipo ssize_t
  - DEALLOCARE: quando passo una stringa ad una funzione, posso deallocarla
               dalla funzione stessa. In questo modo si deallocherà anche 
               la stringa originale                 
------------------------------------------------------------------*/


/*______________________FUN: find_line()_______________________*/
  /*---------------------------------------------------------------
  - parametri = la stringa statica, il file descriptor
  - return    = la stringa statica con i nuovi caratteri letti
                contenenti "\n"
  
  - (alloco il buffer con malloc di BUFFER_SIZE)
  - in un ciclo chiamo la funzione read
  - leggo "byter_read" caratteri ad ogni iterazione dal "buffer"
    (che potranno essere di numero BUFFER_SIZE o minore se, nell'ultima
     lettura la stringa è quasi finita) attraverso la condizione del while.
  - all'interno del ciclo li copio nella stringa statica con ft_strjoin
  
  - Se trova "\n" esce dal ciclo e restituisce stc_backup
    con i caratteri letti inseriti al suo interno.
    Questa stringa conterrà quindi i caratteri estratti dal
    file contenenti il terminatore.
  - libero buffer    
    --------------------------------------------------------------*/
static char  *find_line(int fd, char  *stc_backup)
{
  char  *buffer;       // -> buffer del read()
  ssize_t bytes_read;  // -> return del read (numero di char letti)

  
  bytes_read = 1; /*Userò questo valore come condizione del ciclo:
                  - se vale -1 = errore di lettura
                  - se vale 0  = il file è finito o non esiste
                   o è in modalità sola lettura
                   Mi serve quindi inizializzarlo ad 1 altrimenti il ciclo 
                   while non partirebbe */
  
  /*ALLOCO MEMORIA PER IL BUFFER DI READ()*/ 
  buffer = (char *)malloc((BUFFER_SIZE * sizeof(char)) + 1);
  if (!buffer)
    return(NULL);

  /* CICLO WHILE:
  questo ciclo andrà avanti finchè byte_read è > 0. Al suo interno:
    - farà 1 read
    - copierà i caratteri
    - se ci sono stati caratteri da copiare il mio bytes_read sarà 
      ancora > 0 ed eseguirà di nuovo il ciclo
    - terminerà quando il file è finito
  e fino a quando non trova il carattere "\n" nella stringa statica
  
  Oss: La stringa statica è inizializzata in get next line 
       attraverso questa funzione.
       Entrerò quindi almeno una volta nel ciclo, copierò i caratteri
       e controllerò cosa ho copiato in stc_backup. 
       Se ho copiato un "\n" non riesegue il ciclo e restituisce la stringa

  Oss: al primo giro del while stc_backup sarà vuota. Ho dovuto quindi modificare
       ft_strchr affinchè se la stringa non esiste mi restituisca 0
    */
  while (bytes_read > 0 && (!ft_strchr(stc_backup, '\n')))
  {
    bytes_read = read(fd, buffer, BUFFER_SIZE);

    if (bytes_read == -1)      
    {
      free (buffer);
      return (NULL);
    }                     /*Se il return di read() è "-1" significa che 
                            c'è stato un errore. 
                            libero quindi "buffer"*/
    
    else if (bytes_read == 0) 
      break;             /*Se non ho letto caratteri, e quindi è finito
                           il file allora esco dal ciclo.
                           Supponiamo di essere entrati nel ciclo. read() prova
                           a leggere BUFFER_SIZE caratteri (es 5) ma ne trova 
                           solo 3. la funzione restituirà 3 ed eseguirò un'altra volta 
                           il ciclo (perchè 3 > 0).
                           Il file era però finito quindi, chiamando di nuovo read,
                           avrò come risultato zero. 
                           Metto quindi questo controllo così da non dover far copiare
                           una stringa vuota.
                          Quindi: GET_NEXT_LINE ESEGUE IL FREE QUANDO HA FINITO DI LEGGERE IL FILE|     GRAZIE A QUESTA LINEA*/

    buffer[bytes_read] = '\0'; /*In caso la lettura sia avvenuta termino 
                                 buffer con \0*/

    /*CONCATENO I NUOVI CARATTERI LETTI DENTRO STC_BECKUP*/
    stc_backup = ft_strjoin(stc_backup, buffer); /* stc_back. ora punta alla stringa
                                                    copiata. 
                                                    Questo indirizzo verrà restituito
                                                    in get_next_line alla vera 
                                                    stringa statica.
                                                    Oss: strjoin terminerà con \0 
                                                    la stringa congiunta*/
  }                             

  free(buffer);    /*Prima di uscire libero ogni volta il buffer
                    NOTA: stc_backup (quella vecchia) viene liverata
                          in strjoin. 
                          Non potevo liberarla qui altrimenti non avrei 
                          restituito niente*/
  return (stc_backup);                     
  } 

/*________________________________________________________________*/




/*_______________________FUN: extract_line_________________________*/
  /*--------------------------------------------------------------
    OSS: Devo controllare che ci sia "\n" perchè non è detto che sia
         mai stato inserito nel file.
        (Supponiamo che il file sia composto da "abc". La "find_line" 
         ha restituito questa stringa ma essa non contiene "\n")
    
    - parametro: "stc_backup"
    - la funzione prende "stc_backup" e la legge finchè non trova \n o \0 
      il che implica che o la linea è finita o che il file è finito
    - Se trova \n: estrae da "stc_backup" una substringa che va 
                   dal'inizio a \n e la termina con '\0' e restituisce line
    - Se non trova \n ma trova \0: significa che o non c'era un \n o 
                                   sono all'ultima riga del file 
                                   (o che il file era vuoto).
                                   Estrae la stringa e la restituisce 
  ----------------------------------------------------------------*/
static char  *extract_line(char *stc_backup)
{
  char  *line;      /*stringa che restituirò*/                    
  int   i;                                     
  
    /*Se la linea e' vuoota*/
  if (!stc_backup[0])
    return (NULL);
  
  i = 0;
  /*CONTROLLO QUANTI CARATTERI CI SONO IN STC_BAC. 
    PRIMA DI INCONTRARE \n o \0*/
  while (stc_backup[i] != '\n' && stc_backup[i] != '\0')
    i++;

  /*ALLOCA LINE DI i-CARATTERI + 2
    - 1 per un eventuale \n
    - L'altro per il terminatore*/
  line = (char *)malloc(sizeof(char) * i + 2);
  if (!line)
    return (NULL); 
  
  i = 0;
  /*COPIO STC_BAC. LINE. FINCHE' NON TROVO \n o \0*/
  while (stc_backup[i] != '\n' && stc_backup[i] != '\0')
  {
    line[i] = stc_backup[i];
    i++;
  }

  /*se il carattere in cui mi sono fermato è \n, aggiungo \n
    alla stringa temp_line*/
  if (stc_backup[i] == '\n')
  {
    line[i] = '\n';
    i++;
  }

  /*se non lo è termino la stringa con \0 e la restituisco */
  line[i] = '\0';  
  return (line);
}

/*________________________________________________________________*/




/*________________________FUN: update_stc:string__________________*/
  /*--------------------------------------------------------------
   funzione che aggiorna la stringa statica: 
  estrae da "stc_backup" una substringa che va 
  da \n alla fine di line (\0).

  Se non trova \n restituisce NULL
  ----------------------------------------------------------------*/
char  *update_stc_string(char *stc_backup)
{
  int   i;
  int   j;
  char  *tmp;

  i = 0;

  /*SCORRO LA STRINGA FINO A TROVARE \n O LA FINE DELLA STRINFA*/
  while (stc_backup[i] != '\n' && stc_backup[i])
    i++;

  /*SE NON HO INCONTRATO \n:
    - Significa che o il file è vuoto
    - o sono all'ultima riga.
    In entrambi i casi non dovrò riaggiornare stc_backup quindi 
    posso restituire NULL; ??*/  
  if (stc_backup[i] == '\0')
  {
    free(stc_backup); /* --> la tua funzione update_line effettua la deallocazione 
                             della memoria della stringa originale line anche se non r
                             iceve un doppio puntatore come argomento. In C, i parametri 
                             vengono passati per valore, ma poiché stai modificando il 
                             contenuto a cui punta line (per esempio, stai deallocando 
                             la memoria e successivamente restituendo un nuovo puntatore), 
                             queste modifiche saranno riflesse all'esterno della funzione.
                             
                             Quando passi un puntatore a una funzione in C, in realtà stai 
                             passando una copia del puntatore, ma questa copia fa 
                             riferimento allo stesso blocco di memoria dell'originale. 
                             Pertanto, qualsiasi modifica apportata al blocco di memoria a 
                             cui punta il puntatore all'interno della funzione influirà 
                             sulla versione originale del puntatore all'esterno della 
                             funzione.
                             
                             Nel tuo caso, quando esegui free(line), stai deallocando 
                             la memoria della stringa originale puntata da line*/
    return (NULL);
  }
  tmp = (char *)malloc(sizeof(char) * ft_strlen(stc_backup) - i) + 1;
  if(!tmp)
    return (NULL);

  /*Se ho trovato \n salto il carattere new line
  e alloco memoria per la stringa temporanea*/
  i++;  

  /*COPIO I CARATTERI RIMASTI ALL'INTERNO DI TMP e lo termino con \0*/ 
  j = 0;
  while (stc_backup[i])
    tmp[j++] = stc_backup[i++];
  tmp[j] = '\0';
  free(stc_backup);
  return (tmp);
}                                            
/*________________________________________________________________*/




/*______________________GET_NEXT_LINE_____________________________*/
  /*---------------------------------------------------------------
  - return: "line"
                       
  - esegue controlli sul'fd e sulle allocazioni 
    (fd < 0, BUFFER_SIZE < 0, la chiamata a read ha restituito un
      valore non negativo, se la chiamata a read restituisce 0 ho
      raggiunto la fine del file))
  - chiamo find_line() 
  - ne metto il return in "stc_backup"
  - Ora stc_backup è riempita di caratteri COMPRESO "\n" (in caso ci sia). 
    Devo quindi estrarre la linea fino al "\n" attraverso la funzione "extract_line" 
    per poi assegnare il suo return (la stringa fino al new line) a "line"
  - chiamo "extract_string" assegnandola a "line"




  - assegno a "stc_left_char" il return di "set_line". 
    Avrà così nella mia funzione statica, i caratteri rimasti che 
    vanno da dopo \n agli ultimi letti per poterla riutilizzare 
    nella prossima chiamata
  ----------------------------------------------------------------*/
char    *get_next_line(int fd)
{
    char        *line;   // -> stringa che conterrà la linea letta
    static char *stc_backup; 

    /*CONTROLLI PRELIMINARI*/
    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);

    /*COPIO NELLA STRINGA STATICA I CARATTERI LETTI FINO A \n o \0*/    
    stc_backup = find_line(fd, stc_backup);
    if (!stc_backup)
      return (NULL); /*Se, dopo aver eseguito la funzione, ho come
                             risultato una stringa vuota significa che il 
                             file era vuoto. In questo caso restituisco 
                             NULL*/

    /*ESTRAGGO I CARATTERI FINO AL "\N" DA STC_BACKUP
      NOTA: Non fare controlli di deallocazione, perchè i casi di errore
            delle vaie funzioni sono stati gestiti nelle funzioni stesse
            deallocando ciò che era stato allocato.
            Se quindi qui arriva un NULL nulla è stato allocato*/
    line = extract_line(stc_backup);
    
    /*AGGIORNO LA STRINGA STATICA: rimuovo i caratteri da stc_backup da \n fino a 
                                   \0 cosi da avere quelle in avanzo*/
    stc_backup = update_stc_string(stc_backup);

    /*RESTITUISCO LA NEXT LINE*/
    return (line);

}
/*________________________________________________________________*/

/*

int main(int argc, char **argv)
{
    int        fd;
    char    *line;

    (void)argc;
    fd = open(argv[1], O_RDONLY);
    line = get_next_line(fd);
    printf("%s", line);
}
*/

