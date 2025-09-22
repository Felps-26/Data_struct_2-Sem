#include <stdio.h>
#include "processo.h"

int main() {
    const char *arquivo = "TJDFT_amostra.csv"; // altere aqui para testar outros arquivos

    printf("Total de processos: %d\n", contar_processos(arquivo));

    char id_antiga[32], data_antiga[12]="";
    buscar_dt_mais_antiga(arquivo, id_antiga, data_antiga);
    printf("Processo mais antigo: %s na data %s\n", id_antiga, data_antiga);

    // Exibição das causas:
    printf("Violencia Domestica: %d\n", contar_causa(arquivo, 0));
    printf("Feminicidio: %d\n", contar_causa(arquivo, 1));
    printf("Ambiental: %d\n", contar_causa(arquivo, 2));
    printf("Quilombolas: %d\n", contar_causa(arquivo, 3));
    printf("Indigenas: %d\n", contar_causa(arquivo, 4));
    printf("Infancia/juventude: %d\n", contar_causa(arquivo, 5));

    // Exibe os dias para cada processo:
    calcular_dias(arquivo);

    // Mostra o percentual de meta 1:
    printf("Cumprimento da Meta 1: %.2f%%\n", calcular_percentual_meta1(arquivo));

    // Gera arquivo so com julgados (merito) na Meta 1
    gerar_csv_julgados_meta1(arquivo, "julgados_meta1.csv");

    // Exemplo busca id_ultimo_oj de um processo especifico:
    printf("Id ultimo OJ do proc 323961068: %d\n", buscar_id_ultimo_oj(arquivo, "323961068"));

    return 0;
}
