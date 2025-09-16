#ifndef PROCESSO_H
#define PROCESSO_H

typedef struct {
    char id_processo[32];
    char numero_sigilo[64];
    char sigla_grau[8];
    char procedimento[64];
    char ramo_justica[32];
    char sigla_tribunal[16];
    int id_tribunal;
    int recurso;
    int id_ultimo_oj;
    char dt_recebimento[12];
    int ano_recebimento;     
    int mes_recebimento;     
    int dia_recebimento;     
    int id_ultima_classe;
    int flag_violencia_domestica;
    int flag_feminicidio;
    int flag_ambiental;
    int flag_quilombolas;
    int flag_indigenas;
    int flag_infancia;
    char decisao[12];
    char dt_resolvido[12];
    int cnm1;
    int primeirasentm1;
    int baixm1;
    int decm1;
    int mpum1;
    int julgadom1;
    int desm1;
    int susm1;
} Processo;

int ler_processo(FILE *fp, Processo *p);
int contar_processos(const char* filename);
int buscar_id_ultimo_oj(const char* filename, const char* id_processo);
void buscar_dt_mais_antiga(const char* filename, char* resultado_id, char* resultado_dt);
int contar_causa(const char* filename, int flag_offset);
void calcular_dias(const char* filename);
double calcular_percentual_meta1(const char* filename);
void gerar_csv_julgados_meta1(const char* filename, const char* csv_saida);

#endif
