#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Team.h"

int main(){

    TM * Tabel = ReadData("Tabel.csv");
    for (int i = 0; i < 20, i++)
        printf("%d\t%.2f%%\t%s\n",
            Tabel[i].Pos,
            Tabel[i].Avg,
            Tabel[i].Team);

    return 0;
}