#include <stdio.h>
#include <stdlib.h>

int main (){
    FILE * fp;
    fp = fopen ("db.txt", "r");

    if(fp == NULL) {
        printf("Error reading file");
        exit(1);
    }
    printf("File read successfully\n");

    int acc;
    float bal;
    char name[50];

    for(int i = 0; i <= 3; i++) {
        fscanf(fp, "%d %f %[^\n]", &acc, &bal, name);
        printf("Account: %d\nBalance: %.2f\nName: %s\n", acc, bal, name);
        printf("---------------------\n");
    }

    fclose(fp);

    return 0;
}