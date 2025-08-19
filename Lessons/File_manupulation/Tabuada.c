#include <stdio.h>
#include <stdlib.h>

int main (){
    FILE * fp;
    fp = fopen("Tabuada.txt", "w");

    if(fp == NULL) {
        printf("Error opening file");
        exit(1);
    }
    fprintf(fp, "Tabuada do 7\n\n");
    int i = 7;
    for(int j = 1; j <= 10; j++){
        fprintf(fp, "%d x %d = %d\n", i, j, i * j);
    }
    fprintf(fp, "\n");
    

    printf("File opened successfully\n");

    fclose(fp);

    return 0;
}