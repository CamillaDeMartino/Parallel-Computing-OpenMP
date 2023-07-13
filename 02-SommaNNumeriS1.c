/*
	Somma di N numeri con N non è esattamente divisibile per p (così puòessere generalizzato)
	con la PRIMA STRATEGIA
*/


#include <stdio.h>		
#include <stdlib.h>
#include <omp.h>		
#include <time.h>

int main () {

	double t0, t1, tempototale;
	int i, N, t, nloc, r, id, step;
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
	
	
	t0 = omp_get_wtime();
	printf("Tempo t0: %lf\n", t0);
	
	//parallelo somma tra vettori
	#pragma omp parallel private(nloc, i, sum, id, step) shared(a, N, sumtot, r)		//ognuno di loro calcola la somma di una certa porzione che è quindi privata		
	{
		t = omp_get_num_threads();					       //numero di thread
		nloc = N/t;							               //divido il size per il numero di thread, tutti lavorano sullo stesso numero di elementi
		
		r = N%t;
		id = omp_get_thread_num();

		//suddivisione del lavoro tra i thread
		if(id < r)
		{
			nloc++;
			step = 0;
		}
		else
			step = r;
			
		printf("sono %d, di %d: numeri %d, resto=%d, passo=%d\n", omp_get_thread_num(), t, nloc, r, step);
		
		sum = 0;
		for(i = 0; i < nloc; i++)
		{				
			sum = sum + a[i + nloc*omp_get_thread_num()+ step];
		}
		
		printf("sono %d, di %d: numeri %d, resto=%d, la mia somma=%f\n", omp_get_thread_num(), t, nloc, r, sum);
		
		sumtot += sum;
	}//fine direttiva
	
	
	t1 = omp_get_wtime();
	printf("Tempo t1: %lf\n", t1);
	//stampa finale
	printf("somma finale: %f\n", sumtot);
	
	tempototale = t1-t0;
	printf("Tempo totale: %lf\n", tempototale);
	
}
