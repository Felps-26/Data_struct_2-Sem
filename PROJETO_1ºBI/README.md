# Projeto Processamento de Dados Judiciais

Este projeto realiza o processamento de dados de processos judiciais a partir de um arquivo CSV, fornecendo estatísticas, buscas e relatórios sobre os processos do TJDFT.

---

## Funcionalidades

- **Leitura de processos:** Carrega os dados de cada processo do arquivo CSV.
- **Contagem de processos:** Informa o número total de processos no arquivo.
- **Busca por data mais antiga:** Localiza o processo com a data de recebimento mais antiga.
- **Contagem por causa temática:** Conta processos de cada causa (violência doméstica, feminicídio, ambiental, quilombolas, indígenas, infância/juventude).
- **Cálculo de dias entre recebimento e resolução:** Para cada processo, calcula o tempo entre recebimento e resolução.
- **Percentual de cumprimento da Meta 1:** Calcula o percentual de processos julgados em relação aos casos novos, conforme a Meta 1 do CNJ.
- **Geração de CSV de julgados:** Cria um novo arquivo CSV apenas com processos julgados (mérito).
- **Busca de id_ultimo_oj:** Busca o identificador do último órgão julgador de um processo específico.

---

## Estrutura dos Arquivos

- `main.c` — Arquivo principal, ponto de entrada do programa.
- `processo.h` — Definição da estrutura de dados e funções.
- `processo.c` — Implementação das funções de processamento.
- `TJDFT_amostra.csv` — Arquivo de dados de entrada (exemplo).
- `julgados_meta1.csv` — Arquivo gerado com processos julgados.

---

## Como Executar

### 1. Pré-requisitos

- Ter um compilador C instalado (GCC, MinGW, etc).
- Ter o arquivo `TJDFT_filtrado.csv` na mesma pasta do executável.

### 2. Compilação

No terminal, navegue até a pasta do projeto e execute:

```sh
gcc main.c processo.c -o projeto
```

### 3. Execução

Execute o programa:

```sh
./projeto
```
Ou, no Windows:
```sh
projeto.exe
```

### 4. Resultados

- O programa exibirá no terminal:
  - Total de processos
  - Processo mais antigo
  - Contagem por causa temática
  - Dias entre recebimento e resolução de cada processo
  - Percentual de cumprimento da Meta 1
  - Id do último órgão julgador de um processo exemplo
- Será gerado o arquivo `julgados_meta1.csv` com os processos julgados.

---

## Observações

- Para testar com outro arquivo, altere o nome do arquivo na linha:
  ```c
  const char *arquivo = "TJDFT_amostra.csv";
  ```
  em `main.c`.
- O código espera que o arquivo CSV esteja no formato correto, com campos separados por `;` e datas no formato `AAAA-MM-DD`.

---

## Dúvidas

Se houver dúvidas, consulte os comentários no código ou entre em contato com o autor do projeto.