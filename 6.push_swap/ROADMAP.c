_________________________RULE___________________________________________________
 You have 2 stacks named a and b.
• At the beginning:
◦ The stack a contains a random amount of negative and/or positive numbers
which cannot be duplicated.
◦ The stack b is empty.
• The goal is to sort in ascending order numbers into stack a. To do so you have the
  following operations at your disposal:
sa (swap a): Swap the first 2 elements at the top of stack a.
             Do nothing if there is only one or no elements.

sb (swap b): Swap the first 2 elements at the top of stack b.
 			 Do nothing if there is only one or no elements.

ss : sa and sb at the same time.

pa (push a): Take the first element at the top of b and put it at the top of a.
			 Do nothing if b is empty.

pb (push b): Take the first element at the top of a and put it at the top of b.
			 Do nothing if a is empty.

ra (rotate a): Shift up all elements of stack a by 1.
			   The first element becomes the last one.

rb (rotate b): Shift up all elements of stack b by 1.
			   The first element becomes the last one.

rr : ra and rb at the same time.

rra (reverse rotate a): Shift down all elements of stack a by 1.
					    The last element becomes the first one.

rrb (reverse rotate b): Shift down all elements of stack b by 1.
						The last element becomes the first one.

rrr : rra and rrb at the same time.





________________________________________________________________________________
									TODO: 
________________________________________________________________________________

1) 	Gestione dell imput
1.1) Controllo sui valori inseriti
	 - solo numeri
	 - positivi o negativi
	 - NO alori duplicati

2) Inizializzare le stack (Allocazione, conversione in int, riempimento etc)

3) Controllare se i valori sono ordinati

4) Ordinamento se ho 2 valori

5) Ordinamento se ho 3 valori

6) Ordinamento per tutti

________________________________________________________________________________
									TEORIA: 
________________________________________________________________________________
- 2 stacks
- numeri positivi e negativi
- l algoritmo sistemera in ordine ascendente i numeri inseriti
- il programma dara in output la lista delle N operazione eseguite eseguite per 
   sortare X numeri:

   X = 3 -> N dovra essere <= 3
   X = 5 -> N dovra essere <= 12
   X = 100 -> N dovra essere < 1500
   X = 500 -> N dovra essere < 11500


MECCANICAL TURK_________________________________________________________________
- Questo algoritmo pusha gli elementi dallo stak a al b fino a che non rimangono 
  solo 3 elementi in a
- Ogni volta che un elemento viene pushato in b l algorirmo sortera questa stack
  in ordine decrescente




Supponiamo di avere la stack a con piu di 3 nodi. 
1) "Pusho i peimi due elementi nella stack b in modo ordinato DECRESCENTE."
   Avremo quindi un valore massimo e minimo temrporanei 
   (NOTA: Se a fosse composta da 4 elementi pusherei solo il primo elemento
          in quanto devo rimanere con 3 valori in a)

 A      B
99 
0    
25              
-38    
10
7
42

pusho ed ordino

A      B
25     0
-38    99
10
7
42

Avremo in stak b un minimo temporaneo (0) ed un massimo temporaneo (99) di cui dovrò tenere traccia


2) Cerco il mio target node: Ogni valore di a avra bisogno di un 
   							 "ELEMENTO TARGET" nella stack b.

							 Un "elemento target del valore x" 
							 (con x = elemento di a) sarà il più alto valore, della stack b, 
							 che risulti piu piccolo di x.
							 Cioè 'il più alto valore minore di x contenuto in b'
				
							 ES
							 A    B
							 5    4		-> Il target di 5 sarà 4
							 3	  2     -> Il target di 3 sarà 2 
							 6    99	-> Il target di 6 sarà 4 

ES:
In A ho come elemento in cima 25. Il nodo target in B sara 0 (l unico valore
minore di 25)

 A   		B  			TARGET IN B
25     		0 			->      0 
- 38   		99 			->      99 
10       				->      0 
7        				->      0 
742      				->      0 

NOTA: 'SE NON RIESCO A TROVARE UN NODO TARGET PER UN DATO VALORE DELLA STACK A
	   ANDRO AD ASSOCIARE A TALE NUMERO IL MASSIMO VALORE CONTENUTO NELLA STAC B'

	  -38 non ha un valore target, cioe minore di lui, quindi il suo target
      sara 99


NOTA: Il nodo target ci serve perchè vogliamo pushare gli elementi nella stack_b
	  in ordine decrescente. 
	  Sapere quale è il primo valore minore di ogni elemento della stack_a mi 
	  servirà per capire dove posizionarlo per avere, come detto, automaticamente
	  la stack b in ordine decrescente.
	  Cosi facendo infatti, ogni volta che pusherò un valore di a all interno di b
	  lo posizionerò 'SOPRA IL NUMERO CON IL VALORE IMMEDIATAMENTE PIU PICCOLO'

Ora ogni valore di a ha un suo nodo target



3) Da questo momento in poi, fino a che non avremo solo 3 elementi in a, 
   dopo ogni push dovremo calcolare quale nodo-a pushare in b. 
   In particolare dovremo trovare, per ogni push, il "nodo piu economico da pushare"

   
   *****************************************************
   "FORMULA PUSH COST":

     numero di operazioni per portare il nodo-a in cima
   							+
     numero di operazioni per portare il nodo-target del 
	 nodo a in cima 
							=
						 push cost
    *****************************************************
    
    
	
	Es: Vediamo un esempio, nella situazione corrente, di: 
	    - calcolo di costo per ogni nodo-a
		- esegO le operazioni 
		- pushO il piu economico

		 A   		B  		
		25     		0 			
		- 38   		99 			
		10       				
		7        				
		742      				

		nodo-a   target       push cost    motivo
		  25        0             0        - e gia in cima
		  						           - il suo noda target e gia in cima 
	
		NOTA: "SE IL PUSH COST DEL PRIMO NODA-A E' = 0 NON ANDRO A CALCOLARE 
	          IL VALORE PER GLI ALTRI PERCHE HA GIA IL VALORE MINIMO"


		NOTA: prima di pushare dovrei ordinare in modo descrescente la 
			  Ma quesa operazione non viene eseguita al primo giro 


		pusho:
		A      B 
		-38    25
		10		0
		7      99
		42



	  - 'ricalcolo i target' dato che lo stak b e stato modificato								  
		VALORE A     TARGET IN B
		- 38     ->      99 
		10       ->      0 
		7        ->      0 
		42      ->       25 

	  - 'Calcolo i push cost'	
	  	calcolo il costo per -38
		nodo-a   target      push cost    motivo
		  -38       99           1        - -38 e gia in cima -> costo = 0
		  						          - 99 richiede 1 mossa per portarlo
										    in cima (reverse rotate b)

	    Non e 0 quindi potrei avere un valore con un costo minore.
		calcolo quindi anche per 10, il nodo successivo.
		nodo-a   target      push cost    motivo
		  10       0           1          posso ruotare simultaneamente a e b 
		  								  per portare i due valore in alto 

		Stessa cosa-> calcolo per 7								  
		nodo-a   target      push cost    
		  7        0            3 
		Stessa cosa-> calcolo per 42								  
		nodo-a   target      push cost    
		  42        25           1   

	  - non ho trovato unvalore con push cost minore di -38 andrò quindi a pusharlo 
	  	sopra ad il suo nodo target.
		Il suo target è il 99 

		A      B 
		-38    25
		10	   0
		7      99
		42

	  - Dovrò quindi 'portare il nodo target in cima' per poter pushare sopra di lui 
		il noda-a appena trovato (uso rra)

		A      B 
		-38    99
		10	   25
		7      0
		42
		
	  - Pusho il - 38

	    A      B 
		10	   -38
		7      99
		42     25
				0	

		
	   - SONO RIMASTO CON 3 VALORI NELLO STACK A	


4) Implemento un "ALGORITMO PER ORDINARE 3 NODI IN ORDINE CRESCENTE"
   - Devo avere il numero massino sul fondo
   - fare sa() sui primi due elementi

5) Pusho uno alla volta gli elementi da B ad A assicurandoci che venga posizionato
   sopra l elemento corretto. 

   Ogni nodo B avrà un 
   "NODO TARGET IN A" = "VALORE MAGGIORE PIU VICINO ALL ELEMENTO B CHE ANDREMO A PUSHARE"

   NOTA: Se un elemento di B "NON HA UN NODO TARGET, QUESTO VERRA' ASSOCIATO AL MIN DI A"

   ES:
   A    B           TARGET 													  A      B
   7	-38   ->    Il target di -38 è 7									  -38    99
   10	99									-> 7 è già in cima ad A      ->   7      25
   42	25									   quindi faccio un semplice      10     0
		0									   push                           42



   A    B           TARGET 													  A      B
   -38	99   ->    Il target di 99 è -38									  99    25
   7	25									-> -38 è già in cima ad A      -> -38    0
   10	0									   quindi faccio un semplice       7     
   42										   push                           10	
																			  42


	A    B           TARGET 				
   99	25   ->    Il target di 25 è 42		
   -38	0									
   7										     
   10										   
   42
   Questa volta il valore target non è in cima. Potrei sia ruotare che 
   reverse ruotare stack A per far arrivare 42 in cima. 
   Cosa sceglo ?

   "CONSIDERO LA MEDIANA DI A"
   	A  				
   99	      -> Se il nodo target è "SOPRA LA MEDIANA" "ra() richiederà meno passaggi"
   -38        -> Se il nodo target è "SOTT LA MEDIANA" "rra() richiederà meno passaggi"
   ---------									
   7										     
   10										   
   42

   Eseguo un rra() e pusho
   	A   B
   25   0  	 -> Il target di 0 è 7. Trovandosi sotto la mediana eseguo rra()
   99		
   -38
   ----										
   7										     
   10										   
   42

   Ottenendo
   A   B
   0
   7  
   10		
   25
   ----										
   42										     
   99										   
   -38


5) "CONTROLLO DOVE SI TROVA IL MIN DELLA STACK A E LO PORTO IN CIMA"
   -> Se sopra la mediana -> ra()
   -> Se sotto la mediana -> rra()


