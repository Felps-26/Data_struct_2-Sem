#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAMANHO 500000

void InsertionSort(int * V, int N);
void ExibirVetor(int * V, int N);

int main(){
    int Conjunto[TAMANHO];
    srand(time(NULL));
    for(int i = 0; i < TAMANHO; i++) Conjunto[i] = rand() % 1000;

    clock_t T0 = clock();
    InsertionSort(Conjunto, TAMANHO);
    clock_t T1 = clock();

    printf("Tempo de CPU: %lf segundos\n", (double)(T1 - T0) / CLOCKS_PER_SEC);
    
    printf("Vetor ordenado:\n");
    //ExibirVetor(Conjunto, TAMANHO);

}


void InsertionSort(int * V, int N){
  
    int Chave, i, j;

    for(i = 1; i < N; i++){
        Chave = V[i];
        j = i - 1;

        while(j >= 0 && V[j] > Chave){
            V[j + 1] = V[j];
            j--;
        }

        V[j + 1] = Chave;
    }
}


void ExibirVetor(int * V, int N){
  
    int i;
    for(i = 0; i < N; i++) printf("%d\t", V[i]);
    printf("\n");

}
