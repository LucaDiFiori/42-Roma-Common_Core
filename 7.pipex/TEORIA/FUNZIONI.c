👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻
👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽
___________________________________FUNZIONI_____________________________________
👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽
👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻

👽 "EXECVE() NELLA SHELL________________________________________________________
*******************************************************************************"
- Supponiamo di eseguire il comando ls -la nella shell
- Per eseguire un comando la shell chiama "execve()" che prende in carico il 
  compito ed esegue la linea di comando

__________
👽 COSA FA:
----------

👽 Nella shell, la funzione execve() viene utilizzata per eseguire i comandi 
inseriti dall utente. 
Quando l utente digita un comando nella shell e preme Invio, la shell interpreta
il comando e utilizza execve() per eseguire il programma corrispondente al comando.

Ad esempio, se l utente digita ls nella shell e preme Invio, la shell utilizzerà
execve() per eseguire il comando ls.
Dopo che il programma corrispondente al comando viene eseguito, il controllo 
ritorna alla shell. 
La shell aspetta quindi il prossimo comando inserito dall utente e ripete il 
processo di interpretazione ed esecuzione del comando utilizzando execve().

Più precisamente, la shell interpreta il comando inserito dall utente, 
determina quale programma o script deve essere eseguito e quindi utilizza 
execve() per avviare tale programma all interno del processo della shell corrente. 
Questo processo di esecuzione del programma all interno del processo della shell 
corrente comporta il sovrascrivere il codice della shell con il codice 
del programma appena avviato. 
In questo modo, il programma corrispondente al comando viene eseguito nel contesto 
della shell, consentendo all utente di interagire con il sistema operativo 
tramite il comando eseguito.

In questo modo, execve() è uno dei principali meccanismi attraverso cui la shell
esegue i comandi dell utente e gestisce l interazione tra l utente e il sistema.


👽 "Cosa significa che la shell utilizza execve per eseguire il programma 
  corrispondente al comando?"

  Quando l utente digita un comando nella shell e preme Invio, la shell 
  interpreta il comando e utilizza execve() per eseguire il programma 
  corrispondente al comando.

  In sintesi, quando si dice che la shell utilizza execve() per eseguire il 
  programma corrispondente al comando dell utente, si intende che la shell 
  utilizza questa funzione per caricare ed eseguire il programma all interno 
  del processo corrente della shell, "sostituendo il codice della shell con 
  quello del programma appena avviato."



👽 "COME FA EXECVE A CARICARE ED ESEGUIRE UN PROGRAMMA NELLA SHELL ?"

  1) "Interpretazione del comando:" Quando l utente inserisce un comando nella 
     shell e preme Invio, la shell interpreta il comando per determinare quale 
     programma o script deve essere eseguito. Questo può coinvolgere la 
     ricerca del comando all interno delle directory elencate nella variabile di
     ambiente PATH, o il controllo se il comando include un percorso completo.
     
  2) "Preparazione dei parametri:" Una volta che la shell ha interpretato il 
     comando, prepara gli argomenti e l ambiente per il programma che intende 
     eseguire. Gli argomenti includono il nome del programma stesso e eventuali 
     argomenti aggiuntivi specificati dall utente. 
     L ambiente include le variabili d ambiente e i loro valori.
     
  3) "Chiamata a execve():" Una volta preparati gli argomenti e l ambiente, 
     la shell utilizza la funzione execve() per avviare l esecuzione del 
     programma corrispondente al comando. 
     Il percorso del programma e gli altri parametri necessari vengono passati 
     a execve().
     
  4) "Esecuzione del programma:" execve() carica il programma in memoria, risolve 
     i simboli necessari e avvia l esecuzione del programma. 
     Il controllo del processo viene completamente trasferito al 
     programma appena avviato.
     
  5) "Fine della shell:" Dopo che il programma avviato con execve() termina 
      l esecuzione, il controllo del processo può seguire diverse strade:

      i) Terminazione normale: Se il programma termina normalmente, il controllo 
         può tornare al sistema operativo, che gestisce il completamento del processo. 
         Questo può comportare la chiusura di eventuali risorse allocate dal 
         programma e la restituzione di un codice di uscita.

      ii) Terminazione anomala: Se il programma termina in modo anomalo, 
          il controllo può essere restituito al sistema operativo o al processo 
          padre della shell. In questo caso, il sistema operativo può gestire 
          l errore, e il processo padre della shell può essere informato 
          dell errore o può prendere azioni appropriate.

    In entrambi i casi, il controllo non ritorna alla shell dopo che il programma 
    avviato con execve() ha completato la sua esecuzione. 
    La shell cessa di esistere in quanto il suo codice è stato sostituito con 
    quello del programma appena avviato, e il destino del processo dipende dal 
    modo in cui il programma termina l esecuzione e da come il sistema operativo 
    o il processo padre gestisce il completamento del processo.


In sintesi, la shell utilizza execve() per eseguire i comandi inseriti dall utente, 
avviando l esecuzione del programma corrispondente all interno del processo 
della shell corrente. Una volta avviato il programma, la shell cessa di esistere 
in quanto il suo codice viene sostituito con quello del programma appena avviato.



👽 "ESEMPIO"
   - Supponiamo di trovarci nella shell e stampiamo con il comando echoo $$ il 
     suo PID (identificatore di processo) = 1815085
   - Lanciamo ora il comando "ls" e stampiamo il suo PID. Esso sarà diverso
     = 1825529
   - Lanciamo ora il comando "pwd" e stampiamo il suo PID. Anche questo risulterà
     diverso = 1825847
  
   
    Sì, significa che la shell si biforca (fork) per creare un piccolo processo 
    figlio, che esegue il comando, e poi termina dopo averlo completato. 
    Il controllo è quindi prontamente ripreso dal PPID (Parent PID), 
    che è il PID del programma della shell del terminale, solitamente 
    identificato come 181505 in questo contesto.
  





👽 "EXECVE() IN C_______________________________________________________________
*******************************************************************************"
____________
👽 PROTOTIPO:
------------
int execve(const char *__path, char *const __argv[], char *const __envp[])

"path" specifica il percorso del programma da eseguire.
"argv" è un array di stringhe che rappresentano gli argomenti del programma. 
       L ultimo elemento dell array deve essere un puntatore NULL.
"envp" è un array di stringhe che rappresentano l ambiente del programma. 
       Anche in questo caso, l ultimo elemento dell array deve essere 
       un puntatore NULL.

_________
👽 HEADER:   "unistd.h"
---------

___________
👽 COSA FA:
-----------
  - Sostituisci il processo corrente, eseguendo il percorso PATH con gli argomenti
    ARGV e l ambiente ENVP.
  - ARGV e ENVP sono terminati da puntatori NULL.

La funzione execve() in C viene utilizzata per eseguire un nuovo programma 
all interno di un processo esistente. Questa funzione sovrascrive il programma 
corrente del processo chiamante con il programma specificato. In altre parole, 
execve() carica un nuovo programma nell immagine di memoria del processo 
chiamante e inizia ad eseguirlo.

    --------------------------------------------------------------------
    NOTA: Quando si parla delle "immagini di memoria del processo 
          chiamante" ci si riferisce alla struttura 
          di memoria che contiene il codice eseguibile, i dati, lo stack 
          e altre risorse associate a un processo.

          Ogni processo in un sistema operativo ha la propria immagine 
          di memoria, che rappresenta lo stato del processo mentre è 
          in esecuzione. Questa immagine di memoria include:

          "Codice eseguibile:" Questa parte della memoria contiene le 
          istruzioni eseguibili del programma, ovvero il codice che 
          il processore esegue istruzione per istruzione per 
          eseguire le operazioni desiderate.

          "Dati:" Questa sezione della memoria contiene le variabili 
          globali e statiche, nonché altre strutture dati utilizzate 
          dal programma durante l esecuzione.

          "Stack:" La stack è una struttura dati utilizzata per 
          memorizzare le variabili locali e le informazioni di chiamata 
          delle funzioni. È utilizzato anche per gestire le chiamate 
          di funzioni e le relative attivazioni di frame.

          "Heap:" Il heap è una sezione della memoria utilizzata per la
           gestione dinamica della memoria.
      --------------------------------------------------------------------

Quando si chiama execve(), il programma specificato da path viene caricato nella 
memoria del processo chiamante, sostituendo l immagine di memoria esistente con 
quella del nuovo programma. 
Questo significa che il codice eseguibile, i dati, lo stack e le altre risorse 
associate al processo chiamante vengono sostituiti con quelli del nuovo programma. 

Il controllo del processo chiamante viene quindi completamente trasferito al 
nuovo programma, che inizia ad eseguire le sue istruzioni dalla sua immagine di
memoria appena caricata.

execve() è comunemente utilizzata in combinazione con funzioni di manipolazione 
dei processi come fork(). Ad esempio, un processo genitore può chiamare fork() 
per creare un nuovo processo figlio, e quindi il processo figlio può chiamare 
execve() per eseguire un nuovo programma. Questo è uno dei meccanismi 
principali utilizzati per eseguire programmi separati all interno di un processo.





👽"COME FA EXECVE A CARICARE ED ESEGUIRE UN PROGRAMMA IN C ?"
  La funzione execve() in C viene utilizzata per caricare ed eseguire un 
  programma all interno di un processo. Ecco una spiegazione generale 
  di come funziona:
  
  1) "Interpretazione del percorso del programma:" La shell, o il chiamante che 
     utilizza execve(), fornisce il percorso completo del programma che si 
     desidera eseguire. Questo percorso può includere il nome del file eseguibile 
     e la sua posizione nel sistema di file.

  2) "Caricamento del programma:" La funzione execve() riceve il percorso del 
     programma come primo argomento. Utilizzando questo percorso, execve() 
     carica l immagine del programma dal file eseguibile sul disco nel segmento 
     di memoria del processo chiamante.

  3) "Risoluzione dei simboli:" Una volta che il programma è caricato in memoria, 
     execve() risolve i simboli necessari per l esecuzione del programma. 
     Questo può includere la risoluzione di simboli per funzioni di libreria e 
     variabili globali utilizzate dal programma.

  4) "Preparazione degli argomenti e dell'ambiente:" execve() riceve anche due 
      array di stringhe: 
      i) uno per gli argomenti del programma 
      ii) e uno per l ambiente del programma. 
      Questi vengono utilizzati per passare gli argomenti al programma e per 
      fornire un ambiente di esecuzione appropriato.

  5) "Esecuzione del programma:" Una volta che il programma è stato caricato in 
     memoria e che gli argomenti e l ambiente sono stati preparati, execve() 
     avvia l esecuzione del programma. 
     Il controllo del processo viene completamente trasferito al programma appena 
     avviato, che inizia a eseguire le istruzioni dal suo punto di ingresso 
     (generalmente la funzione main() in C).

  6) "Fine del processo chiamante:" Dopo che il programma avviato con execve() 
     ha completato la sua esecuzione, il controllo non ritorna al processo 
     chiamante originale. Invece, se il programma termina normalmente, 
     il controllo può tornare al sistema operativo, che può gestire il 
     completamento del processo. Se il programma termina in modo anomalo, 
     ad esempio a causa di un errore o di un eccezione, il controllo può essere 
     restituito al processo chiamante con un codice di uscita specificato.

  In questo modo, execve() permette di caricare un programma in memoria e di 
  avviare la sua esecuzione all interno del contesto del processo chiamante, 
  sostituendo il codice esistente con quello del programma appena avviato.



_______
ESEMPIO
-------
Ecco un esempio di utilizzo della funzione execve():
#include <stdio.h>
#include <unistd.h>

int main() {
    char *const args[] = { "/bin/ls", "-l", NULL };
    char *const envp[] = { "PATH=/bin:/usr/bin", NULL };

    execve("/bin/ls", args, envp);

    // Se l'esecuzione arriva qui, significa che qualcosa è andato storto
    perror("execve");
    return 1;
}



Vediamo qui gli argomenti della funzione execve()
const char *pathname: Questo argomento specifica il percorso del file eseguibile 
                      che si desidera eseguire. Deve essere una stringa che 
                      punta al percorso completo del file eseguibile.

char *const argv[]: Questo è un array di stringhe che rappresenta gli argomenti 
                    da passare al nuovo programma. La prima stringa argv[0] 
                    solitamente rappresenta il nome del programma stesso. 
                    L ultimo elemento dell array deve essere un puntatore nullo 
                    per indicare la fine degli argomenti.

char *const envp[]: Questo è un array di stringhe che rappresenta le variabili 
                    di ambiente da passare al nuovo programma. 
                    Ogni stringa in envp[] deve essere nel formato 
                    "nome=valore". 
                    Come argv[], anche envp[] deve terminare con un puntatore 
                    nullo per indicare la fine delle variabili di ambiente.



COME TROVO LA POSIZIONE DEI FILE-COMANDO?
-----------------------------------------
"Variabili di ambiente PATH:" Se il file binario si trova in una directory 
                              elencata nelle variabili di ambiente PATH, 
                              puoi cercarlo automaticamente
                              Puoi ottenere il valore della variabile di 
                              ambiente PATH utilizzando la funzione getenv() 
                              char *path = getenv("PATH");
                              Una volta ottenuto il valore di PATH, dovrai cercare 
                              nel percorso restituito per il file binario desiderato.


Vediamo ad esempio come utilizzare la variabile d'anbiente PATH' per cercare il 
comando "ls" nel sistema:
In questo esempio, il programma cerca il comando "ls" in ciascuna directory 
elencata nella variabile di ambiente PATH. Quando trova il comando "ls", 
lo esegue usando execve(). 
Se il comando non viene trovato in nessuna delle directory di PATH, 
il programma stampa un messaggio di errore.

1) "Ottieni il valore di PATH:" Utilizza la funzione getenv("PATH") per ottenere 
   il valore corrente della variabile di ambiente PATH.

2) "Analizza il valore di PATH:" Otterrai una stringa contenente una serie 
   di directory separate da due punti. Ad esempio: /usr/local/bin:/usr/bin:/bin.

3) "Cerca il comando "ls" in ciascuna directory di PATH:" 
   Itera attraverso ciascuna directory ottenuta da PATH, cercando il file 
   eseguibile "ls".

4) "Esegui "ls" se trovato:" Se trovi il file eseguibile "ls" in una delle 
   directory, puoi usarlo per eseguire il comando "ls" usando execve() o 
   una funzione simile.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main() {
    // Ottieni il valore di PATH
    char *path = getenv("PATH");
    if (path == NULL) {
        printf("Variabile di ambiente PATH non trovata.\n");
        return 1;
    }

    // Analizza il valore di PATH
    char *dir = strtok(path, ":"); /*La funzione strtok è tipo split*/
    while (dir != NULL) {
        // Costruisci il percorso completo per il comando "ls"
        char full_path[256];
        snprintf(full_path, sizeof(full_path), "%s/ls", dir); /*formatta una stringa*/

        // Controlla se il file esiste
        if (access(full_path, X_OK) == 0) {
            printf("Eseguendo il comando 'ls' trovato in: %s\n", full_path);
            
            // Esegui il comando "ls" con execve
            char *const args[] = { "ls", NULL };
            execve(full_path, args, NULL);
            
            // Se execve ritorna, qualcosa è andato storto
            perror("execve");
            return 1;
        }

        // Passa alla prossima directory in PATH
        dir = strtok(NULL, ":");
    }

    printf("Comando 'ls' non trovato in nessuna directory di PATH.\n");
    return 1;
}



USANDO STRJOIN()
----------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Definizione di una funzione strjoin() personalizzata
char *strjoin(const char *s1, const char *s2) {
    size_t len1 = strlen(s1);
    size_t len2 = strlen(s2);
    
    // Alloca memoria per il buffer risultante, inclusi i caratteri di terminazione null
    char *result = (char *)malloc(len1 + len2 + 1);
    if (result == NULL) {
        perror("Errore di allocazione di memoria");
        exit(EXIT_FAILURE);
    }
    
    // Copia la prima stringa nel buffer risultante
    strcpy(result, s1);
    // Concatena la seconda stringa nel buffer risultante
    strcat(result, s2);
    
    return result;
}

int main() {
    char *path = getenv("PATH");
    if (path == NULL) {
        printf("Variabile di ambiente PATH non trovata.\n");
        return 1;
    }

    char *command = "ls"; // Comando da cercare

    char *dir = strtok(path, ":");
    while (dir != NULL) {
        // Costruisci il percorso completo per il comando "ls" utilizzando strjoin()
        char *full_path = strjoin(dir, "/");
        full_path = strjoin(full_path, command);

        // Controlla se il file esiste
        if (access(full_path, X_OK) == 0) {
            printf("Eseguendo il comando 'ls' trovato in: %s\n", full_path);
            
            // Esegui il comando "ls" con execve
            char *const args[] = { "ls", NULL };
            execve(full_path, args, NULL);
            
            // Se execve ritorna, qualcosa è andato storto
            perror("execve");
            return 1;
        }

        // Passa alla prossima directory in PATH
        dir = strtok(NULL, ":");
    }

    printf("Comando 'ls' non trovato in nessuna directory di PATH.\n");
    return 1;
}


                          👽👽👽👽👽👽👽👽👽👽👽




👽 "ACCESS()___________________________________________________________________
*******************************************************************************"
____________
👽 PROTOTIPO:
------------
int access(const char *pathname, int mode);

"pathname:" Una stringa che specifica il percorso del file o della directory di 
          cui si desidera controllare i permessi di accesso.
"mode:" Un intero che specifica le modalità di accesso che si desidera verificare. 
        Questo valore è solitamente una combinazione di flag come 
        F_OK (per verificare lesistenza del file), 
        R_OK (per verificare il permesso di lettura), 
        W_OK (per verificare il permesso di scrittura) e 
        X_OK (per verificare il permesso di esecuzione).

_________
👽 RETURN:
---------
0 se l accesso specificato è consentito, 
-1 se si verifica un errore. 

___________
👽 COSA FA:
-----------
Questa funzione viene utilizzata per verificare i permessi di accesso a un 
file o a una directory in base alla modalità specificata.

In generale verifica se un programma può accedere al file "pathname"





                          👽👽👽👽👽👽👽👽👽👽👽




👽 "UNLINK()___________________________________________________________________
*******************************************************************************"
____________
👽 PROTOTIPO:
------------
int unlink(const char *pathname);

"pathname:" Una stringa che specifica il percorso del file che si desidera 
            rimuovere.
_________
👽 RETURN:
---------
0 se la rimozione del file avviene con successo, 
-1 se si verifica un errore. 

___________
👽 COSA FA:
-----------
La funzione unlink() è utilizzata per rimuovere un file dal sistema di file. 
Quando si chiama questa funzione con il percorso del file che si desidera 
eliminare come argomento, il sistema operativo eliminerà effettivamente 
il file dal disco rigido o da qualsiasi altro dispositivo di archiviazione 
in cui è memorizzato.

Es:
int main() {
    const char *filename = "example.txt";

    // Creazione di un file vuoto per l'esempio
    FILE *file = fopen(filename, "w");
    if (file != NULL) {
        fclose(file);
        printf("File %s creato con successo.\n", filename);
    } else {
        perror("Errore nella creazione del file");
        return 1;
    }

    // Rimozione del file
    if (unlink(filename) == 0) {
        printf("File %s rimosso con successo.\n", filename);
    } else {
        perror("Errore nella rimozione del file");
        return 1;
    }

    return 0;
}

In questo esempio, viene creato un file chiamato "example.txt" e 
successivamente viene rimosso utilizzando la funzione unlink().


                          👽👽👽👽👽👽👽👽👽👽👽




👽 "FORK() NELLA SHELL__________________________________________________________
*******************************************************************************"

fork() nel contesto della shell è utilizzato per avviare un nuovo processo figlio 
che eseguirà un comando specificato dall utente, consentendo alla shell 
di continuare a funzionare in modo interattivo e gestire 
più comandi contemporaneamente.


Nel contesto del terminale, quando digito un comando e premo Invio, la shell 
esegue il comando creando un processo figlio tramite la chiamata di sistema fork. 
Questo processo figlio è una copia del processo della shell.

Il processo figlio quindi chiama "execve" per sostituire la sua memoria 
con quella del nuovo programma (il comando che ho digitato). Il nuovo 
programma inizia l esecuzione dal suo punto di ingresso, e il processo figlio 
diventa ora quel nuovo programma.

Nel frattempo il processo padre (chiamante) continua ad esistere, attendendo il 
completamento del processo figlio. Quando questo accade il processo padre (shell)
riprende il controllo, pronto ad accettare il prossimo comando


Il terminale, quindi, biforca ed esegue i nostri comandi con execve, ma recupera
il controllo alla fine della biforcazione, pronto ad accettare il prossimo comando.

👽 "FORK() IN C________________________________________________________________
*******************************************************************************"

____________
👽 PROTOTIPO:
------------
pid_t fork(void)

_________
👽 HEADER:   "unistd.h"
---------


___________
👽 COSA FA:
-----------
La funzione fork() in C viene utilizzata per creare un nuovo processo chiamato 
processo figlio. Questo nuovo processo è una copia esatta del processo chiamante, 
noto come processo padre, ma con alcune differenze chiave nel suo stato.

Quando fork() viene chiamato, il sistema operativo crea una copia esatta del 
processo chiamante, incluso il suo spazio di indirizzamento, il suo stato di 
esecuzione e altre risorse. 

La differenza principale tra il processo padre e il processo figlio è che il 
processo figlio ha un PID (Process ID) diverso da quello del processo padre, 
mentre tutte le altre risorse, inclusi i file aperti, le variabili, lo stato 
di esecuzione, ecc., sono identiche.

Dopo la chiamata a fork(), il processo padre e il processo figlio continuano 
l esecuzione a partire dal punto della chiamata fork(). 
Tuttavia, poiché il processo figlio è una copia esatta del processo padre, 
entrambi i processi eseguiranno le istruzioni successive alla chiamata a fork().

___________
👽 RETURN:
-----------
La funzione fork() restituisce un valore diverso nei due processi:

"- Nel processo padre, restituisce il PID del processo figlio appena creato.
- Nel processo figlio, restituisce zero (0) per indicare che è il processo figlio."

In questo modo, dopo la chiamata a fork(), sia il processo padre che il processo 
figlio possono continuare l esecuzione in modo indipendente, ognuno con il 
proprio flusso di controllo e con la possibilità di eseguire operazioni diverse.


👽 "ESEMPIO"
int main() {
    pid_t pid;    // Create a child process using fork()
    pid = fork();
   // Parent process
   printf("Hello, I am the parent process! My PID is %d, and my child's PID is %d.\n", getpid(), pid);
   return 0;
}

L output sarà:
Hello, I am the parent process! My PID is 1062886 , and my child s PID is 1062887
Hello, I am the parent process! My PID is 1062887 , and my child s PID is 0

fork() crea un processo figlio con PID 0, che cerca di imitare il processo 
genitore, quindi entrambi stampano il testo fornito, ma con i propri PID e 
quelli del loro figlio.



                          👽👽👽👽👽👽👽👽👽👽👽



👽 "WAITPID()__________________________________________________________________
*******************************************************************************"
____________
👽 PROTOTIPO:
------------
pid_t waitpid(pid_t pid, int *status, int options);

Con:
"pid:" Questo parametro specifica il PID del processo figlio che il processo 
       padre desidera attendere. Può assumere i seguenti valori:

       - Se pid > 0, waitpid() attende la terminazione del processo figlio 
         con il PID specificato.
       - Se pid == -1, waitpid() attende la terminazione di qualsiasi 
         processo figlio.
       - Se pid == 0, waitpid() attende la terminazione di qualsiasi processo 
         figlio nel medesimo gruppo di processi del chiamante.
       - Se pid < -1, waitpid() attende la terminazione di qualsiasi processo 
         figlio il cui gruppo di processi sia uguale al valore assoluto di pid.

"status:" Questo è un puntatore a una variabile di tipo int dove waitpid() 
          scriverà lo stato di uscita del processo figlio. Lo stato di uscita 
          contiene informazioni come il codice di uscita del processo figlio 
          o informazioni sul segnale che ha causato la sua terminazione. 
          È un parametro di output.

"options:" Questo parametro è utilizzato per specificare opzioni aggiuntive 
           per il comportamento della funzione waitpid(). 
           Le opzioni possono includere:
            
            - WNOHANG: Fa sì che waitpid() ritorni immediatamente se non 
              ci sono processi figli in uno stato di terminazione.
            - Altre opzioni specifiche del sistema operativo possono essere 
              disponibili per controllare il comportamento di waitpid().

___________
👽 RETURN:
-----------
Il valore restituito dalla funzione waitpid() è il PID del processo figlio 
che ha terminato o -1 in caso di errore.


_______________
👽 DESCRIZIONE:
---------------
"Attende la terminazione di un processo figlio:" 
Se il parametro pid è maggiore di zero, waitpid() attende la terminazione 
del processo figlio il cui PID corrisponde a quello specificato. 

Se pid è -1, waitpid() attende la terminazione di qualsiasi processo figlio.

"Recupera lo stato di uscita del processo figlio:" 
La funzione waitpid() scrive lo stato di uscita del processo figlio nel 
puntatore status fornito come argomento. 
Questo stato di uscita può contenere informazioni come il codice di uscita 
del processo figlio o le informazioni sull eventuale segnale che ha causato 
la terminazione del processo figlio.

"Opzioni di controllo:" Il parametro options consente di specificare opzioni 
aggiuntive per il comportamento della funzione waitpid(), 
come ad esempio se l attesa deve essere non bloccante o se si desidera 
tracciare solo i processi figli in un certo stato.

In sintesi, la funzione waitpid() consente al processo padre di attendere 
la terminazione di un processo figlio specifico e di ottenere informazioni 
sullo stato di uscita del processo figlio. 
È una parte fondamentale della gestione dei processi in un ambiente Unix-like, 
soprattutto dopo l uso di fork() e execve(), poiché consente al processo padre 
di coordinare l esecuzione dei suoi processi figli.





👽 ESEMPIO:

waitpid(pid, NULL, 0);

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

void    callexecve()
{
 char *const args[] = { "ls", NULL };
 char *const envp[] = { NULL };
 
 execve("/usr/bin/ls", args, envp);
 perror("execve");
    exit(EXIT_FAILURE); // Make sure to exit the child process if execve fails 
}

int main(void)
{
 pid_t pid;
 
 printf("Hi I am the main process. My PID is :%d\n", getpid());
 pid = fork();
 if (pid == -1)
  printf("Error while forking\n");
 else if (pid == 0)
 {
  printf("I am the child. But now a new parent. My PID is :%d --- My child's PID is %d\n", getpid(), pid);
  callexecve();
 }
 else if (pid > 1)
 {
  printf("I am the parent. My PID is :%d --- My child's PID is %d\n", getpid(), pid);
  waitpid(pid, NULL, 0); 
  printf("Got back the control?\n");
 }



                        ***************************



👽 "WAIT()__________________________________________________________________
*******************************************************************************"
____________
👽 PROTOTIPO:
------------
pid_t wait(int *status);

Con:
"status:" puntatore a un area di memoria in cui viene memorizzato lo stato di 
          terminazione del processo figlio.



__________
👽 RETURN:
-----------
"PID del processo figlio:"
Se wait() ha successo e un processo figlio termina, restituisce il PID del 
processo figlio che ha terminato.

"-1:"
Se wait() fallisce, restituisce -1 e imposta errno per indicare l errore 
specifico che è accaduto. Ad esempio, potrebbe restituire -1 se il processo 
padre non ha figli da attendere o se si verifica un errore interno.

Nel caso in cui wait() restituisca il PID del processo figlio terminato, 
è possibile utilizzare la funzione WIFEXITED() per verificare se il processo 
figlio è terminato normalmente, e la funzione WEXITSTATUS() per ottenere il 
valore di uscita del processo figlio. In alternativa, è possibile utilizzare 
altre macro come WIFSIGNALED(), WTERMSIG(), etc. per gestire diversi stati di 
terminazione del processo figlio.



_______________
👽 DESCRIZIONE:
---------------
La funzione wait() blocca il processo padre fino a quando uno qualsiasi dei 
suoi processi figli termina. Se ci sono più processi figli, 
"wait() ritorna quando uno qualsiasi di essi termina."




_________________________________
👽 DIFFERENZA WAIT() E WAITPID():
---------------------------------
1) Argomenti:
La funzione wait() non richiede alcun argomento specifico per identificare il 
processo figlio di cui attendere la terminazione. Si attende semplicemente 
che qualsiasi processo figlio termini.

La funzione waitpid() richiede l argomento pid per specificare il PID del 
processo figlio di cui attendere la terminazione. Questo consente un maggiore 
controllo da parte del processo padre su quale processo figlio attendere.


2) Controllo dei processi:

wait() attende che qualsiasi processo figlio termini, senza specificare quale.

waitpid() consente al processo padre di specificare esattamente quale processo 
figlio attendere, identificandolo tramite il PID. 
Inoltre, waitpid() fornisce ulteriori opzioni di controllo attraverso 
l argomento options, ad esempio per attendere la terminazione di un processo 
figlio in uno stato specifico o in modo non bloccante.




                          👽👽👽👽👽👽👽👽👽👽👽




👽 "PIPE()__________________________________________________________________
*******************************************************************************"
____________
👽 PROTOTIPO:
------------
int pipe(int pipefd[2]);

___________
👽 RETURN:
-----------
restituisce 0 se la pipe è stata creata con successo, 
altrimenti restituisce -1 in caso di errore

_______________
👽 DESCRIZIONE:
---------------
Questa funzione viene utilizzata per creare una pipe, un canale di comunicazione 
unidirezionale tra due processi.
Prende in input un array di interi pipefd di dimensione 2 e restituisce 0 se 
la pipe è stata creata con successo, altrimenti restituisce -1 in caso di errore.


La pipe creata ha due estremi:

pipefd[0]: Questo è il file descriptor di lettura della pipe. 
           I dati scritti nella pipe da un processo possono essere letti 
           da questo file descriptor.

pipefd[1]: Questo è il file descriptor di scrittura della pipe. 
           I dati scritti da un processo in questo file descriptor possono 
           essere letti da un altro processo tramite 
           il file descriptor di lettura.


In breve, pipe() crea una pipe e fornisce due file descriptors: 
uno per la lettura e uno per la scrittura. 
Questi file descriptors possono quindi essere utilizzati per inviare e ricevere 
dati tra i processi attraverso la pipe.

Quindi, pipe() crea una struttura di dati che consente ai processi di scrivere 
dati in un estremità della pipe e di leggerli dall altra estremità. 
Questa pipe rimane attiva finché non vengono chiusi entrambi i file descriptors 
associati, o finché il processo che ha creato la pipe termina.

I file descriptors pfd[0] e pfd[1] non fanno riferimento a file fisici nel 
sistema operativo, ma sono puntatori a un canale di comunicazione 
interprocessuale (IPC) chiamato pipe. 
Questi file descriptors sono utilizzati per indicare rispettivamente la parte 
di lettura e la parte di scrittura della pipe.

Quando si scrive su pfd[1], i dati vengono inviati alla pipe per essere letti 
da pfd[0], e viceversa. Quindi, in questo contesto, i file descriptors 
sono utilizzati come meccanismo per consentire la comunicazione unidirezionale 
tra i processi, piuttosto che per interagire con file fisici memorizzati su disco.


RIASSUMENDO:
1) Ho un processo che produce un output.

2) Questo output viene scritto su un estremità della pipe utilizzando il 
   file descriptor pfd[1].
2) Il secondo processo può leggere questi dati attraverso l estremità opposta 
   della pipe utilizzando il file descriptor pfd[0].

In questo modo, hai messo in comunicazione i due processi, consentendo loro di 
scambiare dati attraverso la pipe



NOTA: La pipe() va "aperta prima della chiamata a fork()" cosi da poter essere
      condivisa dai due pricessi




                          👽👽👽👽👽👽👽👽👽👽👽




👽 "DUP2()__________________________________________________________________
*******************************************************************************"
____________
👽 PROTOTIPO:
------------
int dup2(int oldfd, int newfd);

Con:
"oldfd:" Il file descriptor da duplicare.
"newfd:" Il file descriptor su cui duplicare oldfd.

___________
👽 RETURN:
-----------
"Se ha successo:" restituisce il nuovo file descriptor (newfd) che è stato 
                  associato con successo al file descriptor specificato (oldfd).

"Se si verifica un errore:" restituisce -1 e imposta errno per indicare il tipo 
                            specifico di errore che si è verificato. 
                            Ad esempio, può restituire -1 se oldfd o newfd non 
                            sono validi, oppure se si verificano problemi 
                            di allocazione di risorse.

_______________
👽 DESCRIZIONE:
---------------
La funzione dup2() è una chiamata di sistema che viene utilizzata per duplicare 
un file descriptor in un altro file descriptor specificato

Questa funzione crea una copia del file descriptor oldfd e lo assegna al file 
descriptor newfd. 
Se newfd è già aperto,verrà chiuso prima di duplicare oldfd.

La funzione dup2() è comunemente utilizzata per cambiare l associazione di un 
file descriptor a uno specifico file o dispositivo. 
Ad esempio, può essere utilizzata per riorientare l input o l output di un 
programma verso un file, una pipe o un altro dispositivo di I/O.


In altre parole, la funzione dup2() serve a creare una copia di un file 
descriptor specificato e ad associarla a un nuovo file descriptor. 
Questo può essere utile per cambiare l output o l input di un programma verso 
un altra destinazione senza dover chiudere o aprire manualmente i file descriptors.


Quando la funzione dup2(oldfd, newfd) ha successo, il file descriptor newfd 
viene sostituito con una copia di oldfd



"ESEMPIO"
dup2(pfd[0], 0);
Sostituisce il file descriptor standard di input 0 con il fd pfd[0] che 
rappresenta l"estremità di lettura di una pipe"



                          👽👽👽👽👽👽👽👽👽👽👽



👽 "ACCESS()__________________________________________________________________
*******************************************************************************"

La funzione access è una funzione della libreria standard del linguaggio di 
programmazione C. Essa è utilizzata per verificare 
l'accessibilità di un file o di un percorso di directory.








