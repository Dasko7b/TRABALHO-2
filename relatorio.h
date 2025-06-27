//RELATORIO.h FEITO POR THIAGO DE LIMA DE ASSIS CORDEIRO
#ifndef RELATORIO_H
#define RELATORIO_H

#include <stdio.h>
#include <stdlib.h>

#define MAX_RELATORIO 100

typedef struct {
    char nomeRe[200];
    char idadeRe[4];
    char sintomasRe[500];
    int prioridadeRe;
} dadoRelatorio;

typedef struct {
    dadoRelatorio dados[MAX_RELATORIO];
    int inicio;
    int fim; 
    int tamanho; 
} Relatorio;

Relatorio* iniciarRelatorio(void);
int adicionaRelatorio(Relatorio* r, char nome[200], char idade[4], char sintomas[500], int prioridade);
void imprimirRelatorio(Relatorio* r);
void liberarRelatorio(Relatorio* r);

#endif
