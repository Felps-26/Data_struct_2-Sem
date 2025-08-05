#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//typedef struct Person {
//    char Name[150];
//    char Tel[14];
//    char adress[200];
//} Person;
//
//typedef int Integer;
//
//int main() {
//    
//    Person P;
//    Integer I;
//    
//    strcpy(P.Name, "Maria Alves");
//    strcpy(P.Tel, "(61) 123456789");
//    strcpy(P.adress, "Rua das Flores, 123");
//
//    printf("\nName: %s\n", P.Name);
//    printf("Telephone: %s\n", P.Tel);
//    printf("Address: %s\n", P.adress);
//
//    return 0;
//}

typedef struct {
    float numerator;
    float denominator;
} Fraction;

Fraction createFraction(float num, float den) {
    Fraction f;
    f.numerator = num;
    f.denominator = den;
    return f;
}

int main(){

   Fraction f1 = createFraction(7.0, 2.0);
   printf("Fraction: %.1f / %.1f\n", f1.numerator, f1.denominator);
   printf("result: %.1f\n", f1.numerator / f1.denominator);

    return 0;
}