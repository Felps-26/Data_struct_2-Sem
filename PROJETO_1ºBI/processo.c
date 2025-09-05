#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "processo.h"

// --------- Leitura de Processo de um CSV (uma linha) --------------
int ler_processo(FILE *fp, Processo *p) {
    char linha[2048];
    if (!fgets(linha, sizeof(linha), fp)) return 0;

    linha[strcspn(linha, "\r\n")] = 0; // remove fim de linha

    // Lê todos os campos em sequência do CSV
    int n = sscanf(linha,
        "%31[^;];%63[^;];%7[^;];%63[^;];%31[^;];%15[^;];%d;%d;%d;%11[^;];%d;%d;%d;%d;%d;%d;%d;%11[^;];%11[^;];%d;%d;%d;%d;%d;%d;%d;%d",
        p->id_processo,
        p->numero_sigilo,
        p->sigla_grau,
        p->procedimento,
        p->ramo_justica,
        p->sigla_tribunal,
        &p->id_tribunal,
        &p->recurso,
        &p->id_ultimo_oj,
        p->dt_recebimento,
        &p->id_ultima_classe,
        &p->flag_violencia_domestica,
        &p->flag_feminicidio,
        &p->flag_ambiental,
        &p->flag_quilombolas,
        &p->flag_indigenas,
        &p->flag_infancia,
        p->decisao,
        p->dt_resolvido,
        &p->cnm1,
        &p->primeirasentm1,
        &p->baixm1,
        &p->decm1,
        &p->mpum1,
        &p->julgadom1,
        &p->desm1,
        &p->susm1
    );
    if (n < 27) return 0;
    return 1;
}


// --------- Função para contar número total de processos -----------
int contar_processos(const char* filename) {
    FILE* fp = fopen(filename, "r");
    if (!fp) return -1;
    char header[2048];
    fgets(header, sizeof(header), fp); // pular cabeçalho
    int count = 0;
    Processo p;
    while(ler_processo(fp, &p)) count++;
    fclose(fp);
    return count;
}

// --------- Busca id_ultimo_oj dado id_processo --------------------
int buscar_id_ultimo_oj(const char* filename, const char* idbusca) {
    FILE* fp = fopen(filename, "r");
    if (!fp) return -1;
    char header[2048];
    fgets(header, sizeof(header), fp);
    Processo p;
    while(ler_processo(fp, &p)) {
        if (strcmp(p.id_processo, idbusca) == 0) {
            fclose(fp);
            return p.id_ultimo_oj;
        }
    }
    fclose(fp);
    return -1;
}

// --------- Busca Processo com data mais antiga (dt_recebimento) ---
void buscar_dt_mais_antiga(const char* filename, char* resultado_id, char* resultado_dt) {
    FILE* fp = fopen(filename, "r");
    if (!fp) return;
    char header[2048];
    fgets(header, sizeof(header), fp);
    Processo p;
    int first = 1;
    while(ler_processo(fp, &p)) {
        if (strlen(p.dt_recebimento) == 0)
            continue;
        if (first || strcmp(p.dt_recebimento, resultado_dt) < 0) {
            strcpy(resultado_id, p.id_processo);
            strcpy(resultado_dt, p.dt_recebimento);
            first = 0;
        }
    }
    fclose(fp);
}

// --------- Conta processos por flag temática ----------------------
int contar_causa(const char* filename, int flag_offset) {
    FILE* fp = fopen(filename, "r");
    if (!fp) return -1;
    char header[2048];
    fgets(header, sizeof(header), fp);
    Processo p;
    int count = 0;
    while(ler_processo(fp, &p)) {
        int *flags[] = {
            &p.flag_violencia_domestica, &p.flag_feminicidio, &p.flag_ambiental,
            &p.flag_quilombolas, &p.flag_indigenas, &p.flag_infancia
        };
        if (*(flags[flag_offset]) == 1)
            count++;
    }
    fclose(fp);
    return count;
}

// --------- Calcula e mostra dias entre recebimento e resolvido ----
void calcular_dias(const char* filename) {
    FILE* fp = fopen(filename, "r");
    if (!fp) return;
    char header[2048];
    fgets(header, sizeof(header), fp);
    Processo p;
    printf("id_processo;dias_entre_recebimento_e_resolvido\n");
    while(ler_processo(fp, &p)) {
        // Exige data no formato YYYY-MM-DD
        if (strlen(p.dt_recebimento) < 10 || strlen(p.dt_resolvido) < 10)
            continue;
        int y1, m1, d1, y2, m2, d2;
        sscanf(p.dt_recebimento, "%d-%d-%d", &y1, &m1, &d1);
        sscanf(p.dt_resolvido, "%d-%d-%d", &y2, &m2, &d2);
        struct tm a = {0,0,0,d1,m1-1,y1-1900};
        struct tm b = {0,0,0,d2,m2-1,y2-1900};
        time_t ta = mktime(&a);
        time_t tb = mktime(&b);
        int dias = ta && tb ? (int)((tb-ta)/86400) : 0;
        printf("%s;%d\n", p.id_processo, dias);
    }
    fclose(fp);
}

// --------- Percentual Cumprimento Meta 1 --------------------------
double calcular_percentual_meta1(const char* filename) {
    FILE* fp = fopen(filename, "r");
    if (!fp) return -1.0;
    char header[2048];
    fgets(header, sizeof(header), fp);
    Processo p;
    int cnm1=0, julgadom1=0, desm1=0, susm1=0;
    while(ler_processo(fp, &p)) {
        cnm1 += p.cnm1;
        julgadom1 += p.julgadom1;
        desm1 += p.desm1;
        susm1 += p.susm1;
    }
    fclose(fp);
    if (cnm1 + desm1 - susm1 == 0) return 0.0;
    return 100.0 * julgadom1 / (cnm1 + desm1 - susm1);
}

// --------- Gera CSV só com processos julgados (mérito) -------------
void gerar_csv_julgados_meta1(const char* filename, const char* csv_saida) {
    FILE* fp = fopen(filename, "r");
    FILE* fo = fopen(csv_saida, "w");
    if (!fp || !fo) return;
    char header[2048];
    fgets(header, sizeof(header), fp);
    fprintf(fo, "%s", header); // manter cabeçalho
    Processo p;
    while(ler_processo(fp, &p)) {
        if (p.julgadom1 > 0)
            fprintf(fo, "%s;%s;%s;%s;%s;%s;%d;%d;%d;%s;%d;%d;%d;%d;%d;%d;%d;%s;%s;%d;%d;%d;%d;%d;%d;%d;%d\n",
                p.id_processo, p.numero_sigilo, p.sigla_grau, p.procedimento, p.ramo_justica,
                p.sigla_tribunal, p.id_tribunal, p.recurso, p.id_ultimo_oj, p.dt_recebimento, p.id_ultima_classe,
                p.flag_violencia_domestica, p.flag_feminicidio, p.flag_ambiental, p.flag_quilombolas,
                p.flag_indigenas, p.flag_infancia, p.decisao, p.dt_resolvido, p.cnm1, p.primeirasentm1,
                p.baixm1, p.decm1, p.mpum1, p.julgadom1, p.desm1, p.susm1);
    }
    fclose(fp);
    fclose(fo);
}
