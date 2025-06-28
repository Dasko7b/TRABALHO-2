#include <string.h>
#include "pacientes.h"

//Dyego Dasko
//inicia cabeçalho da lista de registros
void iniciarRegistros(cabeca* c) {
    c->inicio = NULL;
    c->fim = NULL;
    c->tamanho = 0;
}

//Dyego Dasko
//registra paciente na lista com o nome,idade e sintomas
int registraPaciente(cabeca* c, char nome[200], char idade[4], char sintomas[500]) {
    if (c == NULL) {
        printf("Erro: Lista não foi iniciada.\n");
        return 1;
    }

    pacientes* paciente = (pacientes*) malloc(sizeof(pacientes));
    if (paciente == NULL) {
        printf("Erro: Falha na alocação de memória.\n");
        return 1;
    }

    strcpy(paciente->nome, nome);
    strcpy(paciente->idade, idade);
    strcpy(paciente->sintomas, sintomas);
    paciente->prioridade = 0;
    paciente->emFila = false;
    paciente->atendido = false;
    paciente->Prox = NULL;

    if (c->inicio == NULL) {
        c->inicio = paciente;
        c->fim = paciente;
    } else {
        c->fim->Prox = paciente;
        c->fim = paciente;
    }
    
    c->tamanho++;
    return 0;
}

//Dyego Dasko
//libera os ponteiros  alocados para a lista e cria uma nova lista
int liberarRegistros(cabeca* c) {
    if (c == NULL) {
        printf("Erro: Lista não foi iniciada.\n");
        return 1;
    }

    pacientes* atual = c->inicio;
    pacientes* proximo;

    while (atual != NULL) {
        proximo = atual->Prox;
        free(atual);
        atual = proximo;
    }

    iniciarRegistros(c);
    
    printf("Todos os registros foram liberados com sucesso.\n");
    return 0;
}

//Dyego Dasko
//imprime todos os pacientes registrados na lista
void imprimirRegistros(cabeca* c) {
    if (c == NULL || c->inicio == NULL) {
        printf("Lista de pacientes está vazia.\n");
        return;
    }

    printf("\n--- LISTA DE PACIENTES ---\n");
    printf("Total de pacientes: %d\n\n", c->tamanho);

    pacientes* atual = c->inicio;
    int i = 1;
    while (atual != NULL) {
        printf("Paciente #%d\n", i);
        printf("  Nome: %s\n", atual->nome);
        printf("  Idade: %s\n", atual->idade);
        printf("  Sintomas: %s\n", atual->sintomas);
        printf("---------------------------\n");
        atual = atual->Prox;
        i++;
    }
}