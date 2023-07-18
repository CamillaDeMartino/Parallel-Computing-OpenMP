/**
 * PROVA SCRITTA LABORATORIO TRACCIA 1: 29-06-2023
 * 
 * Implementare un programma parallelo per l'ambiente multicore 
 * con np unità processanti che impieghi la libreria OpenMP.
 * 
 * Il programma deve essere organizzato come segue:
 * 
 * 1. Ogni core deve generare una matrice A di dimensione N/np x M,
 *    mentre solo il core master deve leggere un vettore b di lunghezza M
 * 
 * 2. Tutti i core devono calcolare localmente il prodotto c = A x b
 * 
 * 3. Quindi, i core devono organizzarsi per determinare il massimo
 *    valore tra tutti gli elementi dei vettori locali c e il massimo 
 *    globale tra tutti i vettori locali c
 * 
 * 4. Infine, il core master deve stampare il valore massimo
 *    globale trovato ed il tempo d'esecuzione.
*/

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>


int main() {
	srand(time(NULL));

	double t0, t1, tot_time; // Tempo di inizio e fine del programma

	int ** A, **c; // Matrice A
	int *b, *max;
	int N, M; // N = righe, M = colonne
	int max_element; // Numero massimo generabile all'interno della matrice
	int np; // Unità processanti

	printf("Inserisci il numero di righe: ");
	scanf("%d", &N);
	printf("Inserisci il numero di colonne: " );
	scanf("%d", &M);
	printf("Inserire il massimo numero generabile all'interno della matrice e dei vettori: ");
	scanf("%d", &max_element);
	printf("Inserire il numero di unità processanti: ");
	scanf("%d", &np);

	omp_set_num_threads(np);

	max = (int *) calloc(np, sizeof(int));
	for (int i = 0; i < np; i++) {
        	max[i] = rand() % max_element;
    }

	b = (int *) calloc(M, sizeof(int));
	
	c = (int**) calloc(np,sizeof(int*));
	for(int i = 0; i < np; i++)
	{
		c[i] = (int*) calloc(N/np,sizeof(int));
	}

    //1-2

	#pragma omp master
	{
		for (int i = 0; i < M; i++) {
        	b[i] = rand() % max_element;
    	}
	}

	printf("\nVettore :\n");
    for (int i = 0; i < M; ++i) {
        printf("%d ", b[i]);
    }
    printf("\n");

	t0 = omp_get_wtime();

	#pragma omp parallel private(A)shared(b, N, M)//num_threads(np)
	{
		A = (int**) calloc(N/np,sizeof(int*));

		for (int i = 0; i < N/np; i++) {
			A[i] = (int*) calloc(M,sizeof(int));
			for (int j = 0; j < M; j++) {
				A[i][j] = rand() % max_element;
			}
    	}

		int tid = omp_get_thread_num();

		for(int i = 0; i < (N/np); i++){
			for(int j = 0; j < M; j++){

				c[tid][i] += A[i][j]*b[j];
			}
		}

		if(tid != -1)
       		 printf("Thread: %d\n", tid);
    	else
        	printf("Thread\n");

		for(int i=0; i<N/np; i++){
        	for(int j=0; j<M; j++)
          	  printf("%d ", A[i][j]);
        	
			puts("");
    	}
    	puts("");

	}


	#pragma omp parallel shared(c, M)
    {
        int tid = omp_get_thread_num();
        max[tid] = c[tid][0];
        for(int j=0; j<M; j++)
            if(max[tid] < c[tid][j])
                max[tid] = c[tid][j];
    }

	
	max_element = max[0];
    
    #pragma omp parallel for reduction(max:max_element)
    for(int i=1; i<np; i++)
        if(max_element < max[i])
            max_element = max[i];

   
	t1 = omp_get_wtime();
	tot_time = t1 - t0; 

	printf("\nC: \n");
	for(int i=0; i<np; i++){
        for(int j=0; j<N/np; j++)
            printf("%d ", c[i][j]);
        puts("");
    }
    puts("");

	printf("\nlocal Max: \n");
	for(int i=0; i<np; i++)
        printf("%d ", max[i]);
    puts("");

	printf("\nGlobal Max: %d\n", max_element);
	printf("\nEXECUTION TIME: %f\n", tot_time);


    return 0;

}