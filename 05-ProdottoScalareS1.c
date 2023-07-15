#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <omp.h>

int main()
{
	int i, N;
	int sumtot = 0, *a, *b, *c, sum;
	double t1;
	double t2;
	
	printf( "Inserisci N: " );
	scanf( "%d", &N );
	
	
	// Allocazione dinamica
	a = ( int * )calloc( N, sizeof( int ) );
	b = ( int * )calloc( N, sizeof( int ) );
	c = ( int * )calloc( N, sizeof( int ) );
	
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
	#pragma omp parallel for private(i) shared(a,b,c) schedule(static)	
	for ( i = 0; i < N; i++ )
	{
		c[i] = a[i] * b[i];
	}
	
	
	// Stampa di c
	for ( i = 0; i < N; i++ )
	{
		printf( " %d\n", c[i] );
	} 
	
	/**
	* In questo costrutto  andiamo impostare le seguenti direttive al processore che sono
	*	- variabili private
	*	- variabili condivise
	*	- il tipo di scheduler 
	* Dopo aver eseguito il prodotto puntuale andiamo a somma gli N elementi del vettore risultato ottenendo così uno scalare 
	*/
	sum = 0;
	#pragma omp parallel for private(i,sum) shared(sumtot) schedule(static)
	for( i = 0; i < N; i++ )
	{
		sum = c[i];

		#pragma omp atomic
		sumtot += sum;
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
	free(c);
	
	return 0;
}
