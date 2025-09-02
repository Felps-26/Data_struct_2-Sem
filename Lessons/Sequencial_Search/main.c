#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "equipe.h"

int main() {

    Equipe * tabela = LerDados("tabela.csv");

    printf("%.2f\n", getAproveitamento(tabela, "Flamengo"));



}
