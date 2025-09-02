#ifndef EQUIPE_H
#define EQUIPE_H

// Definindo o TAD Equipe

#define ERRO -999

typedef struct {
    int Posicao;
    char Estado[50];
    char Nome[50];
    int Pontos;
    int J;
    int V;
    int E;
    int D;
    int GP;
    int GC;
    int SG;
    float Aproveitamento; // % de pontos conquistados
} Equipe;

Equipe * LerDados(char * NomeArquivo); // retornar vetor de equipes

int getPontos(Equipe * T, int Posicao); // retornar pontos da equipe na posição dada
float getAproveitamento(Equipe * T, int Posicao); // retornar aproveitamento da equipe na posição dada

#endif