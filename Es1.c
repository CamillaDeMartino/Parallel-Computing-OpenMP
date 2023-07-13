/*
	Somma di 2 vettori con STESSO SIZE
*/


#include <stdio.h>	
#include <stdlib.h>
#include <omp.h>		//per prog parallel

int main () {
	int i, N, t, nloc, indice;
	float *a, *b, *c;
	
	printf("Inserire N:  \n");
	scanf(" %d", &N);
	
	//allocazione
	a = (float *)calloc(N, sizeof(float));
	b = (float *)calloc(N, sizeof(float));
	c = (float *)calloc(N, sizeof(float));
	
	
	//lettura
	printf("Inserire gli elementi del vettore a\n");
	for(i = 0; i < N; i++)
	{
		scanf(" %f", &a[i]);
	}
	printf("Inserire gli elementi del vettore b\n");
	for(i = 0; i < N; i++)
	{
		scanf(" %f", &b[i]);
	}
	
	//parallelo somma tra vettori
	#pragma omp parallel private(nloc, i, indice) shared(a,b,c)		//n.b nloc potrebbe anche non essere privato perché ogni thread lavora su uno stesso numero
	{
		t = omp_get_num_threads();					//numero di thread
		nloc = N/t;							//divido il size per il numero di thread, tutti lavorano sullo stesso numero di elementi
		
		printf("sono %d, di %d: numeri %d\n", omp_get_thread_num(), t, nloc);
		
		for(i = 0; i < nloc; i++)
		{								//omp_get_thread_num è l'identificativo del thread
			indice = i+nloc*omp_get_thread_num();			//è l'indice di scorrimento di ogni thread
			c[indice] = a[indice] + b[indice];
		}
	}//fine direttiva
	
	//stampa finale
	for(i = 0; i < N; i++)
	{
		printf(" %f", c[i]);
	}
	
}
