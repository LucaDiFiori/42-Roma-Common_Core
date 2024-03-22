"**********************************PIPEX***************************************"
👽 ESECUZIONE:
./pipex file1 cmd1 cmd2 file2

👽 ARGOMENTI:
4: 2 file
   2 comandi shell con i loro parametri

👽  COMPORTAMENTO:
< file1 cmd1 | cmd2 > file2

👽 ESEMPIO
./pipex infile "ls -l" "wc -l" outfile 
Dovra comportarsi come:  < infile ls -l | wc -l > outfile

👽 ERRORI
In caso di errove veder comportamento della shell



_______________________________UNDERSTAND PIPEX_________________________________
42 gitbook: https://42-cursus.gitbook.io/guide/rank-02/pipex

The goal of pipex is to develop a program that simulates the pipes in the shell.

Prendiamo un esempio:
< infile grep a1 | wc -w > outfile

"Simbolo <"
- e il simbolo di IMPUT DIRECTION
- Nell esempio "<" ridireziona il contenuto di "infile" allo standart input.
  Cosi che, quando grep leggera dallo standard in, ricevera il contenuto di 
  infile

"Simbolo <<"
E un simbolo di reindirizzamento di input.
Dice alla shell di leggere dallo STDIN fino a che non incontra un "LIMITE" 
specificato: cmd << LIMITER | cmd1 >> file
Es:
cat << LIM >> outfile
Hi!
How are you?
LIM

In questo esempio il comando cat aspetta di leggere "LIM" prima di stampare

(Il nostro programma dovrà fare lo stesso:
 ./ pipex here_doc LIM "cat" "cat" outfile
 hi,
 how are you?
 LIM)

"Simbolo >"
l operatore ">" rappresentra l 'output redirection'
Nel nostro esempio, ">" scrive l output di wc sull outfile.
Questo simbolo rimpiazza il contenuto del file alla sua destra con il comando
alla sua sinistra

"Simbolo >>"
Fa la stessa cosa del precedente ma invece di sovrascrivere "appende"


________________________________CHECKLIST_______________________________________
_____
MAIN()
-----
- Check the existence of infile and outfile
- be sure to understand what > does when the file does not exist
  (Se outfile non esiste, il comando ">" lo creerà)
- Create the necessary pipe (or pipes)
- Create a child process for each command
- Wait for all the processes to end before writing to the outfile

________________
EXECUTE (EXECVE)
----------------
Remember that the execve() function needs the path to a binary file as parameter, 
so you ll have to find where the commands binaries are stored on your computer. 
Before going further, you have to know how to find any command binary.

(Vedere esempio in "teoria.c" nella funione "execve". Non posso però usare la 
funzione usata nell esempio. Dovrò quindi fare uno split sull array di stringhe
envp (variabili d anbiente), usando come separatore "PATH". Dovrò poi togliere 
la scritta "PATH" ed estrarre tutti i path. Mettere alla fine di ogni path il comando
che voglio e testarlo con la funzione eccess() )

- Check in all possible locations if the binary (command) requested by the 
  user exists.
- "Build" the arguments array for the command.
- Execute the command using execve()




________________________________PROGRAM_MAP_____________________________________
NOTE: -Gli errori vanno stampati nello stderror
      - fd[0] = file di lettura dalla pipe
      - fd[1] = file di scrittura nella pipe
      - STDIN = 0 (lettura)
      - STDOUT = 1 (scrittura)

      - PERCHE REINDIRIZZARE GLI STDIN E OUT:
        Nella creazione di una pipe, si sostituiscono gli STDIN e STDOUT con 
        le estremità della pipe per consentire la comunicazione tra due processi. 
        Questo è necessario perché una pipe fornisce un meccanismo per il 
        trasferimento di dati tra due processi correlati, e 
        l utilizzo di STDIN e STDOUT per leggere e scrivere dalla pipe consente 
        ai processi di comunicare tra loro in modo efficiente.
        
        Ecco perché avviene questa sostituzione:
        "Comunicazione tra processi:" 
        Quando si crea una pipe, si ottengono due file descriptor: 
        uno per l estremità di lettura (file descriptor di lettura) e uno per 
        l estremità di scrittura (file descriptor di scrittura) della pipe. 
        Questi file descriptor vengono utilizzati per leggere e scrivere dati 
        attraverso la pipe. Sostituendo STDIN con l estremità di lettura della 
        pipe e STDOUT con l estremità di scrittura della pipe, si consente ai 
        processi di leggere dati dalla pipe e scriverli su di essa in modo naturale 
        utilizzando le chiamate di sistema standard per la lettura e la scrittura 
        dei file.

        "Convenienza e compatibilità:" 
        Sostituendo STDIN e STDOUT con le estremità della pipe, 
        si mantiene la convenzione di utilizzare STDIN per l input e STDOUT per
        l output, il che rende più facile scrivere e leggere dati attraverso 
        la pipe utilizzando le chiamate di sistema standard come read() e write(). 
        Questo rende anche i programmi più facilmente interoperabili e 
        compatibili con altri programmi e utility che seguono la stessa convenzione.
        
        In sintesi, sostituire STDIN e STDOUT con le estremità della pipe consente 
        una comunicazione efficiente e convenzionale tra due processi utilizzando 
        le chiamate di sistema standard per la lettura e la scrittura dei file.

        - tutti gli errori vanno stampati nello stardard error



MAIN():
- Controlla che gli argc siano 5
- apre la pipe 
- esegue il fork
- nel processo figlio esegue child_process()
- nel padre aspetta e poi esegue parent_process()

child_process(argv, envp, fd/*array con i 2 fd della pipe*/):
- apro/creo il file argv[1] e assegno l fd che restituisce ad una variabile
  (Non devo prearlo perchè non avrebbe senso. Se il file di lettura non esiste 
   non avrà senso eseguire comandi su qualcosa che non esiste)
- Chiudo l'fd[0]' (di lettura dalla pipe) perchè questo processo scriverà su di essa
- Con dup2 faccio associo l'fd' associato al file aperto il nuovo STDIN 
  (fd standard di lettura)
- Con dup2 faccio associo l'fd[1]' (fd di scrittura nella pipe) allo STDOUT 
  (fd standard di scrittura).
  faccio diventare l estremità di scrittura della pipe lo standard output
  (così da poter scrivere automaticamente nella pipe)
- Chiamo ft_execute(envp, argv[2])


parent_process():
- stessa cosa del child process ma con fd invertiti
- Chiamo ft_execute(envp, argv[3])


FT_EXECUTE(char **envp, char *argv)
- estrae con split il comando dalla stringa argv passata (separata da ' ')
  NOTA: per "comando" intendiamo il comando e i parametri inviati. Es: ls -l
- chiama path_finder() che salva la stringa del path contenente il comando inviato
- if path non esiste faccio un ciclo per fare free sul doppio puntatore **comando\
- else mando execve con (path, comando, envp)

char *path_finder(char **envp, char *cmd)
- cerco la stringa "PATH" (con strnstr) attraverso un ciclo while su tutte le variabili
  d anbiente /*<--------------------------*/




"**********************************BONUS***************************************"

md << LIMITER | cmd1 >> file

- >> è una variante di >, ma anziché sovrascrivere il contenuto di un file, 
  aggiunge l output alla fine del file esistente 
  (o crea un nuovo file se non esiste).

  HERE_DOC
  Un here document è una caratteristica disponibile in molti linguaggi di shell, 
  come bash, che consente di fornire input multilinea direttamente 
  all interno di uno script shell o di un comando. 
  È particolarmente utile quando si desidera passare un blocco di testo 
  come input a un comando senza doverlo scrivere in un file separato.
  
  La sintassi di un here document è la seguente:
  COMMAND <<DELIMITER
    Texto
    multilinea
  DELIMITER
  Dove:

  COMMAND è il comando che riceverà il testo multilinea come input.
  DELIMITER è un delimitatore scelto dall utente. È solitamente una stringa 
            arbitraria che non appare nel testo fornito. 
            Questo delimitatore segna l inizio e la fine del blocco di testo 
            multilinea.

  Il testo multilinea tra <<DELIMITER e la successiva occorrenza di DELIMITER 
  sarà fornito come input al comando.
  Ad esempio, considera il seguente script bash:


  cat <<END
  Questo è un esempio
  di here document.
  Puoi scrivere testo multilinea
  senza dover usare citazioni o caratteri di escape.
  END
  In questo esempio, il comando cat riceverà il testo multilinea come input. 
  Il testo tra <<END e END sarà passato come input al comando cat e stampato 
  sullo stdout.

  L utilizzo di here document rende il codice più leggibile e evita la necessità 
  di creare file temporanei solo per passare del testo come input a un comando.

  NOTA: Si andra quindi a creare un here_doc temporaneo e se non esiste
        il comando << lo crea 