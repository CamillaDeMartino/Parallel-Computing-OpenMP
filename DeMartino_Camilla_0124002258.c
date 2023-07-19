/**
 * Startegia 1 per righe - matrice per vettore
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <omp.h>

int main() {
    srand(time(NULL));
    int **A, *b;     //matrice e vettore
    int N, M;
    int np;          // Unità processanti
    int max_element; // Numero massimo generabile all'interno della matrice
    double t0, t1, tot_time;
    
    printf("Inserisci il numero di righe: ");
    scanf("%d", &N);
    printf("Inserisci il numero di colonne: ");
    scanf("%d", &M);
    printf("Inserire il massimo numero generabile all'interno della matrice e del vettore: ");
	scanf("%d", &max_element);
	printf("Inserire il numero di unità processanti: ");
	scanf("%d", &np);
    
    omp_set_num_threads(np);

    
    //1 - Il core master deve generare una matrice A di dimensione NxM e un vettore b di dimensione M
    #pragma omp master
	{   
        //Allocazione dinamica della matrice
        A = (int**) calloc(N, sizeof(int *));

        for (int i = 0; i < N; ++i) {
            A[i] = (int*) calloc(M, sizeof(int)); 
        }

        // Inizializzazione della matrice
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                A[i][j] = rand() % max_element;;
            }
        }
        
        //Inizializzazione e allocazione del vettore b
        b = (int *) calloc(M, sizeof(int));
		for (int i = 0; i < M; i++) {
        	b[i] = rand() % max_element;
    	}
	}    
    

    // Stampa della matrice
    printf("\nMatrice Iniziale:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            printf("%d ", A[i][j]);
        }
        printf("\n");
    }


    // Stampa del vettore
    printf("\nVettore Iniziale b:\n");
    for (int i = 0; i < M; i++) {
        printf("%d ", b[i]);
    }
    printf("\n");

    //vettore risultato
    int *c = (int*) calloc(N,sizeof(int));
    
    int nloc = 0, step, r, tid, num_threads;
    t0 = omp_get_wtime();
    
    //I core collaborano per effettuare il prodotto matrice per vettore Axb=c
    //Per farlo si moltipilca ogni riga per gli elementi del vettore
    //poi si sommano gli elementi delle righe = somma dei N numeri del vettore
    //il risultato è un vettore
    #pragma omp parallel shared(A, c, b, N, M, np) private(nloc, step, r, tid)
    {
        tid = omp_get_thread_num();
        nloc = N / np;
        r = N % np;

        if (tid < r) {
            nloc++;
            step = 0;
        } else {
            step = r;
        }

        for (int i = 0; i < nloc; ++i) {
            int index = i + tid * nloc + step;

            for (int j = 0; j < M; ++j) {
                c[index] += A[index][j] * b[j];
            }
        }
    }

    printf("\nVettore c:\n");
    for (int i = 0; i < N; ++i) {
        printf("%d ", c[i]);
    }
    printf("\n");

    //i core collaborano per calcolare in parallelo il valore minimo del vettore c
    int min = c[0];
    #pragma omp parallel for shared(c) reduction(min: min) 
		for(int i = 1 ; i < N ; i++)
		{
			if(c[i] < min)
			{
				min = c[i];
			}
		}

    t1 = omp_get_wtime();
    tot_time = t1 - t0;
    printf("\nIl minimo è:");

    //Il core master stampa il tisultato finale e il tempo di esecuzione
    #pragma omp master
    {
        printf(" %d\n", min);
        printf("\nEXECUTION TIME: %f\n", tot_time);
    }

    //Buona norma è liberare la matrice
    for ( int i = 0; i < M; i++ )
        free( ( A )[i] );
    free( A );
    
    return 0;

}
