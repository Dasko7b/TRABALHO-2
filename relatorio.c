//RELATORIO.C FEITO POR THIAGO DE LIMA DE ASSIS CORDEIRO
//Implementa o uso de uma fila simples, onde é armazenado o historico do paciente e depois imprime na order da prioridade
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "relatorio.h"

// Cria uma nova fila vazia
Relatorio* iniciarRelatorio(void) {
    Relatorio* novoRelatorio = (Relatorio*)malloc(sizeof(Relatorio));
    if (novoRelatorio != NULL) {
        novoRelatorio->inicio = 0;
        novoRelatorio->fim = 0;
        novoRelatorio->tamanho = 0;
    }
    return novoRelatorio;
}

int adicionaRelatorio(Relatorio* r, char nome[200], char idade[4], char sintomas[500], int prioridade) {

    if (r == NULL || r->tamanho >= MAX_RELATORIO) {

        return 1;

    }

    strcpy(r->dados[r->fim].nomeRe, nome);
    strcpy(r->dados[r->fim].idadeRe, idade);
    strcpy(r->dados[r->fim].sintomasRe, sintomas);
    r->dados[r->fim].prioridadeRe = prioridade;

    r->fim++;
    r->tamanho++;

    return 0;

}

//Imprime os relatórios
void imprimirRelatorio(Relatorio* r){
    if (r == NULL || r->tamanho == 0) {
        printf("Fila vazia\n");
        return;
    }

    dadoRelatorio copia[100];
    dadoRelatorio aux;


    for (int i = 0; i < r->tamanho; i++) {
        copia[i] = r->dados[i];
    }

    // Ordena por prioridade 
    for (int i = 0; i < r->tamanho - 1; i++) {
        for (int j = 0; j < r->tamanho - 1 - i; j++) {
            if (copia[j].prioridadeRe > copia[j + 1].prioridadeRe) {
                aux = copia[j];
                copia[j] = copia[j + 1];
                copia[j + 1] = aux;
            }
        }
    }

    int A = 0, B = 0, C = 0, D = 0, E = 0;

    for (int i = 0; i < r->tamanho; i++) {
        switch (copia[i].prioridadeRe) {
            case 1: A++; break;
            case 2: B++; break;
            case 3: C++; break;
            case 4: D++; break;
            case 5: E++; break;
        }
    }
    int soma = A + B + C + D + E;

    printf("TOTAL DE PACIENTES = %d\n", soma);
    printf("|TOTAL DE PACIENTES POR NIVEL DE PRIORIDADE|\n");
    printf("Prioridade A (1): %d\n", A);
    printf("Prioridade B (2): %d\n", B);
    printf("Prioridade C (3): %d\n", C);
    printf("Prioridade D (4): %d\n", D);
    printf("Prioridade E (5): %d\n", E);
    printf("%-20s %-6s %-30s %-10s\n", "| Nome ", "| Idade", "| Sintomas", "| Prioridade");
    printf("|--------------------------------------------------------------------------------|\n");
    for (int i = 0; i < r->tamanho; i++) {
            printf("%-25s %-5s %-31s %-11d\n",
            copia[i].nomeRe,
            copia[i].idadeRe,
            copia[i].sintomasRe,
            copia[i].prioridadeRe);
    }
}

//Libera o ponteiro alocado para relatorio
void liberarRelatorio(Relatorio* r) {
    if (r != NULL) {
        free(r);
    }
}
