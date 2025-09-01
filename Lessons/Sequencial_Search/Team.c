#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Team.h"

TM * ReadData(char * Arquive){

    printf("Reading data from file: %s\n", Arquive);

    TM * X = malloc(20 * sizeof(TM));
    if(X == NULL){
        printf("Error to allocate memory\n");
        exit(1);
    }

    FILE * fp = fopen(Arquive, "r");
    if(fp == NULL){
        printf("Error to open file %s\n", Arquive);
        exit(1);
    }

    int i = 0;

    char header[100];
    fscanf(fp, "%s", header);

    while(
        fscanf(
            fp, 
            "%d;%[^;];%[^;];%d;%d;%d;%d;%d;%d;%d;%f",
            &X[i].Pos, X[i].Stt, X[i].Team,
            &X[i].Pts, &X[i].Gp, &X[i].W, &X[i].D, &X[i].L,
            &X[i].Gf, &X[i].Ga, &X[i].Gd, &X[i].Avg
        ) == 11){
           X[i].Avg = (float) 100 * X[i].Pts / (3 * X[i].Gp);
              i++;
    }

    fclose(fp);
    return X;
}