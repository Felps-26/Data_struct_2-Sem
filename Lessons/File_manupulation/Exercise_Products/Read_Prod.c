#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main (){
    FILE * fp;
    fp = fopen ("Products.txt", "r");

    if(fp == NULL) {
        printf("Error reading file");
        exit(1);
    }
    printf("File read successfully\n");

    char line[100];
    char name[50];
    int quantity;
    float Uprice, price, Tprice = 0;

    while(fgets(line, sizeof(line), fp)){
        if(sscanf(line, "%d %f %[^\n]", &quantity, &Uprice, name) == 3){
            price = quantity * Uprice;
            printf("Product: %s, %d x %.2f, price: %.2f\n", name, quantity, Uprice, price);
            printf("----------------------------------\n");
            Tprice += price;
        }
    }

    printf("Total price of all products: %.2f\n", Tprice);

    fclose(fp);

    return 0;
}