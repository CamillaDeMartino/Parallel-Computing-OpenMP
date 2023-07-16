/**
 * Assegnata una matrice di dimensione N×N, estrarre in parallelo gli elementi
 * della diagonale principale e ricopiarli in un vettore, quindi calcolarne il
 * massimo, con una procedura parallela
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <omp.h>

int main()
{
    srand(time(NULL));
	int **matrix, *diag;
    int n;
    double t0, t1;

    printf("Inserire il size della matrice quadrata: ");
    scanf("%d", &n);

	//Alloco la matrice
	matrix = (int**) calloc(n,sizeof(int*));
	diag = (int*) calloc(n,sizeof(int));

	for(int i = 0; i < n; i++)
	{
		matrix[i] = (int*) calloc(n,sizeof(int));
	}
	
	
	//Riempio la matrice
	for(int i = 0; i < n; i++)
	{
		for(int j = 0 ; j < n ; j++)
		{
				matrix[i][j] = rand() % 11;
		}
	}
	
	printf("\nStampiamo la matrice:\n");
	for(int i = 0; i< n; i++)
	{
		for(int j = 0; j < n; j++)
		{
			printf("%d ", matrix[i][j]);
		}
		printf("\n");
	}
	
	t0 = omp_get_wtime();
	//Mi calcolo la diagonale e la salvo
	#pragma omp parallel for shared(matrix, diag, n) //num_threads(2)
		for(int i = 0; i < n; i++)
		{
			diag[i] = matrix[i][i];
		}
	
	printf("\nStampo la diagonale:\n");
	for(int i = 0 ; i < n; i ++)
	{
			printf(" %d \n",diag[i]);
	}

	int max_value = diag[0];
	
	//Calcolo il massimo del vettore diagonale
	#pragma omp parallel for shared(diag) reduction(max: max_value) //num_threads(2)
		for(int i = 1 ; i < n ; i++)
		{
			if(diag[i] > max_value)
			{
				max_value = diag[i];
			}
		}
	t1 = omp_get_wtime();
	printf("\n");
	printf("tempo finale: %f\n", t1-t0);

	printf("\nMassimo valore del vettore diagonale: %d\n", max_value);


    //Libera la memoria
    for ( int i = 0; i < n; i++ )
        free( ( matrix )[i] );
    free( matrix );
    free( diag );


	return 0;
}