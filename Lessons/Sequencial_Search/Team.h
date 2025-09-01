#ifndef TEAM_H
#define TEAM_H

typedef struct {
    int Pos;
    char Stt[30];
    char Team[50];
    int Pts, Gp, W, D, L, Gf, Ga, Gd;
    float Avg;
} TM;

TM * ReadData(char * Arquive);




#endif