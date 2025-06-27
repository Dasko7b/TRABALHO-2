#include <stdio.h>
#include <stdlib.h>
#include "fila.h"
#include "triagem.h" // Para ter acesso a obter_cor_por_prioridade.

void iniciarFila(cabeca* fila) {
    if (fila != NULL) {
        fila->inicio = NULL;
        fila->fim = NULL;
        fila->tamanho = 0;
    }
}

bool filaEstaVazia(cabeca* fila) {
    return (fila == NULL || fila->tamanho == 0);
}

int inserirPacienteNaFila(cabeca* fila, pacientes* novoPaciente) {
    if (fila == NULL || novoPaciente == NULL) {
        printf("Erro: Fila ou paciente inválido.\n");
        return 1;
    }

    novoPaciente->Prox = NULL;

    // Lógica de inserção:
    // Caso 1: Fila está vazia ou o novo paciente tem prioridade mais alta que o primeiro.
    if (filaEstaVazia(fila) || novoPaciente->prioridade < fila->inicio->prioridade) {
        novoPaciente->Prox = fila->inicio;
        fila->inicio = novoPaciente;
    } 
    // Caso 2: Inserir no meio ou no fim da fila.
    else {
        pacientes* atual = fila->inicio;
        // Avança na fila ENQUANTO o próximo nó existir E a prioridade dele for menor ou igual à do novo paciente.
        while (atual->Prox != NULL && atual->Prox->prioridade <= novoPaciente->prioridade) {
            atual = atual->Prox;
        }
        // 'atual' é o nó que deve vir ANTES do novo nó.
        novoPaciente->Prox = atual->Prox;
        atual->Prox = novoPaciente;
    }

    // Atualiza o fim da fila se necessário (importante para consistência)
    if (novoPaciente->Prox == NULL) {
        fila->fim = novoPaciente;
    }
    
    fila->tamanho++;
    return 0;
}

pacientes* atenderProximoPaciente(cabeca* fila) {
    if (filaEstaVazia(fila)) {
        return NULL;
    }

    pacientes* pacienteAtendido = fila->inicio; // O primeiro é sempre o de maior prioridade
    fila->inicio = pacienteAtendido->Prox; // A fila começa no próximo

    if (fila->inicio == NULL) { // Se a fila ficou vazia
        fila->fim = NULL;
    }

    fila->tamanho--;
    pacienteAtendido->Prox = NULL; // "Desconecta" o paciente da fila
    return pacienteAtendido;
}

void visualizarFilaDeEspera(cabeca* fila) {
    printf("\n--- Fila de Espera Atual (Total: %d) ---\n", fila->tamanho);

    if (filaEstaVazia(fila)) {
        printf("Fila vazia.\n");
    } else {
        pacientes* atual = fila->inicio;
        int posicao = 1;
        while (atual != NULL) {
            printf("%dº -> Prioridade: %d (%s) | Nome: %s\n", posicao, atual->prioridade, 
            obter_cor_por_prioridade(atual->prioridade), // Função de 'triagem.h'
            atual->nome);
            atual = atual->Prox;
            posicao++;
        }
    }
    printf("-----------------------------------------\n");
}

int liberarFila(cabeca* fila) {
    if (fila == NULL) return 1;

    pacientes* atual = fila->inicio;
    while (atual != NULL) {
        pacientes* noLiberar = atual;
        atual = atual->Prox;
        free(noLiberar);
    }
    
    // Reseta a estrutura da fila
    iniciarFila(fila);
     
    printf("Fila foi liberada com sucesso.\n");
    return 0;
}
