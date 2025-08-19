#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int numerator;
    int denominator;
} Fraction;

Fraction createFraction(int num, int den);
void exibitFraction(Fraction f);
int MCDcalculator(int A, int B);
Fraction simplifyFraction(Fraction f);
Fraction sumFractions(Fraction f1, Fraction f2);
Fraction subFraction(Fraction f1, Fraction f2);

int main() {
    system("cls");

    Fraction F1 = createFraction(24, 30);
    F1 = simplifyFraction(F1);
    exibitFraction(F1);
    printf("\n");

    Fraction F2 = createFraction(-24, 30);
    F2 = simplifyFraction(F2);
    exibitFraction(F2);
    printf("\n");

    Fraction F3 = createFraction(37, 42);
    F3 = simplifyFraction(F3);
    exibitFraction(F3);
    printf("\n");

    Fraction F4 = createFraction(5, 6);
    Fraction F5 = createFraction(4, 9);
    Fraction F6 = sumFractions(F4, F5);
    exibitFraction(F6);
    printf("\n");

    Fraction F7 = subFraction(F4, F5);
    exibitFraction(F7);
    printf("\n");


    return 0;
}

Fraction createFraction(int num, int den) {
    Fraction f;
    f.numerator = num;
    f.denominator = den;
    return f;
}

void exibitFraction(Fraction f) {
    printf("Fraction: %d / %d\n", f.numerator, f.denominator);
    printf("Result: %.2f\n", (float)f.numerator / f.denominator);
}

int MCDcalculator(int A, int B){
    if(A < 0) A = -A;
    if(B < 0) B = -B;

    while(B != 0) {
       int temp = B;
       B = A % B;
       A = temp;
    }
    return A;
}

Fraction simplifyFraction(Fraction f) {
    int mcd = MCDcalculator(f.numerator, f.denominator);
    f.numerator = f.numerator / mcd;
    f.denominator = f.denominator / mcd;
    return f;
}

Fraction sumFractions(Fraction f1, Fraction f2) {
    Fraction Answer;
    Answer.denominator = f1.denominator * f2.denominator;
    Answer.numerator = f1.numerator * f2.denominator + f2.numerator * f1.denominator;
    Answer = simplifyFraction(Answer);
    return Answer;
}

Fraction subFraction(Fraction f1, Fraction f2) {
    Fraction Answer;
    Answer.denominator = f1.denominator * f2.denominator;
    Answer.numerator = f1.numerator * f2.denominator - f2.numerator * f1.denominator;
    Answer = simplifyFraction(Answer);
    return Answer;
}