/*
	Somma di N numeri con N = Kp con la PRIMA STRATEGIA
*/


#include <stdio.h>		
#include <stdlib.h>
#include <omp.h>		

int main () {
	int i, N, t, nloc;
	float *a, sumtot, sum;
	sumtot = 0;
	
	printf("Inserire N:  \n");
	scanf(" %d", &N);
	
	//allocazione
	a = (float *)calloc(N, sizeof(float));
	
	
	//lettura
	printf("Inserire gli elementi del vettore a da sommare\n");
	for(i = 0; i < N; i++)
	{
		scanf(" %f", &a[i]);
	}
	
	
	//parallelo somma tra vettori
	#pragma omp parallel private(nloc, i, sum) shared(sumtot)		//ognuno di loro calcola la somma di una certa porzione che è quindi privata		
	{
		t = omp_get_num_threads();					//numero di thread
		nloc = N/t;							//divido il size per il numero di thread, tutti lavorano sullo stesso numero di elementi
		
		printf("sono %d, di %d: numeri %d\n", omp_get_thread_num(), t, nloc);
		
		sum = 0;
		
		for(i = 0; i < nloc; i++)
		{				
			sum = sum + a[i + nloc*omp_get_thread_num()];
		}
		sumtot += sum;
	}//fine direttiva
	
	//stampa finale
	printf("somma finale: %f\n", sumtot);
	
}
