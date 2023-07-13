#include <stdio.h>		
#include <stdlib.h>
#include <omp.h>		

int main(){


	double**A;
	double *b, *a,*out1,*r, *r1, *out1;
	double alpha,beta;
	double out = 1;
	int N,M,ops = 0;
	double t0,t1;
	
	N = M = 8;
	r = (double*) calloc (M,sizeof(double));
	r1 = (double*) calloc (M,sizeof(double));
	out1 = (double*) calloc (M,sizeof(double));
	a = (double*) calloc (N,sizeof(double));
	b = (double*) calloc (N,sizeof(double));
	
	A = (double*) calloc (N,sizeof(double));
	for (int i = 0; i < N; ++i)
	{
		A[i] = (double*) calloc (N,sizeof(double));
	}
	for (int i = 0; i < N; ++i)
	{
		a[i] = (double)((rand()%1000)+1)/1000;
		b[i] = (double)((rand()%1000)+1)/1000;
		for(int j = 0; j < M; j++){
			A[i][j] = (double)((rand()%1000)+1)/1000;
		}
	}


	alpha = 3;
	beta = 2;
	double sum = 0;
	#pragma omp parallel sections num_threads(2) reduction(+=sum)
	{
		#pragma omp section
		{
			for(int i = 0; i < M; i++){
				for (int j = 0; j < N; ++j)
				{
					// alpha x A x b;
					r[i] += alpha*A[i][j]*b[j];
			
				}
			}
			
			//printf("Sono il thread numero: %d\n", omp_get_thread_num());
			//printf("Hello world One!\n");
		}
		
		
		#pragma omp section 
		{
		
			for(int i = 0; i < M; i++){
		
				r1[i] += (a[i]*beta);
			}
			//printf("Sono il thread numero: %d\n", omp_get_thread_num());
			//printf("Hello world Two!\n");
		}
		
		#pragma omp section 
		{
			for(int i = 0; i < M; i++){
		
				sum += r[i] + r1[i];
			}
			
			out = sum;
		}
	
	
	}
		
	printf("sum: %f", out);
	
	
	return 0;


}

