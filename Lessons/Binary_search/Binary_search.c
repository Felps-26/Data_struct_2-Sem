#include <stdio.h>
#include <stdlib.h>

#define ERRO -1

int main(){

    int Numbers[] = {1, 2, 4, 5, 6, 7, 8, 10, 12, 14, 16, 18, 20, 21, 22};
    int Size = sizeof(Numbers) / sizeof(int);
    int Element = 12;
    int Position = PB(Numbers, Size, Element);

    if (Position != ERRO) printf("The Position is %d.\n", Position);
    else printf("Element not found.\n");

}

int PB(int * V, int N, int key){
    int Left = 0;
    int Right = N - 1;

    while(Left <= Right){
        int Mid = (Left + Right) / 2;

        if (V[Mid] == key) return Mid;
        else if (V[Mid] < key) Left = Mid + 1;
        else Right = Mid - 1;
    }

    return ERRO;
}

int PBR(int * V, int Left, int Right, int key){
    if (Left > Right) return ERRO;

    int Mid = (Left + Right) / 2;

    if (V[Mid] == key) return Mid;
    else if (V[Mid] < key) return PBR(V, Mid + 1, Right, key);
    else return PBR(V, Left, Mid - 1, key);
}