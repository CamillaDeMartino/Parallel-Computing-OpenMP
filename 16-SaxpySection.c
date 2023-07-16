#include <omp.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char const *argv[])
{
	double**A;
	double *b, *a, *out1,*r;
	double alpha,beta;
	double out = 1;
	int N,M, ops = 0;  // contatore relativo al numero totale di operazioni eseguite
	double t0,t1;

	N = M = 8;
	r = (double*) calloc (M,sizeof(double));
	a = (double*) calloc (N,sizeof(double));
	b = (double*) calloc (N,sizeof(double));
	A = (double**) calloc (N,sizeof(double*));
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

	t0 = omp_get_wtime();
    // Le operaizioni SAXPY sono indipendenti
	#pragma omp parallel sections shared(N, M, A, a, b, r) num_threads(4)
	{
        #pragma omp section
        {
            for(int i = 0; i < M; i++){
		        for (int j = 0; j < N; ++j)
		        {
			        r[i] += alpha*A[i][j]*b[j];
			        #pragma omp atomic update
				        ops = ops +1;
		        }
		
	        }
        }


        #pragma omp section
        {
            for(int i = 0; i < M; i++)
                r[i] += (a[i]*beta);
        }
    }
    

	#pragma omp parallel for reduction(*:out)
	for (int i = 0; i < M; ++i)
	{
		out*=r[i];
	}
	t1 = omp_get_wtime();
	printf("total time = %lf\n\n",t1-t0);
	printf("alpha*A*b = ");

	for (int i = 0; i < N; ++i)
	{
		printf("%lf ",out1[i]);	
	}

	printf("\n\nalpha*A*b + beta*a = ");
	for (int i = 0; i < M; ++i)
	{
		printf("%lf ",r[i]);	
	}

	printf("\n\nout = %lf\n",out);

	return 0;
}