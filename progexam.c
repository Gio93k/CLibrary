#include "mylib.h"

bookList list;	
short ID=0;																//inizializzazione del numero d'inventario a 0

int main() {
	
	char first_access;
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
	do {
		printf("Stai per accedere a G.N.U Library Database. \n ");
		printf("Se hai già usato questo programma e vuoi caricare i dati salvati, premi 1.\nAltrimenti, premi 0: ");
		scanf(" %c", &first_access); 
		fflush(stdin); } while ((first_access!='1') && (first_access!='0'));
	if (first_access=='1') loadData();									//carica i dati salvati
	else if (first_access=='0') resetList(list.p_first); 				//azzera la lista nel caso in cui vi siano elementi indesiderati in memoria
	book book_record;
	cell *temp;
	char func_choice;
	_Bool on=1;															//indica lo stato del programma
	printf("\n\n\n" 
           "                         _ _ _ _ _ _ _ _ _ _\n"             
           "                        |         |         |\n"             
           "                        |  G.N.U. |  ---    |\n"              
           "                        |  ----   |  -----  |\n"                
           "                        |  -----  |  ----   |\n"                 
           "                        |  -----  |  -----  |\n"                 
           "                        |_ _ _ _ _|_ _ _ _ _|\n"                 
           "                                 | |   |_\n"                     
           "                              _ _| |_ _  \\______\n"               
           "                     _ _ _ _ _ _ _ _ _ _ _ _ _  \\__\n"          
           "                    |-_-_-_-_-_-_-_-_-_-_-_-_-| /__\\\n\n"               
           "                  ____________________________________\n\n"
           "                             _   _   _   _\n"   
           "                       |  | |_) |_) |_| |_) |_|\n"             
           "                       |_ | |_) | \\ | | | \\  /\n"               
           "                     _   _  _ _  _   _   _   _   _\n"          
           "                    | \\ |_|  |  |_| |_) |_| |_  |_\n"        
           "                    |_/ | |  |  | | |_) | |  _| |_\n\n");  
	printf("             Inserisci le tue iniziali per cominciare: ");
	char user[5];
	scanf("%s", user);
	while (on){
			printf("\n\n- Seleziona una delle seguenti opzioni: -\n\n"
							" 1. Inserimento nuovo elemento\n"
							" 2. Ordinamento lista\n"
							" 3. Ricerca elemento attraverso id\n"
							" 4. Gestione prestiti\n"
							" 5. Stampa lista\n"
							" 6. Rimozione singolo elemento\n"
							" 7. **BONUS FEATURE** - abiura!\n"
							" 8. Reset lista\n"
							" 0. Chiudi programma\n");
	printf("\nOpzione selezionata: ");	
	scanf(" %c", &func_choice);
		
	switch (func_choice) {
			
		case '0': {
			printf("\n- Chiusura programma -\n\nVuoi salvare la lista? 1: Salva 0: Chiudi senza salvare");
			char choice;
			do { 
				printf("\nScelta: ");
				scanf(" %c", &choice); } while ((choice!='0') && (choice!='1')); 
			if (choice=='0') { 											//esce dal programma
				printf("\nArrivederci %s!\n\n\n", user);
				on=0; }												
			else if (choice=='1') {										//salva ed esce
				saveList(list.p_first);
				printf("\nLista salvata. Arrivederci %s!\n\n\n", user);
				on=0; } 												
				break; }
				
				
		case '1': {
			char choice, choice2; 
			//char menu;
			do {
				printf("\n- Inserimento nuovo elemento -\n\n");
				
				
				/*printf("In caso avessi sbagliato a digitare, per tornare al menù principale, premi 1\n");
				printf("Scelta: ");
				
					 scanf(" %c", &menu);
					if(menu!='1') printf("\n- Inserimento nuovo elemento -\n\n");
					   else {break;}
					*Ovviamente ho provato ad auto buggarmi il controllo, e se metto le lettere, mi va direttamente all'autore
					 * scegliere a sto punto se migliorarla o se omettere questo controllo, anche se a mio parere risulterebbe utile
					 * se usato con intelligenza! */
				
				
				
				while (1) { 
					if (addBook(&book_record));							//se l'inserimento ha effetto, esce dal while
					break; }
				if (list.p_first!=NULL) {								//fa scegliere dove collocare il record solo a partire dal secondo elemento
					do { 
						printf("\nInserire l'elemento in testa o in coda? 1: Testa 2: Coda\nScelta: ");
						scanf(" %c", &choice); } while ((choice!='1') && (choice!='2'));
						if (choice=='1') insHead(&book_record);
						else insTail(&book_record); }
				else insHead(&book_record);								//se si sta inserendo il primo elemento, viene posto arbitrariamente in testa
				do {
					printf("\nVuoi inserire un altro libro? Sì: 1 No: 0\nScelta: ");		
				    scanf(" %c", &choice2); } while ((choice2!='0') && (choice2!='1')); 
					} while (choice2=='1');								//chiude il do/while più esterno
				if (choice2=='0') on=1;									//torna al menu principale
				break; } 
			
				
					
		case '2': {
			char choice;
			printf("\n- Ordinamento lista -\n");
			if ((list.p_first!=NULL) && (list.p_first->p_nextcell!=NULL)) {
				do {													//é possibile ordinare la lista solo a partire da 2 elementi registrati
					printf("\n1. Ordinamento in base a ID crescente\n2. Ordinamento lessicografico\n\nScelta: ");
					scanf(" %c", &choice); } while ((choice!='1') && (choice!='2'));
				if (choice=='1') {
					orderListId(list.p_first);
					printList(list.p_first);							//stampa il risultato dell'ordinamento
					printf("\nDigita un carattere qualsiasi per tornare al menu principale: ");
					char menu;
					scanf(" %c", &menu);
					break; }
				else {
					orderListAlphabet(list.p_first); 
					printList(list.p_first); 							//stampa il risultato dell'ordinamento
					printf("\nDigita un carattere qualsiasi per tornare al menu principale: ");
					char menu;
					scanf(" %c", &menu);
					break; } 
									}									//chiude l'if più esterno
								
			else printf("\nNon ci sono elementi sufficienti per un ordinamento.\n");	
			printf("\nDigita un carattere qualsiasi per tornare al menu principale: ");
					char menu;
					scanf(" %c", &menu);
			break; }		
				
				
		case '3': {
			char choice;
			printf("\n-Ricerca elemento attraverso ID-\n\n");
			printf("Inserisci l'ID: ");
			short userID;
			scanf("%hd", &userID);										//prende da tastiera l'ID da ricercare
			temp=searchId(list.p_first, userID);						//associa a un puntatore temporaneo l'esito della ricerca				
			if (temp==NULL) printf("\nElemento non trovato.");
			else {
				printf("\nElemento presente."); 
				do {
					printf("\nVuoi stampare l'elemento trovato? 1: Sì  0: No\nScelta: ");
					scanf(" %c", &choice); } while ((choice!='0' && choice!='1'));
					if(choice=='1') {
						printf("\n");
						printElement(&temp->book_record); }
					else break; }										//chiude l'else
			printf("\nDigita un carattere qualsiasi per tornare al menu principale: ");
					char menu;
					scanf(" %c", &menu);
				break; }
				   
				   
		case '4': {
			char choice;
			printf("\n- Gestione prestiti -\n");
			do {
				printf("\n1. Prendi in prestito un libro \n2. Restituisci un libro\nScelta: ");
				scanf(" %c", &choice);} while ((choice!='1') && (choice!='2'));
			if (choice=='1') copyOut(list.p_first);
			else copyIn(list.p_first);
			printf("\nDigita un carattere qualsiasi per tornare al menu principale: ");
					char menu;
					scanf(" %c", &menu);
			break; }
	    
		case '5': {
			char choice;
			printf("\n- Stampa lista -\n");
			do {
				printf("\n1. Stampa intera lista 2. Stampa in base al genere\nScelta: ");
				scanf(" %c", &choice); } while ((choice!='1') && (choice!='2'));
			if (choice=='1') printList(list.p_first);
			else printGenre(list.p_first);
			printf("\nDigita un carattere qualsiasi per tornare al menu principale: ");
					char menu;
					scanf(" %c", &menu);
			break; }
				
			
						
		case '6': {
			char choice, choice2;
			printf("\n-Rimozione singolo elemento-\n\n");
			do { 
				do {
					printf("Quale elemento vuoi rimuovere?\n"
						   "1: Elemento in testa  2: Elemento in coda  3: Rimozione per id\nScelta: ");
					scanf(" %c", &choice); } while ((choice!='1') && (choice!='2') && (choice!='3'));
					if (choice=='1') {
						if (list.p_first!=NULL) {						//richiama rmvHead solo se la lista non é vuota
							rmvHead(/*list.p_first*/);
							printf("Primo elemento eliminato.\n"); }
						else printf("Nessun elemento da eliminare.\n"); }
					else if (choice=='2') {
							if (list.p_first!=NULL) {					//richiama rmvTail solo se la lista non é vuota
								rmvTail(list.p_first);
								printf("Ultimo elemento eliminato.\n"); }
							else printf("Nessun elemento da eliminare.\n"); }
					else {
							if (list.p_first!=NULL) {					//richiama rmvId solo se la lista non é vuota
							_Bool n=rmvId(list.p_first); 
							if (n==0) printf("Elemento eliminato.\n"); 
							else if (n==1) printf("Elemento non trovato"); } 
						else printf("Nessun elemento da eliminare.\n"); }
						
					do {
						printf("\nVuoi rimuovere un altro elemento? 1: Sì  0: No\nScelta: ");
						scanf(" %c", &choice2); } while ((choice2!='0') && (choice2!='1')); }
							while (choice2=='1'); 						//chiude il do/while più esterno
					if (choice2=='0') break; 
				break; } 
					
		case '7': {
			char choice;
			while (1) {
				printf("- NOVITÀ: Fai abiurare il tuo autore preferito e sentiti come il tribunale della Sacra Rota! -\n");
				rmvAuthor(list.p_first);
				do {
					printf("Conosci altri eretici? Si: 1 No: 0\nScelta: ");	
					scanf(" %c", &choice); } while ((choice!='1') && (choice!='0'));
					if (choice=='0') break;
					 }		
			printf("\nDigita un carattere qualsiasi per tornare al menu principale: ");
					char menu;
					scanf(" %c", &menu);
			break; }
								
		case '8': {
			char choice;
			printf("\n- Reset lista -\n");
			do {
				printf("\nTutti i dati inseriti saranno cancellati.\nPremi 1 per procedere, 2 per annullare: ");
				scanf(" %c", &choice); } while ((choice!='1') && (choice!='2')); 
			if (choice=='1') {
				resetList(list.p_first);
				printf("\nLista cancellata."); }
			printf("\nDigita un carattere qualsiasi per tornare al menu principale: ");
					char menu;
					scanf(" %c", &menu);
			break; }
				
		default: break;
			
			break; }													//chiude lo switch
			}															//chiude il while	
							
	return 0; }															//chiude il main
