/**
 * Odd-Even Sort è un algoritmo di ordinamento basato su Bubble Sort
 * Funziona confrontando tutte le coppie indicizzate pari/dispari di elementi adiacenti nell'elenco e,
 * se una coppia è nell'ordine sbagliato (la prima è più grande della seconda) gli elementi vengono invertiti.
 * Il passaggio successivo lo ripete per le coppie indicizzate pari/dispari (di elementi adiacenti).
 * Quindi si alterna tra i passaggi pari/dispari e pari/dispari fino a quando l'elenco non viene ordinato.
 * Di solito l'algoritmo parallelo non viene utilizzato per confrontare le operazioni, 
 * ma questo è per un esercizio accademico
*/

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define SIZE 10
#define MAXVALUE 100

void printVector( int*, int, char[] );
void oddEvenSort( int*, int);
int main() {
    
    int* vector;
    vector = ( int* ) malloc( SIZE * sizeof( int ) );
    srand( time( NULL ) );
    
    for ( int i = 0; i < SIZE; i++ )
        vector[i] = rand() % MAXVALUE + 1;
    
    printVector( vector, SIZE, "Vector before the sorting" );
    oddEvenSort( vector, SIZE );
    printVector( vector, SIZE, "Vector after the sorting" );
    
    printf( "\n" );
    return 0;
}

void printVector( int* vector, int N, char name[] ) {
    printf( "\n%s: ", name );
    for ( int i = 0; i < SIZE; i++ )
        printf( "%d ", vector[i] );
}

void oddEvenSort( int* a, int N ) {

    int sw = 1, start = 0, i = 0;
    int temp;
    while( sw || start ) {
        sw = 0;
        
        #pragma omp parallel for private( temp ) 
        for ( i = start ; i < N - 1 ; i += 2) {
            if ( a[i] > a[ i + 1 ] ) {
                temp = a[i] ;
                a[i] = a[ i + 1 ];
                a[ i + 1 ] = temp ;
                sw = 1 ;
            }
        }

        if ( start == 0 ) 
            start = 1 ;
        else 
            start = 0;
    }
}