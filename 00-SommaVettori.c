/*
	Somma di 2 vettori con STESSO SIZE: FULL PARALLEL

	N.B per modificare il numero dithread in fase di compilazione puoi fare export OMP_NUM_THREADS=numero di thread
*/


#include <stdio.h>	
#include <stdlib.h>
#include <omp.h>		//per prog parallela
#include <time.h>

int main() {

	srand(time(NULL));
	int i, N, t, nloc, indice;
	float *a, *b, *c;
	
	printf("Inserire N:  \n");
	scanf(" %d", &N);
	
	//allocazione
	a = (float *)calloc(N, sizeof(float));
	b = (float *)calloc(N, sizeof(float));
	c = (float *)calloc(N, sizeof(float));
	
	
	//lettura
	for(i = 0; i < N; i++)
	{
		a[i] = (float) rand()/(int)RAND_MAX * 10;
	}
	for(i = 0; i < N; i++)
	{
		printf(" %f", a[i]);
	}
	printf("\n");

	for(i = 0; i < N; i++)
	{
		b[i] = (float) rand()/(int)RAND_MAX * 10;

	}
	for(i = 0; i < N; i++)
	{
		printf(" %f", b[i]);
	}
	printf("\n");

	//parallelo somma tra vettori
	#pragma omp parallel private(i, indice) shared(a,b,c, nloc)		//n.b nloc potrebbe anche non essere privato perché ogni thread lavora su uno stesso numero
	{
		t = omp_get_num_threads();					//numero di thread
		nloc = N/t;									//divido il size per il numero di thread, tutti lavorano sullo stesso numero di elementi
		
		printf("sono %d, di %d: numeri %d\n", omp_get_thread_num(), t, nloc);
		
		for(i = 0; i < nloc; i++)
		{													//omp_get_thread_num è l'identificativo del thread
			indice = i+nloc*omp_get_thread_num();			//è l'indice di scorrimento di ogni thread
			c[indice] = a[indice] + b[indice];
		}
	}//fine direttiva
	
	//stampa finale
	for(i = 0; i < N; i++)
	{
		printf(" %f", c[i]);
	}
	printf("\n");


	return 0;
	
}
