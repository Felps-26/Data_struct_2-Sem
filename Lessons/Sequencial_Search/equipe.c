#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "equipe.h"

// Recebe NomeArquivo como parâmetro e retorna vetor de Equipes

Equipe * LerDados(char * NomeArquivo) {

    FILE * fp = fopen(NomeArquivo, "r");
    if(fp == NULL) {
        printf("ERRO: o arquivo nao pode ser aberto");
        exit(ERRO);
    }
    
    char buffer[200];
    fscanf(fp, "%s", buffer);

    Equipe * X = malloc(20 * sizeof(Equipe));
    int i = 0;

    while (fscanf(fp,
        "%d;%[^;];%[^;];%d;%d;%d;%d;%d;%d;%d;%d\n",
        &X[i].Posicao, // Lendo a posição da equipe (1ª coluna)
        X[i].Estado,   // Lendo estado (incluindo espaços em nomes compostos)
        X[i].Nome,
        &X[i].Pontos,
        &X[i].J,
        &X[i].V,
        &X[i].E,
        &X[i].D,
        &X[i].GP,
        &X[i].GC,
        &X[i].SG
        ) == 11) {
                X[i].Aproveitamento = 100 * (float) X[i].Pontos / (float) (3 * X[i].J);                
                i++;
    }

    fclose(fp);
    return X;

}

int getPontos(Equipe * T, int Posicao){

    int i;
    for(i = 0; i < 20; i++)
        if(T[i].Posicao == Posicao)
            return T[i].Pontos;
        
        return ERRO;
}

float getAproveitamento(Equipe * T, int Posicao){
    int i;
    for (i = 0 ; i < 20; i++)
        if(T[i].Posicao == Posicao)
            return T[i].Aproveitamento;
    return ERRO;
}