#include <stdio.h>
#include <stdlib.h>
#define SIZEt 64														//definizione della dimensione max per la stringa contenente il titolo
#define SIZEw 32														//definizione della dimensione max per la stringa contenente l'autore

enum genres {FICTION=1, ESSAY, POETRY, DICTIONARY, HANDBOOK};			//enum GENRES

typedef struct {														/*definizione del tipo DATE*/
	short day; 
	short month; 
	short year;
} date;

typedef struct {														/*definizione del tipo BOOK*/
    char title[SIZEt];
    char writer[SIZEw];
    date publication_date;												//impiego del tipo DATE
    enum genres genre;													//impiego dell'enum
    short in_library; 											
    short out_library;
    short id;
	} book;

typedef struct cell{													/*definizione del tipo CELL*/
    book book_record;													
    struct cell *p_nextcell; 											//puntatore alla cella successiva->lista concatenata semplice
    } cell;
    
typedef struct {														/*definizione del tipo BOOKLIST*/
    cell *p_first;														//puntatore all prima cella della lista
    cell *p_last;														//puntatore all'ultima cella della lista	
    } bookList;
    

															/*FUNZIONI ACCESSIBILI DAL MAIN*/
															
/*Funzioni richieste nel testo dell'esame*/

void insHead(book *book_record);										//inserimento in testa (case 1)
void insTail(book *book_record);										//inserimento in coda (case 1)
void printList(cell *p_first);											//stampa intera lista (case 2, case 5)
void copyOut(cell *p_first);											//prestito (case 4)
void copyIn(cell *p_first);												//restituzione (case 4)
cell *searchId(cell *p_first, short ID);								//ricerca per ID (case 3)
void rmvHead(/*cell *p_first*/);										//rimozione elemento in testa (case 6)
void rmvTail(cell *p_first);											//rimozione elemento in coda (case 6)
_Bool rmvId(cell *p_first);												//rimozione secondo ID passato dall'utente (case 6)

cell *orderListId(cell *p_first);										//ordinamento per id (ordine d'immissione) (case 2)
void orderListAlphabet(cell *p_first);									//ordinamento lessicografico (titolo) (case 3)
void printGenre(cell *p_first);											//stampa per genere (case 5)
void rmvAuthor(cell *p_first);											//rimozione per autore (rielaborazione rmvCharTitle) (case 7)

/*Funzioni aggiuntive e/o implicitamente necessarie*/

void printElement(book *book_record);									//stampa elemento (case 3)
int addBook(book *book_record);											//aggiunta nuovo record (case 1)
void resetList(cell *p_first);											//azzeramento lista (case 8)
void saveList(cell *p_first);											//salvataggio dati (case 0)
void loadData();														//caricamento dati (esterno allo switch)
