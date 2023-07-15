/* 
   La Terza strategia prevede la suddivisione del lavoro per righe e colonne

   non funziona
*/


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <omp.h>

int main() {
    int numThreads = 4;
    int N, M, scalar;
    int Np = (N/(numThreads/2));
    int Mp = (M/(numThreads/2));
    double t1, t2;
    
    printf("Inserisci il numero di righe: ");
    scanf("%d", &N);
    printf("Inserisci il numero di colonne: ");
    scanf("%d", &M);
    
    // Allocazione dinamica della matrice
    int *matrix = (int*) calloc(N*M, sizeof(int *));

    // Inizializzazione della matrice
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            matrix[(i * N) + j] = (i+1) * (j+1);
        }
    }

    // Stampa della matrice
    printf("\nMatrice Iniziale:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            printf("%d ", matrix[(i * N) + j]);
        }
        printf("\n");
    }

    printf("Inserisci scalare: ");
    scanf("%d", &scalar);

	//Tempo iniziale 
	t1 = omp_get_wtime();

    // Funziona solo per 4 thread
	#pragma omp parallel num_threads(numThreads) shared(matrix)
    {
        int threadID = omp_get_thread_num();
        int rowStart = ( threadID / 2 ) * Np;
        int colStart = ( threadID % 2 ) * Mp;

        for (int i = rowStart; i < rowStart + Np; i++ ) {
            for (int j = colStart; j < colStart + Mp; j++ ) {
                matrix[ i * M + j ] = threadID;
            }
        }
    }
		
		
	//Tempo finale 
	t2 = omp_get_wtime();
	
	printf("\nTempo iniziale: %lf", t1);
	printf("\nTempo finale: %lf", t2);
    printf("\nTempo totale: %lf \n", t2-t1);

	// Stampa della matrice
    printf("\n\nMatrice Finale:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            printf("%d ", matrix[(i * N) + j]);
        }
        printf("\n");
    }
    
    
    
    
    
    return 0;

}