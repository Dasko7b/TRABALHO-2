#include <stdio.h>
#include <stdlib.h>
#include "relatorio.h"

// Cria uma nova fila vazia
Relatorio* iniciarRelatorio(Relatorio* r){

    Relatorio* novoRelatorio = (Relatorio*)malloc(sizeof(Relatorio));

    if (novoRelatorio != NULL){
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

    //r->fim++ estava aqui tirei porque na minha cabeça não fazia sentido ele estar aqui

    strcpy(r->dados[r->fim].nomeRe, nome);
    strcpy(r->dados[r->fim].idadeRe, idade);
    strcpy(r->dados[r->fim].sintomasRe, sintomas);
    r->dados[r->fim].prioridadeRe = prioridade;

    r->fim++;
    r->tamanho++;


    return 0;

}

void imprimirRelatorio(Relatorio* r, int tipo){
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


    printf("Prioridade A (1): %d\n", A);
    printf("Prioridade B (2): %d\n", B);
    printf("Prioridade C (3): %d\n", C);
    printf("Prioridade D (4): %d\n", D);
    printf("Prioridade E (5): %d\n", E);
    printf("%-20s %-6s %-30s %-10s\n", "| Nome ", "| Idade", "| Sintomas", "| Prioridade");
    printf("---------------------------------------------------------------------\n");
    for (int i = 0; i < r->tamanho; i++) {
            printf("%-20s %-6s %-30s %-10d\n",
            copia[i].nomeRe,
            copia[i].idadeRe,
            copia[i].sintomasRe,
            copia[i].prioridadeRe);
    }
}

void liberarRelatorio(Relatorio* r) {
    if (r != NULL) {
        free(r);
    }
}
