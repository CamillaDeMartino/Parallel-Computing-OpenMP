/**
     * In questo caso si sta lavorando su due vettori per eseguire un prodotto scalare
     * di conseguenza inizialmente andremo a moltiplicare ogni elemento del primo vettore
     * con il corrispettivo elemento del secondo vettore, quindi analogamente alla somma 
     * di due vettori ( II Nucleo computazionale ), di conseguenza anche esso
     * è un algoritmo full parallel e non c'è collezione dei dati;
     * successivamente, andiamo ad eseguire la somma degli elementi
     * risultanti dal prodotto, come nella somma di N numeri ( I Nucleo computazionale ),
     * che sappiamo non essere un algorimto full parallel, di coseguenza dobbiamo adottare
     * una strategia conveniente che ci permette di gestire questa situazione.
     * In questo caso utilizziamo la seconda strategia attraverso la clausola reduction.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <omp.h>

int main()
{
	int i, N;
	int sumtot = 0, *a, *b;
	double t1;
	double t2;
	
	printf( "Inserisci N: " );
	scanf( "%d", &N );
	
	
	// Allocazione dinamica
	a = ( int * )calloc( N, sizeof( int ) );
	b = ( int * )calloc( N, sizeof( int ) );
	
	// Inizializzazione vettore a, b
	for( i = 0; i < N; i++ )
	{
		//a[i] = rand() % 10 + 1;
		//b[i] = rand() % 10 + 1;
		a[i] = i+1;
		b[i] = i+1;
	}

	
	
	// Prendiamo il tempo di inizio
	t1 = omp_get_wtime();
	printf( "\nStampa t1: %f\n", t1 );
	
	/**
	* In questo costrutto  andiamo impostare le seguenti direttive al processore che sono
	*	- variabili private
	*	- variabili condivise
	*	- il tipo di scheduler 
	* Eseguiamo quindi il prodotto puntuale tra due vettori
	*/
	#pragma omp parallel for private(i) shared(a,b) schedule(static) reduction(+:sumtot)
	for ( i = 0; i < N; i++ )
	{
		sumtot += a[i] * b[i];
	}
	
	// Prendiamo il tempo di fine e stampiamo la durata dell'esecuzione
	t2 = omp_get_wtime();
	printf("Stampa t2: %f", t2);
	printf("\nTempo finale: %f\n", t2-t1);
	
	// Stampa Prodotto Scalare
	printf( "Somma Totale: %d\n", sumtot );

    //buona norma è liberare la memoria
    free(a);
    free(b);
    
	return 0;
}
