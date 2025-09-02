#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TAMANHO 100

int main(){

    int V[TAMANHO];

    for(int i = 0; i < TAMANHO; i++) V[i] = rand();
    for(int i = 0; i < TAMANHO; i++) printf("%d\t", V[i]);
}