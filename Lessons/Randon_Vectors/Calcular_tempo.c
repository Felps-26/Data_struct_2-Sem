#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAMANHO 200000

int main(){

    int Soma = 0;

    srand(time(NULL));
    clock_t T0 = clock();

    for(int i = 0; i < TAMANHO; i++){
        int temp = rand() % 10000;
        printf("%d\n", temp);
        Soma = Soma + temp;
    }

    clock_t TF = clock();
    
    double TempoCPU = (double)(TF - T0) / CLOCKS_PER_SEC;
    

}