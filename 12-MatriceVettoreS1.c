#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <omp.h>

int main() {
    srand(time(NULL));
    int N, M;
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

    int *x = (int *) calloc(M, sizeof(int));
    for (int i = 0; i < M; ++i) {
        x[i] = rand() % 20;
    }

    // Stampa del vettore
    printf("\nVettoreIniziale:\n");
    for (int i = 0; i < M; i++) {
        printf("%d ", x[i]);
    }
    printf("\n");


    int *y;
	y = (int*) calloc(N,sizeof(int));
    
    int nloc = 0, step, r, tid, num_threads;

    //N.B per farlo si moltipilca ogni rica per gli elementi del vettore
    //poi si sommano gli elementi delle righe = somma dei N numeri del vettore
    //il risultato è un vettore
    #pragma omp parallel shared(matrix, x, y, N, M, num_threads) private(nloc, step, r, tid)
    {
        tid = omp_get_thread_num();
        num_threads = omp_get_num_threads();
        nloc = N / num_threads;
        r = N % num_threads;

        if (tid < r) {
            nloc++;
            step = 0;
        } else {
            step = r;
        }

        for (int i = 0; i < nloc; ++i) {
            int index = i + tid * nloc + step;

            for (int j = 0; j < M; ++j) {
                y[index] += matrix[index][j] * x[j];
            }
        }
    }

    printf("\nVettore y:\n");
    for (int i = 0; i < N; ++i) {
        printf("%d ", y[i]);
    }
    printf("\n");
    
    return 0;

}