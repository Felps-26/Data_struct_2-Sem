#include <stdio.h>
#include "processo.h"

int main() {
    const char *arquivo = "Amostra.csv";

    printf("Total de processos: %d\n", contar_processos(arquivo));

    char id_antiga[32], data_antiga[12]="";
    buscar_dt_mais_antiga(arquivo, id_antiga, data_antiga);
    printf("Processo mais antigo: %s na data %s\n", id_antiga, data_antiga);

    // Você pode exibir as causas assim:
    printf("Violência Doméstica: %d\n", contar_causa(arquivo, 0));
    printf("Feminicídio: %d\n", contar_causa(arquivo, 1));
    printf("Ambiental: %d\n", contar_causa(arquivo, 2));
    printf("Quilombolas: %d\n", contar_causa(arquivo, 3));
    printf("Indígenas: %d\n", contar_causa(arquivo, 4));
    printf("Infância/juventude: %d\n", contar_causa(arquivo, 5));

    // Exibe os dias para cada processo:
    calcular_dias(arquivo);

    // Mostra o percentual de meta 1:
    printf("Cumprimento da Meta 1: %.2f%%\n", calcular_percentual_meta1(arquivo));

    // Gera arquivo só com julgados (mérito) na Meta 1
    gerar_csv_julgados_meta1(arquivo, "julgados_meta1.csv");

    // Exemplo busca id_ultimo_oj de um processo específico:
    printf("Id último OJ do proc 323961068: %d\n", buscar_id_ultimo_oj(arquivo, "323961068"));

    return 0;
}
