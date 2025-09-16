#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 500000

void TrocarElemento(int * A, int * B);
int particao(int * V, int Inf, int Sup);
void QuickSort(int * V, int Inf, int Sup);
void ExibirVetor(int * V, int Tamanho);

double TempoExecucao(void (*func)(int*, int, int), int *V, int Inf, int Sup);

int main(){

    int Vetor[SIZE];
    int Tamanho = SIZE;

    srand(time(NULL));
    for(int i = 0; i < Tamanho; i++)
        Vetor[i] = rand();

    //printf("Vetor antes da ordenação:\n");
    //ExibirVetor(Vetor, Tamanho);

    double tempo = TempoExecucao(QuickSort, Vetor, 0, Tamanho - 1);

    //printf("Vetor após a ordenação:\n");
    //ExibirVetor(Vetor, Tamanho);

    printf("Tempo de execucao da ordenacao: %.3f segundos\n", tempo);
    fflush(stdout);
}

void TrocarElemento(int * A, int * B){

    int temp = *A;
    *A = *B;
    *B = temp;

}

int particao(int * V, int Inf, int Sup){

    int pivot = V[(Inf + Sup) / 2];
    int i = Inf;
    int j = Sup;

    while (i <= j) {
        while (V[i] < pivot) i++;
        while (V[j] > pivot) j--;
        if (i <= j) {
            TrocarElemento(&V[i], &V[j]);
            i++;
            j--;
        }
    }
    return i; // retorna i, não j
}

void QuickSort(int * V, int Inf, int Sup){

    if (Inf < Sup) {
        int index = particao(V, Inf, Sup);
        QuickSort(V, Inf, index - 1);    // até index-1
        QuickSort(V, index, Sup);        // de index até Sup
    }
}

void ExibirVetor(int * V, int Tamanho){

    for(int i = 0; i < Tamanho; i++) printf("%d\t", V[i]);
    printf("\n");

}

// Função para medir tempo de execução
double TempoExecucao(void (*func)(int*, int, int), int *V, int Inf, int Sup){
    clock_t inicio = clock();
    func(V, Inf, Sup);
    clock_t fim = clock();
    return (double)(fim - inicio) / CLOCKS_PER_SEC;
}

