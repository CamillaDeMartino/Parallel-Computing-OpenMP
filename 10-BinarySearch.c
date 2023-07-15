// Binary Search algorithm using OMP parallel

#include <stdio.h>
#include <omp.h>
#include <stdlib.h>

#define N 100

int binary(int l, int r, int key, int n, int *a){
    int index = -1;
    int size = (r-l+1)/n;

    /**
     * Se l'intervallo è abbastanza piccolo o è presente un solo thread, 
     * si esegue una ricerca sequenziale all'interno dell'intervallo
    */
    if(size == 0 || n == 1){
        #pragma omp parallel for
        for(int i = l; i <= r; i++){
            if(a[i] == key){
                index = i;
            }
        }
        return index;
    }

    int left = l;
    int right = r;

    omp_set_num_threads(n);
    /**
     * Quando si chiama omp_set_nested(1) con il valore 1 come argomento,
     * si imposta l'abilitazione delle regioni parallele annidate.
     * Ciò significa che è possibile creare regioni parallele all'interno di
     * altre regioni parallele e i thread possono essere creati per
     * l'esecuzione di queste regioni annidate. 
    */
    omp_set_nested(1);
    
    #pragma omp parallel
    {
        int id = omp_get_thread_num();
        int lt = l + id * size;
        int rt = lt + size - 1;

        //Regola l'intervallo dell'ultimo thread per coprire gli elementi rimanenti
        if(id == n-1){
            rt = r;
        }

        //Controlla se la chiave si trova all'interno del sottointervallo del thread
        if(a[lt] <= key && a[rt] >= key){
            left = lt;
            right = rt;
        }
    }

    //Se il sottointervallo non è cambiato, la chiave non viene trovata
    if(left == l && right == r){
        return -1;
    }

    return binary(left, right, key, n, a);
}

int main() {
    int * vector;
    vector = malloc(N * sizeof(int));

    int key = 0;

    do {
        printf("Inserisci la chiave: ");
        scanf("%d", &key);
    } while (key > (N - 1) || key < 0);
    
    for (size_t i = 0; i < N; i++)
        vector[i] = i;
    
    printf("Vettore: ");
    for (int i = 0; i < N; i++)
        printf("%d ", vector[i]);
    
    printf("\nBinary Search con chiave %d è: %d", key, binary(0, N, key, N, vector));
    
    printf("\n");
    return 0;
}
