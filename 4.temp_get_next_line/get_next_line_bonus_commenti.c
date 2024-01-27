#include "get_next_line_bonus.h"

/*---------------------------NOTE---------------------------------
  - La costante OPEN_MAX è definita nell'header limits.h in C. 
    Essa rappresenta il numero massimo di file che un processo può 
    avere aperti simultaneamente              
------------------------------------------------------------------*/


/*______________________FUN: find_line()_______________________*/
  /*---------------------------------------------------------------

    --------------------------------------------------------------*/
static char  *find_line(int fd, char  *stc_backup)
{
  char  *buffer;       // -> buffer del read()
  ssize_t bytes_read;  // -> return del read (numero di char letti)

  
  bytes_read = 1; 
  
  /*ALLOCO MEMORIA PER IL BUFFER DI READ()*/ 
  buffer = (char *)malloc((BUFFER_SIZE * sizeof(char)) + 1);
  if (!buffer)
    return(NULL);

  /* CICLO WHILE: CONCATENA I CARATTERI LETTI NELLA STRINGA STATICA*/

  while (bytes_read > 0 && (!ft_strchr(stc_backup, '\n')))
  {
    bytes_read = read(fd, buffer, BUFFER_SIZE);
    
    if (bytes_read == -1)      
    {
      free (buffer);
      return (NULL);
    }
    
    else if (bytes_read == 0) 
      break;             /*Se non ho letto caratteri, e quindi è finito
                           il file allora esco dal ciclo.


    buffer[bytes_read] = '\0'; /*In caso la lettura sia avvenuta termino 
                                 buffer con \0*/

    /*CONCATENO I NUOVI CARATTERI LETTI DENTRO STC_BECKUP*/
    stc_backup = ft_strjoin(stc_backup, buffer);
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

  ----------------------------------------------------------------*/
static char  *extract_line(char *stc_backup)
{
  char  *line;      /*stringa che restituirò*/                    
  int   i;                                     
  
  if (!stc_backup)
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

  /*SE NON HO INCONTRATO \n:restituire NULL*/  
  if (stc_backup[i] == '\0')
  {
    free(stc_backup);
    return (NULL);
  }
  tmp = (char *)malloc(sizeof(char) * ft_strlen(stc_backup) - i) + 1;
  if(!tmp)
    return (NULL);

  /*Se ho trovato \n salto il carattere new line*/
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
   - Per poter gestire piu' files, invece di usare una variabile statica,
     userò un array di stringhe statico
   - userò FD come indice per accedere ai vari files
  ----------------------------------------------------------------*/
char    *get_next_line(int fd)
{
    char        *line;   // -> stringa che conterrà la linea letta
    static char *stc_backup[OPEN_MAX];

    /*CONTROLLI PRELIMINARI*/
    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);

    /*COPIO NELLA POSIZIONE FD DELL'ARRAY DI STR STATICHE LA 
      LINE CONTENENTE \n*/  //<----------------------------------------------------------------  
    stc_backup[fd] = find_line(fd, stc_backup[fd]);
    if (!stc_backup[fd])
      return (NULL);

    /*ESTRAGGO I CARATTERI FINO AL "\N" DA STC_BACKUP*/
    line = extract_line(stc_backup[fd]);
    
    /*AGGIORNO LA STRINGA STATICA*/
    stc_backup[fd] = update_stc_string(stc_backup[fd]);

    return (line);

}
/*________________________________________________________________*/


