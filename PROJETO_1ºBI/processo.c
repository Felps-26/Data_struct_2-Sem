#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "processo.h"

// --------- Leitura de Processo de um CSV (uma linha) --------------
int ler_processo(FILE *fp, Processo *p) {
    char linha[2048];
    if (!fgets(linha, sizeof(linha), fp)) return 0;

    linha[strcspn(linha, "\r\n")] = 0; // remove o \n

    char *token = strtok(linha, ";");
    int i = 0;
    while (token) {
        switch(i) {
            case 0: strncpy(p->id_processo, token, 31); p->id_processo[31] = '\0'; break;
            case 1: strncpy(p->numero_sigilo, token, 63); p->numero_sigilo[63] = '\0'; break;
            case 2: strncpy(p->sigla_grau, token, 7); p->sigla_grau[7] = '\0'; break;
            case 3: strncpy(p->procedimento, token, 63); p->procedimento[63] = '\0'; break;
            case 4: strncpy(p->ramo_justica, token, 31); p->ramo_justica[31] = '\0'; break;
            case 5: strncpy(p->sigla_tribunal, token, 15); p->sigla_tribunal[15] = '\0'; break;
            case 6: p->id_tribunal = atoi(token); break;
            case 7: p->recurso = atoi(token); break;
            case 8: p->id_ultimo_oj = atoi(token); break;
            case 9: {
                strncpy(p->dt_recebimento, token, 11);
                p->dt_recebimento[11] = '\0'; 
                int ano = 0, mes = 0, dia = 0;
                if (sscanf(token, "%d-%d-%d", &ano, &mes, &dia) == 3) {
                    p->ano_recebimento = ano;
                    p->mes_recebimento = mes;
                    p->dia_recebimento = dia;
                } else {
                    p->ano_recebimento = p->mes_recebimento = p->dia_recebimento = 0;
                }
                break;
            }
            case 10: p->id_ultima_classe = atoi(token); break;
            case 11: p->flag_violencia_domestica = atoi(token); break;
            case 12: p->flag_feminicidio = atoi(token); break;
            case 13: p->flag_ambiental = atoi(token); break;
            case 14: p->flag_quilombolas = atoi(token); break;
            case 15: p->flag_indigenas = atoi(token); break;
            case 16: p->flag_infancia = atoi(token); break;
            case 17: strncpy(p->decisao, token, 11); p->decisao[11] = '\0'; break;
            case 18: strncpy(p->dt_resolvido, token, 11); p->dt_resolvido[11] = '\0'; break;
            case 19: p->cnm1 = strlen(token) ? atoi(token) : 0; break;
            case 20: p->primeirasentm1 = atoi(token); break;
            case 21: p->baixm1 = atoi(token); break;
            case 22: p->decm1 = atoi(token); break;
            case 23: p->mpum1 = atoi(token); break;
            case 24: p->julgadom1 = strlen(token) ? atoi(token) : 0; break;
            case 25: p->desm1 = strlen(token) ? atoi(token) : 0; break;
            case 26: p->susm1 = strlen(token) ? atoi(token) : 0; break;
        }
        token = strtok(NULL, ";");
        i++;
    }
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
        int flag_value = 0;
        switch(flag_offset) {
            case 0: flag_value = p.flag_violencia_domestica; break;
            case 1: flag_value = p.flag_feminicidio; break;
            case 2: flag_value = p.flag_ambiental; break;
            case 3: flag_value = p.flag_quilombolas; break;
            case 4: flag_value = p.flag_indigenas; break;
            case 5: flag_value = p.flag_infancia; break;
        }
        if (flag_value == 1) count++;
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
    return 100.0 * ((double)julgadom1 / (cnm1 + desm1 - susm1));
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
