#ifndef PACIENTE_H
#define PACIENTE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct pacientes
{
    char nome[200];
    char idade[4];
    char sintomas[500];
    int prioridade;
    struct pacientes* Prox;
} pacientes;

typedef struct cabeca
{
    pacientes* inicio;
    pacientes* fim;
    int tamanho;
} cabeca;

void iniciarRegistros(cabeca* c);
int registraPaciente(cabeca* c, char nome[200], char idade[4], char sintomas[500]);
int liberarRegistros(cabeca* c);
void imprimirRegistros(cabeca* c);

#endif