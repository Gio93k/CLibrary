#include "mylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern bookList list;
extern short ID;

															/*CREAZIONE NUOVO RECORD*/
															
int addBook(book *book_record) {
	char choice1;															
	short year, month, day;														
	int genre;																
	
	book_record->id=++ID;													//incremento ID (parte da 1)
	
	do{	
		printf("\nTitolo: ");												//inserimento TITOLO 				
		scanf(" %64[^\n]", book_record->title);								//esclude dalla scanf solo il carattere newline, permettendo spazi

		printf("\nAutore: ");												//inserimento AUTORE 
		scanf(" %32[^\n]", book_record->writer);							//vedi riga 20
		
		printf("\nData di pubblicazione\n");								//inserimento DATA
		printf("Anno: ");
		scanf(" %hd", &book_record->publication_date.year);
		year=book_record->publication_date.year;							//associa a year i dati immessi per facilitare la convalida
       		
		do {	
			printf("Mese: ");
			scanf(" %hd", &book_record->publication_date.month);			//associa a month i dati immessi per facilitare la convalida
			month=book_record->publication_date.month; } 
				while ((month <=0) || (month >12));							//convalida mese
	 
		do{  
			printf("Giorno: ");
			scanf(" %hd", &book_record->publication_date.day);
			day=book_record->publication_date.day; }						//associa a day i dati immessi per facilitare la convalida			
				while ((day<0) /*giorni negativi*/ || ((month==1 || month==3 || month==5 || month==7 || month==8 || month==10 || month==12) && day>31) /*eccesso giorni nei mesi di 31*/ || ((month==4 || month==6 || month==11) && day>30) /*eccesso giorni nei mesi di 30*/ || ((month==2) && (((year%4==0) && (year%100!=0)) || year%400==0) && (day>29)) /*febbraio nei bisestili*/ || (((month==2) && ((year%4!=0) && (year%400!=0)) && (day>28))));
								/*riga precedente: convalida giorno in base a durata mese e bisestilità*/
		 
		do {
			printf("\nCopie disponibili: ");								//inserimento n. COPIE DISPONIBILI
			scanf ("%hd", &book_record->in_library); } 
				while (book_record->in_library<0);							//convalida copie disponibili (non negative)
			
		do {
			printf("Copie in prestito: ");									//inserimento COPIE IN PRESTITO
			scanf ("%hd", &book_record->out_library); }
				while (book_record->out_library<0);							//convalida copie in prestito (non negative)
				
								
		printf("\nGeneri\n1. Narrativa \n2. Saggio \n3. Poesia \n4. Dizionario \n5. Manuale");
		do {
			printf("\nGenere selezionato: ");
			scanf(" %d",(int*)&book_record->genre);							//inserimento GENERE
			genre=book_record->genre;} while ((genre<0) || (genre>5));		//assegnamento dei dati immessi a genre e convalida (1-5)
	 	
														/*Verifica dati immessi*/
		printf("\n\n- Dati inseriti: -\n");
		printElement(book_record);											//stampa del nuovo record
	
		do {
			printf("\nI dati inseriti sono corretti?\nPremi 1 per confermare, 2 per sovrascrivere: ");
			scanf(" %c", &choice1); } while ((choice1!='1') && (choice1!='2')); } while(choice1=='2');
		if (choice1=='1') return 0; 
				
		return 0; }



															/*STAMPA DI UN ELEMENTO*/

void printElement(book *book_record) {
	printf(	   "Numero inventario: %d\n"										//stampa dei dati della cella, escluso il genere
			   "Titolo: %s\n"
               "Autore: %s\n"  
               "Data: %hd/%hd/%hd\n"
			   "Copie disponibili: %hd\n"
			   "Copie in prestito: %hd\n",
               book_record->id,
			   book_record->title,
               book_record->writer, 
               book_record->publication_date.day, 
               book_record->publication_date.month, 
			   book_record->publication_date.year, 
			   book_record->in_library,
			   book_record->out_library);
			   
			   int printGen=book_record->genre;									//a seconda del numero immesso, stampa il genre corrispondente
			   
			   if (printGen==1) printf("Genere: Narrativa\n");
			   else if (printGen==2) printf("Genere: Saggio\n");
			   else if (printGen==3) printf("Genere: Poesia\n");
			   else if (printGen==4) printf("Genere: Dizionario\n");
			   else if (printGen==5) printf("Genere: Manuale\n");
			   else printf("Genere non trovato\n");	}



																/*INSERIMENTO IN TESTA*/
															
void insHead(book *book_record) {												//l'argomento della funzione é il record appena immesso

	cell *temp=malloc(sizeof(cell));											//alloca lo spazio necessario per una cella
	temp->book_record=*book_record;												//colloca il record nello spazio ad esso dedicato della cella corrente
	
	if (list.p_first==NULL)	{													//caso "lista vuota"
		temp->p_nextcell=NULL;													
		list.p_first=temp;
		list.p_last=temp; }														//p_first e p_last coincidono e puntano alla cella corrente
		
	else { 																		//caso "lista piena" (almeno un elemento preesistente)
		temp->p_nextcell=list.p_first;   										//la cella successiva a quella corrente é quella puntata da p_first
		list.p_first=temp; }													//p_first deve puntare alla cella corrente
	}
	
	
	
																/*INSERIMENTO IN CODA*/  			  

void insTail(book *book_record) {												//l'argomento della funzione é il record appena immesso

	cell *temp=malloc(sizeof(cell));											//alloca lo spazio necessario per una cella
	temp->book_record=*book_record;												//colloca il record nello spazio ad esso dedicato della cella corrente	
		
	if (list.p_first==NULL)	{													//caso "lista vuota": si comporta come insHead
    temp->p_nextcell=NULL;	
	list.p_first=temp;
	list.p_last=temp; }
		
	else {																		//caso "lista piena"
		list.p_last=list.p_first;												//il puntatore all'ultimo elemento é inizializzato al primo
		while(list.p_last->p_nextcell!=NULL) {									//si "scorre" la lista
			list.p_last=list.p_last->p_nextcell; }								//incremento di p_last
		list.p_last->p_nextcell=temp;
		list.p_last=temp; }														//p_last punta alla cella corrente
	}

	
	
															/*STAMPA INTERA LISTA*/

void printList(cell *p_first) {
	
	if (list.p_first==NULL) printf("\nNessun elemento registrato.\n");			//controlla se la lista è vuota
	
	else {
		printf("\n\nGli elementi registrati sono:\n\n");								
		cell *temp=list.p_first;												//p_first é assegnato a una variabile temporanea									 
		while (temp!=NULL) {													//si deve "scorrere" la lista fino alla fine 							
		printElement(&temp->book_record);										//stampa un elemento per volta con printElement
	    printf("------------------------------------------\n");
	    temp=temp->p_nextcell; }												//incrementa la variabile temporanea
		 }
	}



														/*RIMOZIONE ELEMENTO IN TESTA*/
														
void rmvHead(/*cell *p_first*/) {
	list.p_first=list.p_first->p_nextcell; 									//aggiorna p_first
	free(list.p_first);	}													//svuota la prima cella

	
	
	
														/*RIMOZIONE ELEMENTO IN CODA*/
														
void rmvTail(cell *p_first) {
	cell *temp1, *temp2;													//dichiarazione di due puntatori a cella temporanei
	temp1=list.p_first;														//assegna ad uno il puntatore alla prima cella
	temp2=list.p_first->p_nextcell;											//all'altro, il puntatore alla cella successiva
	while (temp2->p_nextcell!=NULL) {										//scorre la lista finché il successivo del successivo non raggiunge la fine
		temp1=temp2;														//temp1 punta al penultimo elemento della lista
		temp2=temp1->p_nextcell; }											//temp2 punta all'ultimo elemento della lista
	free(temp1->p_nextcell);												//svuota l'ultima cella
	temp1->p_nextcell=NULL;													//termina la lista
	if (p_first==temp1) 
	{ p_first=NULL; }														//se p_first é ora l'ultimo elemento della lista, diventa NULL
	}
	
	

																/*RICERCA PER ID*/
																
cell* searchId(cell *p_first, short ID) {
	
	if (p_first!=NULL) {														
		while (p_first!=NULL) {											
			if (ID==p_first->book_record.id) {
				break; }													//esce dal ciclo nel momento in cui trova una corrispondenza
			else p_first=p_first->p_nextcell; }
								}
																			//restituisce un puntatore a NULL nel caso in cui non vi sia corrispondenza
	return p_first; 														//altrimenti, restituisce l'indirizzo della cella trovata
	}
	
	
	
														/*ORDINAMENTO PER ID CRESCENTE*/
														
cell *orderListId(cell *p_first) {											//bubble sort
	
	cell *curr;		
	book temp;												
	_Bool flag=1;														
	while (flag==1) {														//il ciclo continua solo se avviene uno scambio
		curr=p_first;
		flag=0;
		while (curr->p_nextcell!=NULL) {
			if (curr->book_record.id>(curr->p_nextcell)->book_record.id) {	//verifica se l'ID dell'elemento corrente é maggiore di quello del successivo
				temp=curr->book_record;										//assegna a temp il record contenuto nella cella corrente
				curr->book_record = (curr->p_nextcell)->book_record;		//scambia i due record
				(curr->p_nextcell)->book_record = temp;
				flag =1; }													//segnala che lo scambio é avvenuto e permette un ulteriore confronto
		curr = curr->p_nextcell; }											//incrementa curr
					}														

	return(p_first);
}

	
	
	
	
																/*STAMPA PER GENERE*/
																
void printGenre(cell *p_first) {   
	int gen;
	_Bool flag=0;
	do {
		printf("Inserisci genere da ricercare:\n1. Narrativa  2. Saggio  3. Poesia  4. Dizionario  5. Manuale\nGenere selezionato: ");
		scanf("%d",&gen); } while ((gen<1) || (gen>5));
	if (p_first!=NULL) {
		printf("\nGli elementi registrati sono:\n"); 
			while (p_first!=NULL) {
			if(gen==p_first->book_record.genre) {
				flag=1;															//segnala che é stata trovata una corrispondenza
				printElement(&p_first->book_record); 
				printf("------------------------------------------\n"); }
				p_first=p_first->p_nextcell; }									//incrementa p_first
					}															//chiude l'if più esterno
		if ((flag==0) && (list.p_first!=NULL)) printf ("\nNon ci sono libri di questo genere.\n");
		if (list.p_first==NULL) printf("\nNessun elemento registrato.\n");
		    
}
	
	
	
																	/*PRESTITO*/
																	
void copyOut(cell *p_first) {
	cell *temp;
	char choice;
	printf("\nInserisci l'ID del libro desiderato: ");
	short id;
	scanf("%hd", &id);
	temp=searchId(p_first, id);												//richiama searchId
	if(temp==NULL) printf("\nElemento non trovato.\n");
	else {
		printf("\n");
		printElement(&temp->book_record);									//se trova l'elemento, lo stampa
		printf("\nVuoi prendere questo libro? Sì: 1 No: 0\nScelta: ");
		while(1) {
			scanf(" %c",&choice);
			if(choice=='1') {
				if(temp->book_record.in_library>0) {  
					temp->book_record.out_library++; 						//incrementa le copie in prestito
					temp->book_record.in_library--; 						//decrementa le copie disponibili
					printf("Prestito registrato con successo.\n");
					}
					else printf("Non ci sono copie disponibili.\n"); 
			break; }
			else if (choice=='0') break;
			else printf("Immissione non valida.\n Reinserisci scelta:\n"); }//chiude il while(1)
		 }																	//chiude l'else (lista piena)
	}
	
	
	
																/*RESTITUZIONE*/
																		
void copyIn(cell *p_first) {
	cell *temp;
	char choice;
	printf("\nInserisci ID del libro da restituire: ");
	short id;
	scanf("%hd",&id);
	temp=searchId(p_first,id);
	if(temp==NULL) printf("Elemento non trovato.\n");
	else {
		printf("\n");
		printElement(&temp->book_record);									//se trova l'elemento, lo stampa				
		printf("\nVuoi restituire questo libro? Sì: 1 No: 0\nScelta: ");
		while(1) {
		scanf(" %c",&choice);
		 if(choice=='1') {
			if(temp->book_record.out_library>0) {  
				temp->book_record.out_library--; 
				temp->book_record.in_library++; 
				printf("Restituzione effettuata."); }
			else { 
				printf("Nessuna copia risulta in prestito.\n"); } 
				break; }
			else if (choice=='0') break;
			else printf("Immissione non valida.\n Reinserisci scelta:\n"); }//chiude il while(1)
		 }																	//chiude l'else (lista piena)	
	}
	
	
	
												/*COMPARAZIONE STRINGHE (ORDINE ALFABETICO)*/
												
static int alphabetCompare(char *string1 , char *string2) {
		int c1, c2, i;														//dichiara un contatore i e i due caratteri da comparare 
		for(i=0; i<64; i++) {                 							   	//scorre l'intera stringa
			if(string1[i]<= 'Z' && string1[i] >= 'A') 						//se il catattere é maiuscolo, il suo valore intero viene decrementato di 54
				c1=string1[i] - 54;	 
			else if(string1[i]<= 'z' && string1[i] >= 'a')					//se é minuscolo, viene decrementato di 86
				c1=string1[i] - 86;										
			else if(string1[i]<= '9' && string1[i] >= '0')					//se é una cifra, viene decrementata di 47
				c1=string1[i] - 47;	
			else c1=0;														//tutti gli altri catatteri sono euguagliati a 0
			
			if(string2[i]<= 'Z' && string2[i] >= 'A') 
			c2=string2[i] - 54;             			            		//la stessa cosa vale per il carattere della seconda stringa in esame
			else if(string2[i]<= 'z' && string2[i] >= 'a')							
			c2=string2[i] - 86;													
			else if(string2[i]<= '9' && string2[i] >= '0')	
			c2=string2[i] - 47;									
			else c2=0;
			
			/*solo dopo aver assegnato il medesimo valore a minuscole e minuscole avviene il confronto tra i due caratteri*/
			
			if(c1>c2) return 1;												//restituisce 1 se il carattere della prima stringa viene dopo l'altro										
			else if(c2>c1) return 2;
			}																//chiude il for
	return 0;                                      		   	
	}															 
	
	
	
															/*ORDINAMENTO PER TITOLO*/
	
void orderListAlphabet(cell *p_first) {
	cell *last= NULL, *current=p_first;
	book temp;
	while(current!=last) {
		while(current->p_nextcell!= last){									//riga seguente: confronto stringhe titolo
			if(alphabetCompare(current->book_record.title, current->p_nextcell->book_record.title)==1) {
				temp=current->book_record;
				current->book_record=current->p_nextcell->book_record;
				current->p_nextcell->book_record= temp;	}					//se necessario, i record vengono scambiati 
		current=current->p_nextcell; }										//incrementa la cella corrente
	last=current;
	current=p_first; }
	}



																/*RIMOZIONE PER ID*/
																
_Bool rmvId (cell *p_first) {
	
	short ID;
	printf("\nInserisci l'ID da rimuovere: ");
	scanf("%hd", &ID);
	cell *temp=searchId(p_first, ID);										//invocazione di searchId
	if (temp==NULL) return 1;												//restituisce 1 se l'elemento non viene trovato
	else {
		if (temp==list.p_first) {											//se l'elemento trovato é il primo, lo rimuove con l'apposita funzione
			rmvHead(list.p_first);
			return 0; }
		
		else if (temp==list.p_last) {										//idem se l'elemento trovato é l'ultimo
			rmvTail(list.p_last);
			return 0; }
			
		else {
			cell *prev=list.p_first;										//salva come prev il primo elemento (già controllato)
			cell *curr=list.p_first->p_nextcell;							//considera il successivo l'elemento corrente
			while (1) {
				if (temp==curr) {
				prev->p_nextcell=curr->p_nextcell;							//quando trova la corrispondenza, aggiorna i puntatori del precedente
				free(curr); 												//solo dopo, elimina l'elemento corrente
				return 0; }												
				prev=prev->p_nextcell;										//incrementa entrambi i puntatori temporanei
				curr=curr->p_nextcell; }
			}
		}
}


																
															/*AZZERAMENTO DELLA LISTA*/

void resetList(cell *p_first) {
	if (list.p_first!=NULL) {												//svuota la lista soltanto se ci sono elementi registrati
		while (list.p_first!=NULL) {
		rmvHead(list.p_first);
		ID=0; }																//resetta l'ID in modo che riparta da 0
	}																		//chiude l'if
}



																/*CONTEGGIO ELEMENTI*/
															
static int cellCount(cell *p_first) {
	int n=0;
	if (list.p_first==NULL) {												//controlla se la lista é vuota
		n=0;}
	else {
		while (p_first!=NULL) {
			++n;
			p_first=p_first->p_nextcell; }
		 }
	return n;																//restituisce il numero di celle, pari a quello dei record
	}

																/*SALVATAGGIO DATI*/
																
void saveList(cell *p_first) {
	FILE *p_file;
	p_file=fopen("dati_salvati.bin", "wb"); 								//apre un file binario; se non esiste, lo crea
	int n;
	n=cellCount(list.p_first);												//conta gli elementi della lista
	fwrite(&n, sizeof(int), 1, p_file);										//memorizza il numero di elementi
	fwrite(&ID, sizeof(short), 1, p_file);									//memorizza l'ultimo ID inserito (=l'attuale valore della variabile ID)
	while (n--) {															//effettua il salvataggio di un elemento per n volte
		fwrite(&p_first->book_record, sizeof(book), 1, p_file); 			//salva il primo record
		p_first=p_first->p_nextcell; }										//incrementa p_first scorrendo la lista
	fclose(p_file);															
	}
	
	
															/*CARICAMENTO DATI SALVATI*/
															
void loadData() {
	FILE *p_file;
	book temp;
	p_file=fopen("dati_salvati.bin", "ab+");								//apre il file binario preesistente (solo se richiesto durante l'esecuzione)
	rewind(p_file);
	int n;
	fread(&n, sizeof(int), 1, p_file);										//legge il numero di elementi salvati
	fread(&ID, sizeof(short), 1, p_file);									//legge l'ID in modo che un eventuale nuovo record abbia il valore successivo
	while (n--) {															//effettua il caricamento di un record per n volte
		fread(&temp, sizeof(book), 1, p_file);								//legge i dati di un record
		insTail (&temp);													//inserisce il record in coda per mantenere il giusto ordine
		}
	fclose(p_file);
	}
	
															
															
													/*ABIURA (=eliminazione libri di un dato autore)*/
																
void rmvAuthor(cell *p_first) {
	char userString[SIZEw];
	int n0=cellCount(list.p_first);													//conta le celle
	printf("Inserisci il nome completo dell'imputato: ");
	scanf(" %32[^\n]", userString);													//vedi riga 20
	if (strcmp(userString, p_first->book_record.writer)==0) {						//controlla se è uguale all'autore del book_record della prima cella			
		do {																		//esce dal ciclo nel caso in cui le stringhe siano diverse
			rmvHead(list.p_first); }												//finché sono uguali, richiama rmvHead
				while (strcmp(userString, p_first->book_record.writer)!=0); }	   
	cell *prev=p_first;																//memorizza il primo elemento (già confrontato) come prev 
	cell *curr=p_first->p_nextcell;													//memorizza il secondo elemento come curr 
	while (curr!=NULL) {															//scorre la lista fino alla fine
		if (strcmp(userString, curr->book_record.writer)==0) {						//compara l'autore dell'elemento corrente con la stringa immessa
			prev->p_nextcell=curr->p_nextcell;										//se sono uguali, elimina temp e aggiorna i puntatori		
			free(curr);																
			curr=prev->p_nextcell; }
		else {																		//se sono diversi, incrementa sia prev che curr
			prev=curr;
			curr=curr->p_nextcell; }
						}															//chiude l'if
	int n1=cellCount(list.p_first);													//riconta le celle dopo l'abiura
	if (n1!=n0) printf("\n%s ha abiurato.\n", userString);							//il messaggio é stampato solo se il numero delle celle é mutato
	else printf("\n%s ci é sfuggito, maledizione! Sarà messo al rogo non appena lo acciuffiamo!\n", userString);
	}



