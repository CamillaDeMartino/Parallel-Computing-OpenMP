/**
	Assegmata una matrice NxN, estrarre in parallelo gli elementi della diagonale principale e ricopiarli in un vettore, 
	quindi calcolarne il massimo con una procedura parallela.

	N diagonali righe
	- copiare gli elementi della diagonale in un vettore
	- 
*/

#include <stdio.h> 
#include <omp.h>
#include <stdlib.h>

#define N 100
int main()
{
	int** matrix;
	int *diag;
	int max;
	int maxr;
	double t0, t1, totReduction;
	
	matrix = (int **) calloc(N, sizeof(int*));
	diag = (int * )calloc(N, sizeof(int));
	
	for(int i = 0; i < N; i++)
	{
		matrix[i] = (int *) calloc(N, sizeof(int));
	}

	
	for(int i = 0; i < N; i++)
	{
		for(int j = 0; j < N; j++)
		{
			matrix[i][j] = i+j;
		}
	}
	
	t0 = omp_get_wtime();
	#pragma parallel for shared(N, matrix, diag)
	for(int i = 0; i < N; i++)
	{
		diag[i] = matrix[i][i];
	}


	for(int i = 0; i < N; i++)
	{
		for(int j = 0; j < N; j++)
		{
			printf(" %d", matrix[i][j]);
		}
		printf("\n");
	}
	
	printf("\nDiagonale\n");
	for(int i = 0; i < N; i++)
	{
		
		printf(" %d", diag[i]);	
		
	}
	
	printf("\n");
	
	/** Il costrutto critical usalo solo quando non sai che fare
			 
	max = diag[0];
	#pragma parallel for shared(diag) private(max) num_threads(2)
	for(int i = 1; i < N; i++)
	{
		#pragma omp critical
		if(diag[i] > max)
			max = diag[i];
	}
	
	printf("\n Massimo: %d", max);
	printf("\n");
	*/

	
	maxr = diag[0];
	#pragma parallel for shared(diag) reduction(max: maxr)num_threads(2)
	for(int i = 1; i < N; i++)
	{
		if(diag[i] > maxr)
			maxr = diag[i];
	}
	t1 = omp_get_wtime();
	printf("\n Massimo Reduction: %d", maxr);
	printf("\n");
	printf("tempo finale: %f\n", t1-t0);
	return 0;
}
