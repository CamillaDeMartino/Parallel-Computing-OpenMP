/**
 * PROVA SCRITTA LABORATORIO TRACCIA 1: 29-06-2023
 * 
 * Implementare un programma parallelo per l'ambiente multicore 
 * con np unità processanti che impieghi la libreria OpenMP.
 * 
 * Il programma deve essere organizzato come segue:
 * 
 * 1. Ogni core deve generare una matrice A di dimensione N/np x M,
 *    mentre solo il core master deve leggere un vettore b di lunghezza M
 * 
 * 2. Tutti i core devono calcolare localmente il prodotto c = A x b
 * 
 * 3. Quindi, i core devono organizzarsi per determinare il massimo
 *    valore tra tutti gli elementi dei vettori locali c e il massimo 
 *    globale tra tutti i vettori locali c
 * 
 * 4. Infine, il core master deve stampare il valore massimo
 *    globale trovato ed il tempo d'esecuzione.
*/

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

void alloc_matrix(int *** matrix, int row, int col);
void fill_matrix(int ** matrix, int row, int col, int max_element);
void print_matrix(int ** matrix, int row, int col);
void dealloc_matrix(int ** matrix, int row);
void fill_array(int * array, int size, int max_element);
void print_array(int * array, int size);

int main() {
	srand(time(NULL));

	double startTime, endTime; // Tempo di inizio e fine del programma

	int ** A; // Matrice A
	int * a, * b;
	int N, M; // N = righe, M = colonne
	int max_element; // Numero massimo generabile all'interno della matrice
	int np; // Unità processanti

	printf("Inserisci il numero di righe: ");
	scanf("%d", &N);
	printf("Inserisci il numero di colonne: " );
	scanf("%d", &M);
	printf("Inserire il massimo numero generabile all'interno della matrice e dei vettori: ");
	scanf("%d", &max_element);
	printf("Inserire il numero di unità processanti: ");
	scanf("%d", &np);
	omp_set_num_threads(np);


    //1
    
    return 0;

}