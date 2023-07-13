#include <stdio.h>
#include <omp.h>


void main(){

	// dichiarizione di variabili
	
	// dichiarazione specifiva
	// -- una variabile per l'identificativo del thread
	// -- una variabile per numero di thread di esecuzione
	int ID_THREAD = 0;
	int NUM_THREADS = 0;
	
	
	
	#pragma omp parallel shared(NUM_THREADS)private(ID_THREAD) 
	{
		ID_THREAD = omp_get_thread_num();
		NUM_THREADS = omp_get_num_threads();
		printf("Hello from thread %d, nThreads %d\n", ID_THREAD, NUM_THREADS);
	}
	
 
}
