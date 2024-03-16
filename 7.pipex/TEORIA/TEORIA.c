____________________________________PIPEX_______________________________________
👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽
👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻
________
👽LINKS
--------
https://medium.com/@lannur-s/pipex-42-chapter-1-metamorphosis-execve-1a4710ab8cb1




- Questo programma riproduce il comportamento della pipe della shell |.
- Viene lanciato cosi: ./pipex infile cmd1 cmd2 outfile
  E riproduce il comportamento della seguente linea di comando:
  < infile cmd1 | cmd2 > outfile

- Idea generale: Leggiamo da "infile", eseguiamo "cmd1" con infile come input,
                 mandiamo l outupt a "cmd2" che scriverà su "outfile"

                 La funzione "pipe()" manda l output del primo "execve()" come
                 input del secondo "execve()". La funzione "forck()" runna due 
                 processi (due comandi) in un singolo programma.
                 La funzione "dup2()"  scambia i nostri file con stdin e stdout.

* COME LAVORA LA SHELL PER ESEGUIRE UNA PIPE:
  - Il core di questo meccanismo risiede nel comando "exceve()" 
    (execute with vector of environment variables)

















👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻
👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽
_______________________________USARE FORK ED EXECVE_____________________________
👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽
👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻

1) "execve() in azione:" Chi ha il controllo - il processo padre o quello figlio?
2) "Il passaggio di consegne:" Una volta che execve() fa il suo lavoro, 
   chi ottiene di nuovo il controllo? Il padre continua a guidare, o è il figlio?
3) "Il Grande Ritorno:" Dopo l azione, come avviene il ritorno del controllo. 
   avviene realmente o c è dell altro?

1) "execve() in azione: DOVE USARLA"
   - Nel nostro programma chiameremo execve() "ALL'INTERNO DEL PROCESSO FIGLIO"
   
   NOTA: Come per la shell, se in un programma uso la funzione fork() significa
         che voglio eseguire piu di un operazione alla volta.
         Dovro quindi usare la funzione exevce() (che andra ad eseguire questa
         nuova operazione) dentro al processo figlio che andro a generare 

     Se stai programmando in C e stai usando la funzione fork() in un programma, 
     la chiamata alla funzione execve() dovrebbe avvenire all interno del 
     |processo figlio creato da fork(). Dopo aver chiamato fork(), 
     il processo padre e il processo figlio condivideranno lo stesso codice e 
     lo stesso spazio di indirizzamento. Pertanto, il processo figlio dovrebbe 
     chiamare execve() per sostituire il suo spazio di indirizzamento con un 
     nuovo programma. Il processo padre può continuare a eseguire il 
     suo codice senza chiamare execve().

     "ESEMPIO"
    int main() {
    pid_t pid = fork();
    
    if (pid == -1) {
        // Errore nella creazione del processo figlio
        perror("fork");
        return 1;
    } else if (pid == 0) {
        // Codice eseguito nel processo figlio
        char *args[] = {"/bin/ls", "-l", NULL}; // Esempio di argomenti per ls
        execve("/bin/ls", args, NULL);
        // Se execve ritorna, si è verificato un errore
        perror("execve");
        return 1;
    } else if (pid > 1)
        // Codice eseguito nel processo padre
        printf("Processo padre continua...\n");
        // Il processo padre può eseguire ulteriori operazioni o aspettare il figlio
    }
    
    return 0;
} 

   NOTA: "Il codice scritto dopo la chiamata a execve() (contenuta nella parte 
         di codice eseguita else if (pid == 0)), nel caso in cui execve() 
         abbia avuto successo, quel codice non verrà mai eseguito." 
         
         Questo perché execve() sostituisce l intero spazio di indirizzamento 
         del processo chiamante con il nuovo programma specificato. 
         Quindi, il flusso di esecuzione del programma passa direttamente al 
         nuovo programma specificato da execve(), e il codice successivo 
         a execve() non viene raggiunto o eseguito.
         
         Tuttavia, se execve() fallisce per qualche motivo, allora il flusso 
         di esecuzione passerà al codice successivo a execve(). In tal caso, 
         è comune gestire l errore utilizzando perror() o 
         altre funzioni di gestione degli errori.



2) "Il passaggio di consegne:"
   - Durante l esecuzione del programma chiamato da execve(), il processo padre 
     rimane in attese
   - Una volta completata la task eseguita da execve() il processo padre 
     entra in gioco 
     (parliamo della parte di codice eseguita quando else if (pid > 1))
     
     NOTA: Se non ci fosse stato execve() questa parte sarebbe stata eseguita 
           simultaneamente al processo figlio

     ATTENZIONE: il processo padre non ha garanzia di attendere il completamento 
                 del processo figlio prima di riprendere il proprio flusso di 
                 esecuzione. 
                 
                 Dopo aver chiamato fork(), il processo padre e il processo 
                 figlio sono entrambi in esecuzione, ma in parallelo. 
                 Se il processo figlio esegue execve() per eseguire un nuovo 
                 programma, non c è alcuna garanzia che il processo padre 
                 aspetterà che il nuovo programma nel processo figlio termini 
                 prima di continuare la propria esecuzione.
                 
                 Questo significa che potrebbe verificarsi una sovrapposizione 
                 temporale tra l esecuzione del nuovo programma nel processo 
                 figlio e l esecuzione del codice del processo padre. 
                 Se il processo padre dipende dai risultati del processo 
                 figlio, potrebbe essere necessario implementare meccanismi di 
                 sincronizzazione o di comunicazione tra processi per garantire 
                 che il processo padre aspetti il completamento 
                 del processo figlio prima di procedere. 
                 
                 (Questi meccanismi di controllo possono essere imnplementati 
                  tramite le funzioni wait(), waitpid() o pipe())


3) "Il Grande Ritorno:"

Il processo padre deve attendere che il figlio svolga il suo compito, fino 
a quando non è completato. 
La funzione waitpid() svolge un ruolo chiave nella gestione dei processi
padre-figlio, soprattutto nell uso delle funzioni di fork ed execve. 

Consente a un processo padre di attendere che un processo figlio specifico 
completi la sua esecuzione e di recuperare informazioni sullo 
stato di uscita del figlio.

Con queste informazioni (esempio della funzione waitpid()) possiamo simulare 
l esecuzione di un singolo comando Unix in C. 
Dobbiamo ora vedere le pipes 












👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻
👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽
__________________________PIPE() con e senza fork()_____________________________
👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽
👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻

👽 Una pipe è un meccanismo di comunicazione interprocessuale (IPC) che consente 
    lo scambio di dati tra due processi in un sistema operativo Unix o Unix-like. 
    Una pipe può essere considerata come un "tubo" virtuale che collega 
    l'output di un processo all input di un altro processo.'

* Le pipe sono create utilizzando la funzione di sistema pipe(), 
  che restituisce due file descriptors: 
  uno per la lettura (pfd[0]) e uno per la scrittura (pfd[1]).
  (Vedi meglio la funzione nella sezione dedicata) 

* Sono monodirezionali

* In C, per creare una pipe che connetta due processi, vengono utilizzati due 
  file descriptors. 
  1) Uno dei file descriptors viene utilizzato per 
    "scrivere dati nella pipe" (pfd[1]), 
    
  2) mentre l altro viene "utilizzato per leggere i dati dalla pipe" (pfd[0]).

  Il processo che scrive invia i dati attraverso il file descriptor pfd[1], 
  e il processo che legge li riceve attraverso il file descriptor pfd[0]. 
  "I dati fluiscono in un unica direzione dalla scrittura alla lettura."

                          PIPTE
                         _______
                    --> |_______| -->
               PFD[1]             pfd[0]
               Scrive da          legge da
               questa             quetsa estrmità
              estremità              



--------------------------------------------------------------------------------
"ESEMPIO"
In questo esempio, il processo padre scrive un messaggio sulla pipe utilizzando 
il file descriptor pfd[1], mentre il processo figlio legge il messaggio dalla 
pipe utilizzando il file descriptor pfd[0].


/*******CREAZIONE DELLA PIPE***************************************************/
Si dichiara un array pfd di interi con due elementi. Questi elementi saranno 
utilizzati per i due estremi della pipe. La funzione pipe() viene chiamata 
per creare la pipe e restituisce 0 se ha successo, altrimenti restituisce -1 
e stampa un messaggio di errore con perror().
/******************************************************************************/
int main() {
    int pfd[2];
    char buffer[20];

    if (pipe(pfd) == -1) {
        perror("pipe");
        return 1;
    }

/******CREAZIONE DEL PROCESSO FIGLIO*******************************************/
    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        return 1;
    } else if (pid == 0) { // Processo figlio (lettura dalla pipe)

    /**************************************************************************/
    Nel processo figlio, si chiude il file descriptor di scrittura (pfd[1]) 
    perché il figlio non scriverà sulla pipe. Quindi si legge dalla pipe 
    utilizzando il file descriptor di lettura (pfd[0]). 
    Il messaggio letto viene stampato a schermo, 
    e infine si chiude il file descriptor di lettura.
    /**************************************************************************/
        close(pfd[1]); // Chiudo il file descriptor di scrittura

        // Leggo dalla pipe
        read(pfd[0], buffer, sizeof(buffer));
        printf("Processo figlio: Ricevuto messaggio: %s\n", buffer);

        close(pfd[0]); // Chiudo il file descriptor di lettura

/********PROCESSO PADRE********************************************************/
Nel processo padre, si chiude il file descriptor di lettura (pfd[0]) perché 
il padre non leggerà dalla pipe. Viene quindi definito un messaggio da scrivere 
sulla pipe. Questo messaggio viene scritto sulla pipe utilizzando il file 
descriptor di scrittura (pfd[1]), e infine si chiude 
il file descriptor di scrittura. 
 /*****************************************************************************/       
    } else { // Processo padre (scrittura sulla pipe)
        close(pfd[0]); // Chiudo il file descriptor di lettura

        // Scrivo sulla pipe
        const char *msg = "Messaggio dalla pipe";
        write(pfd[1], msg, sizeof(msg));

        close(pfd[1]); // Chiudo il file descriptor di scrittura
    }

    return 0;
}

In questo modo, il processo padre scrive un messaggio sulla pipe e il processo 
figlio legge quel messaggio dalla pipe. 
La pipe gestisce il flusso dei dati tra i due processi in modo unidirezionale.

NOTA: 
"Scrivere sulla pipe" significa inserire dati nella pipe, in modo che possano 
essere letti da un altro processo che ha accesso alla stessa pipe. 
In pratica, il processo che scrive invia dati attraverso uno dei file 
descriptors associati alla pipe, mentre il processo che legge riceve quei dati 
attraverso un altro file descriptor associato alla stessa pipe.
--------------------------------------------------------------------------------




👽 Associate alla funzione pipe() avremo quindi le funzioni:
    write(fd[1], char * buf1, len1);
    read(fd[0], char * buf2, len2);

    Le quali leggerenno e scriveranno dalle due estremità della pipe restituendo
    rispettivamente il numero di caratteri scritti e letti.




--------------------------------------------------------------------------------
"ESEMPIO"

#include <unistd.h>
#include <stdio.h>

int main()
{
    int pfd[2];  // Dichiarazione di un array di interi per i file descriptors 
                //  della pipe

    char str[20];  // Dichiarazione di un array di caratteri per memorizzare 
                   // i dati letti dalla pipe

    // Creazione della pipe
    pipe(pfd);

    // Scrittura del messaggio "hello" sulla pipe tramite il file descriptor 
    // di scrittura pfd[1]
    write(pfd[1], "hello", 5);

    // Lettura dei dati dalla pipe tramite il file descriptor di lettura pfd[0]
    // Viene letto solo il numero di byte specificato (2 byte) e memorizzato 
    // nell'array str
    read(pfd[0], str, 2);

    // Aggiunta del terminatore di stringa '\0' per assicurarsi che str 
    // sia una stringa valida
    str[2] = '\0';

    // Stampa della stringa letta dalla pipe
    printf("%s\n", str);
}
--------------------------------------------------------------------------------

👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻
"CHIUDUSA DELLE ESTREMITA' "

👽 Come possiamo stabilire una pipe fra due processi creati tramite fork()?
    (Non consideriamo al momento execve())

    Ricordiamo l ordine stabilito: Il figlio viene eseguito e termina per primo
                                   mentre il padre subbentra successivamente 
                                   (grazie alle funzioni waitpid() o wait())

Quindi ora proviamo a far scrivere qualcosa al figlio per poi farlo leggere
al padre: 

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main(void)
{
    pid_t pid;   // variabile per memorizzare il PID del processo figlio
    int pfd[2];  // array di interi per i file descriptors della pipe

    // Creazione della pipe
    pipe(pfd);

    // Creazione di un nuovo processo figlio
    pid = fork();
    if (pid < 0) 
    {
        fprintf(stderr, "Fork2 failed.\n");
        return 1;
    }

// Questo blocco di codice è eseguito solo nel processo figlio
    else if (pid == 0)
    {        
        // Chiude il file descriptor di lettura della pipe perché il processo 
        // figlio non lo utilizzerà
        close(pfd[0]); 

        // Scrive il messaggio sulla pipe attraverso il file descriptor di 
        // scrittura pfd[1]
        write(pfd[1], "this is a new message", 22);  

        // Chiude il file descriptor di scrittura della pipe dopo aver 
        // scritto il messaggio
        close(pfd[1]); 

        // Termina il processo figlio
        exit(EXIT_SUCCESS);     
    }

// Questo blocco di codice è eseguito solo nel processo padre
    else 
    {   
        // Chiude il file descriptor di scrittura della pipe perché il processo 
        // padre non lo utilizzerà
        close(pfd[1]); 

        // Dichiarazione di un array di caratteri per memorizzare i dati 
        // letti dalla pipe
        char str[22];

        // Legge i dati dalla pipe attraverso il file descriptor di lettura 
        // pfd[0] e li memorizza nell'array str
        read(pfd[0], str, 22);

        // Stampa il messaggio letto dalla pipe
        printf("Parent received:%s\n", str);

        // Chiude il file descriptor di lettura della pipe dopo aver letto 
        close(pfd[0]); 

        // Il processo padre attende che il processo figlio termini l'esecuzione
        wait(NULL);
    }

    // Restituisce EXIT_SUCCESS indicando che il programma è terminato correttamente
    return EXIT_SUCCESS;
}            --> l output sarà:  Parent recived: this is a new message 



* Concentriamoci sull uso combinato di pipe() e fork():
  Un singolo processo infatti non ha bisogno di una pipe. Queste sono usate 
  quando abbiamo 2 processi che vogliono comunicare fra lore (one-way)

int pfd[2];

pipe(pfd);
pid = fork();

1) Prima del fork:

                              PIPTE
                             _______
                        --> |_______| -->
                   PFD[1]             pfd[0]
                   Scrive da          legge da
                   questa             quetsa estrmità
                  estremità              


2) dopo il fork:

                pfd[1]        parent        pfd[0]
                      _____           ____
                -->  |__   |_________|   _| -->
                        |               | 
                      __|   _________   |_
                -->  |_____|          |___| -->

                 pfd[1]         child        pfd[0]

  Dopo la chiamata a fork() verranno a crearsi due estremi di lettura e due
  di scrittura nella pipe.
  - per "chiudere l'estremo di lettura entrambe le read ends dovranno essere chiuse"
  - per "chiudere l'estremo di scrittura entrambe le write ends dovranno essere chiuse"

  Entrambi i processi potranno scrivere-sulla e leggere-dalla pipe, ma non 
  possiamo dire quale processo riceverà quali dati.


👽 Per questo "un processo dovrà chiudere la sua estremità di lettura mentre 
    l'altro chiude la sua estremità di scrittura", cosi di ricreare una pipe 
    semplice e monodirezionale.

    Nell ellesempio sopra, dato che abbiamo deciso che il processo figlio 
    scriverà, andrò a chiudere la sua estremità di lettura (pfd[0]). 
    Farò lo stesso ma in modo opposto con il padre:

    else if (pid == 0)
    {
      close(pfd[0]); //close unused end (the reading end) of the pipe
      ...  
    }
    else 
    {
      close(pfd[1]); //close unused end (the writing end) of the pipe
      ...
    }



👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻
                "REINDIRIZZAMENTO DI INPUT, OUTPUT TRAMITE DUP2"

👽 Una pipeline funziona perché i due processi conoscono il file descriptor 
    di ciascuna estremità della pipe. 
    
    Ogni processo PERò ha tre file descriptor predefiniti: 
    stdin (0), stdout (1) e stderr (2). 
    I file descriptors effettivi utilizzati dipenderanno dai file aperti in 
    precedenza e potrebbero essere, ad esempio, 3 e 4.

    Quando uno dei processi sostituisce se stesso con un operazione di exec, 
    il nuovo processo avrà aperti i file descriptor 0, 1, 2, 3 e 4. 
    Come farà a sapere quali di questi file descriptor appartengono alla pipe? 
    Non può saperlo.

    Cioè:
    Quando un processo esegue un operazione di exec, sostituisce la propria 
    immagine con un nuovo programma. 
    Questo significa che il nuovo programma inizia a eseguire il codice del 
    programma specificato nell operazione di exec, ereditando alcune proprietà 
    dal processo precedente, come i file descriptor aperti.

    Tuttavia, il nuovo programma non conosce la provenienza dei file descriptor 
    ereditati. Ciò significa che, se uno dei file descriptor ereditati è 
    associato a una pipe, il nuovo programma non ha modo di sapere quale file 
    descriptor appartiene a quella specifica pipe.


    ESEMPIO: supponiamo che nel processo precedente sia stata creata una pipe e 
             che il file descriptor di scrittura della pipe sia 3 e il file 
             descriptor di lettura sia 4. 

             Dopo l operazione di exec, il nuovo programma erediterà i 
             file descriptor 0, 1, 2, 3 e 4 (perchè 0, 1 e 2 esistono in automatico
             e a questi si aggiungono il 3 e 4, rispettivamente fd di lettura
             e scrittura della pipe creata)
             ma non saprà quali file descriptor appartengono alla pipe.


    ESEMPIO 
    PRATICO: Per implementare ls | wc, la shell crea una pipe e quindi esegue 
             una biforcazione (fork). 
             Il processo padre esegue un exec per essere sostituito da ls, 
             mentre il processo figlio esegue un exec per essere sostituito da wc. 
             
             L estremità di scrittura della pipe potrebbe avere il descrittore 3 
             e l estremità di lettura potrebbe avere il descrittore 4. 
             
             Normalmente, ls scrive sull output standard (descrittore 1) e wc 
             legge dall input standard (descrittore 0). 
             
             Come avviene il collegamento tra questi?

             Quando la shell esegue ls, il file descriptor 1 (standard output) 
             viene rindirizzato per scrivere sulla pipe (il 3), invece che 
             sull output standard dello schermo. 
             La shell fa questo prima di eseguire l exec per ls. 
             In questo modo, l"output di ls viene inviato alla pipe."

             Allo stesso modo, quando la shell esegue wc, il file descriptor 0 
             (standard input) viene rindirizzato per leggere dalla pipe (fd 4), 
             invece che dall input standard della tastiera. 
             Anche in questo caso, la shell configura il rindirizzamento 
             prima di eseguire l exec per wc. 
             Così, wc legge l input dalla pipe, che è l output di ls, 
             contando le righe, le parole e i byte come previsto.


"PER MODIFICARE I FD DI INPUT ED OUTPUT USEREMO LA FUNZIONE DUP2 (vedi sezione funzioni)" 


"ESEMPIO"
Supponiamo di avere due processi collegati e di voler reindirizzare i loro input
ed output dagli STANDARD I/O alla pipe (cioè fra loro) 


In breve, questo codice crea un processo figlio che scrive un messaggio sulla 
pipe, il processo padre legge il messaggio dalla pipe e lo stampa. 
La funzione dup2() viene utilizzata per reindirizzare l input e l output 
standard dei processi verso la pipe, in modo che i dati possano 
fluire correttamente tra i due processi.

...
// Questo blocco di codice è eseguito solo nel processo figlio.
else if (pid == 0) {

    close(pfd[0]); // Chiude il file descriptor di lettura della pipe nel 
                   // processo figlio perché non sarà utilizzato.

    dup2(pfd[1], 1); // Duplica il file descriptor della pipe e associa il 
                     //risultato al file descriptor standard di output (stdout).

    close(pfd[1]); // Chiude il file descriptor di scrittura della pipe nel 
                   // processo figlio dopo aver reindirizzato l'output standard.

    write(1, "this is a new message", 22); // Scrive il messaggio "this is a new 
                                           // message" sull'output standard del 
                                           // processo figlio, che in realtà è la pipe.

    exit(EXIT_SUCCESS); // Il processo figlio esce con successo dopo aver 
                        //scritto il messaggio sulla pipe.
}

// Questo blocco di codice è eseguito solo nel processo padre.
else {
    

    close(pfd[1]); // Chiude il file descriptor di scrittura della pipe nel 
                   // processo padre perché non sarà utilizzato.

    dup2(pfd[0], 0); // sostituisce il file descriptor standard di input (stdin, con indice 0) 
                     //con il file descriptor pfd[0], che rappresenta l'estremità di lettura della pipe.

    close(pfd[0]); // Chiude il file descriptor di lettura della pipe 
                   // nel processo padre dopo aver reindirizzato l'input standard.

    char str[22]; // Dichiarazione di un array di caratteri per memorizzare i dati letti dalla pipe.

    read(0, str, 22); // Legge i dati dalla pipe attraverso l'input standard e 
                      // li memorizza nell'array str.

    printf("Parent received:%s\n", str); // Stampa il messaggio letto dalla 
                                         // pipe sullo standard output del processo padre.

    wait(NULL); // Il processo padre attende che il processo figlio termini l'esecuzione.
}


NOTA: Nel codice precedente, dopo aver eseguito le chiamate dup2(), 
      "CHIUDO I FILE DESCRIPTOR PFD UTILIZZATI PER LA PIPE" 
      Questo è fatto perché dopo aver riorientato l input e l output standard 
      usando dup2(), non ho più bisogno dei file descriptor specifici per la pipe, 
      poiché l input e l output standard sono stati riorientati verso la pipe stessa.

      In pratica, dopo aver eseguito dup2(), il processo figlio pensa ancora di 
      leggere dalla tastiera e scrivere sul terminale, ma in realtà legge dalla 
      pipe e scrive sulla pipe. 
      "Chiudendo i file descriptor pfd, ci assicuriamo che non ci siano 
      ulteriori accessi alla pipe tramite quei file descriptor," 
      poiché ora l input e l output standard sono stati completamente 
      riorientati verso la pipe.







👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻
👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽
__________________________ENVIRORMENT VARIABLES_____________________________
👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽
👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻👻

👽 Scrivendo sul terminale il comando "envp" Otterro le mie envp

SYSTEMD_EXEC_PID=380240
SSH_AUTH_SOCK=/run/user/101161/keyring/ssh
SESSION_MANAGER=local/e4r1p2.42roma.it:@/tmp/.ICE-unix/380217,unix/e4r1p2.42roma.it:/tmp/.ICE-unix/380217
GNOME_TERMINAL_SCREEN=/org/gnome/Terminal/screen/c757d6c1_02bc_4269_96f3_57039d319e93
LANG=en_US.UTF-8
LANGUAGE=en_US:
XDG_CURRENT_DESKTOP=ubuntu:GNOME
QT_ACCESSIBILITY=1
LC_IDENTIFICATION=fr_FR.UTF-8
XDG_GREETER_DATA_DIR=/var/lib/lightdm-data/ldi-fior
COLORTERM=truecolor
LIBVIRT_DEFAULT_URI=qemu:///system
GPG_AGENT_INFO=/run/user/101161/gnupg/S.gpg-agent:0:1
DESKTOP_SESSION=ubuntu
HOME=/nfs/homes/ldi-fior
XDG_MENU_PREFIX=gnome-
XDG_SESSION_PATH=/org/freedesktop/DisplayManager/Session1
QT_IM_MODULE=ibus
USER=ldi-fior
DOTNET_BUNDLE_EXTRACT_BASE_DIR=/nfs/homes/ldi-fior/.cache/dotnet_bundle_extract
DBUS_SESSION_BUS_ADDRESS=unix:path=/run/user/101161/bus
DOCKER_HOST=unix:///run/user/101161/docker.sock
LC_NUMERIC=fr_FR.UTF-8
SSH_AGENT_LAUNCHER=gnome-keyring
GTK_MODULES=gail:atk-bridge
XDG_CONFIG_DIRS=/etc/xdg/xdg-ubuntu:/etc/xdg
GTK_IM_MODULE=ibus
XDG_SESSION_DESKTOP=ubuntu
KRB5CCNAME=FILE:/tmp/krb5cc_101161_v7KpE8
GNOME_DESKTOP_SESSION_ID=this-is-deprecated
LC_TIME=fr_FR.UTF-8
XDG_DATA_DIRS=/usr/share/ubuntu:/usr/share/gnome:/nfs/homes/ldi-fior/.local/share/flatpak/exports/share:/var/lib/flatpak/exports/share:/usr/local/share:/usr/share:/var/lib/snapd/desktop
LOGNAME=ldi-fior
LC_PAPER=fr_FR.UTF-8
XDG_SEAT_PATH=/org/freedesktop/DisplayManager/Seat0
PATH=/nfs/homes/ldi-fior/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin:/nfs/homes/ldi-fior/.dotnet/tools
XDG_RUNTIME_DIR=/run/user/101161
XMODIFIERS=@im=ibus
SHELL=/bin/zsh
XDG_SESSION_TYPE=x11
LC_MONETARY=fr_FR.UTF-8
LC_TELEPHONE=fr_FR.UTF-8
LC_MEASUREMENT=fr_FR.UTF-8
VTE_VERSION=6800
GNOME_TERMINAL_SERVICE=:1.148
XAUTHORITY=/nfs/homes/ldi-fior/.Xauthority
PWD=/nfs/homes/ldi-fior
LC_NAME=fr_FR.UTF-8
XDG_SESSION_CLASS=user
GDMSESSION=ubuntu
TERM=xterm-256color
DISPLAY=:0
LC_ADDRESS=fr_FR.UTF-8
SHLVL=1
OLDPWD=/nfs/homes/ldi-fior
ZSH=/nfs/homes/ldi-fior/.oh-my-zsh
PAGER=less
LESS=-R
LSCOLORS=Gxfxcxdxbxegedabagacad
LS_COLORS=rs=0:di=01;34:ln=01;36:mh=00:pi=40;33:so=01;35:do=01;35:bd=40;33;01:cd=40;33;01:or=40;31;01:mi=00:su=37;41:sg=30;43:ca=30;41:tw=30;42:ow=34;42:st=37;44:ex=01;32:*.tar=01;31:*.tgz=01;31:*.arc=01;31:*.arj=01;31:*.taz=01;31:*.lha=01;31:*.lz4=01;31:*.lzh=01;31:*.lzma=01;31:*.tlz=01;31:*.txz=01;31:*.tzo=01;31:*.t7z=01;31:*.zip=01;31:*.z=01;31:*.dz=01;31:*.gz=01;31:*.lrz=01;31:*.lz=01;31:*.lzo=01;31:*.xz=01;31:*.zst=01;31:*.tzst=01;31:*.bz2=01;31:*.bz=01;31:*.tbz=01;31:*.tbz2=01;31:*.tz=01;31:*.deb=01;31:*.rpm=01;31:*.jar=01;31:*.war=01;31:*.ear=01;31:*.sar=01;31:*.rar=01;31:*.alz=01;31:*.ace=01;31:*.zoo=01;31:*.cpio=01;31:*.7z=01;31:*.rz=01;31:*.cab=01;31:*.wim=01;31:*.swm=01;31:*.dwm=01;31:*.esd=01;31:*.jpg=01;35:*.jpeg=01;35:*.mjpg=01;35:*.mjpeg=01;35:*.gif=01;35:*.bmp=01;35:*.pbm=01;35:*.pgm=01;35:*.ppm=01;35:*.tga=01;35:*.xbm=01;35:*.xpm=01;35:*.tif=01;35:*.tiff=01;35:*.png=01;35:*.svg=01;35:*.svgz=01;35:*.mng=01;35:*.pcx=01;35:*.mov=01;35:*.mpg=01;35:*.mpeg=01;35:*.m2v=01;35:*.mkv=01;35:*.webm=01;35:*.webp=01;35:*.ogm=01;35:*.mp4=01;35:*.m4v=01;35:*.mp4v=01;35:*.vob=01;35:*.qt=01;35:*.nuv=01;35:*.wmv=01;35:*.asf=01;35:*.rm=01;35:*.rmvb=01;35:*.flc=01;35:*.avi=01;35:*.fli=01;35:*.flv=01;35:*.gl=01;35:*.dl=01;35:*.xcf=01;35:*.xwd=01;35:*.yuv=01;35:*.cgm=01;35:*.emf=01;35:*.ogv=01;35:*.ogx=01;35:*.aac=00;36:*.au=00;36:*.flac=00;36:*.m4a=00;36:*.mid=00;36:*.midi=00;36:*.mka=00;36:*.mp3=00;36:*.mpc=00;36:*.ogg=00;36:*.ra=00;36:*.wav=00;36:*.oga=00;36:*.opus=00;36:*.spx=00;36:*.xspf=00;36:
_=/usr/bin/env


Queste variabili rappresentano il mio sistema.

👽 - Ogni variabile e nella forma: NOME=valore
   - I nomi sono in caps
   - I valori sono rappresentati da stringhe (infatti avro **envp)

👽 Il loro scopo e comunicare al programma i settaggi della macchina

👽 "Passare ad un programma le variabili di anbiente"
   Scrivendo questo:
   int main(int argc, char **argv, char **envp)
   Il sistema passera al mio programma le variabili d anbiente nella forma di 
   un array di stringhe NULL-terminato

👽 "Settare una varibile d anbiente da terminale"
   - Da terminare posso scrivere ad esempio:
     PASSCODE=esempio ./a.out
     Questo comando impostera la variabile d anbiente PASSCODE con il valore esempio
     solo per questo programma
   
   - Se voglio settarla per l intera sessione del terminale dovro usare il comando
     "export":
     export PASSCODE=esempio 
     Questa variabile sara impostata per ogni programma runnato in questa sessione
     del terminale

     Il comando "unset" la rimuovera

👽 "Settare una varibile d anbiente nel main"
    Posso usare le funzioni "putenv" o "setenv"
    putenv(PASSCODE=esempio);
    setenv("PASSCODE", "esempio", 1);

    Settera la variabile per questo programma e tutti i suoi processi figlio 