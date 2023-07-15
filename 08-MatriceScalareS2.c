/* 
   La seconda è analoga basta invertire i for nel pragma
*/


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <omp.h>

int main() {
    int N, M, scalar;
    double t1,t2;
    
    printf("Inserisci il numero di righe: ");
    scanf("%d", &N);
    printf("Inserisci il numero di colonne: ");
    scanf("%d", &M);
    
    // Allocazione dinamica della matrice
    int **matrix = (int**) calloc(N, sizeof(int *));
    for (size_t i = 0; i < N; ++i) {
        matrix[i] = (int*) calloc(M, sizeof(int)); 
    }
  

    // Inizializzazione della matrice
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            matrix[i][j] = (i+1) * (j+1);
        }
    }

    // Stampa della matrice
    printf("\nMatrice Iniziale:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    printf("Inserisci scalare: ");
    scanf("%d", &scalar);

	//Tempo iniziale 
	t1 = omp_get_wtime();

	#pragma omp parallel for shared(N,M,matrix)schedule(guided)//num_threads(4)
		for(int j = 0; j < M; j++)
		{
			for(int i = 0; i < N; i++)
			{
			 	matrix[i][j] *= scalar;
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
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
    
    
    
    
    
    return 0;

}