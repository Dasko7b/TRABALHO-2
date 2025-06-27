// triagem.c
// Autor: [Seu Nome]
// Função: Implementa a lógica de classificação de risco do paciente segundo o Protocolo de Manchester

#include <stdio.h>
#include <string.h>
#include "triagem.h"

Classificacao classificar_paciente(int prioridade) {
    Classificacao c;
    c.prioridade = prioridade;

    switch (prioridade) {
        case 1:
            strcpy(c.cor, "Vermelho");
            c.tempo_maximo = 0;
            break;
        case 2:
            strcpy(c.cor, "Laranja");
            c.tempo_maximo = 10;
            break;
        case 3:
            strcpy(c.cor, "Amarelo");
            c.tempo_maximo = 60;
            break;
        case 4:
            strcpy(c.cor, "Verde");
            c.tempo_maximo = 120;
            break;
        case 5:
            strcpy(c.cor, "Azul");
            c.tempo_maximo = 240;
            break;
        default:
            strcpy(c.cor, "Desconhecido");
            c.tempo_maximo = -1;
            break;
    }

    return c;
}

void exibir_categorias_de_risco(void) {
    printf("Categorias de Risco (Protocolo de Manchester):\n");
    printf("1 - Vermelho: Atendimento Imediato\n");
    printf("2 - Laranja : Até 10 minutos\n");
    printf("3 - Amarelo : Até 60 minutos\n");
    printf("4 - Verde   : Até 120 minutos\n");
    printf("5 - Azul    : Até 240 minutos\n");
}

const char* obter_cor_por_prioridade(int prioridade) {
    switch (prioridade) {
        case 1: return "Vermelho";
        case 2: return "Laranja";
        case 3: return "Amarelo";
        case 4: return "Verde";
        case 5: return "Azul";
        default: return "Desconhecido";
    }
}

int obter_tempo_por_prioridade(int prioridade) {
    switch (prioridade) {
        case 1: return 0;
        case 2: return 10;
        case 3: return 60;
        case 4: return 120;
        case 5: return 240;
        default: return -1;
    }



}

void aplicar_classificacao(pacientes* p, int prioridade) {
    if (p == NULL) return;

    p->prioridade = prioridade;

    Classificacao c = classificar_paciente(prioridade);
    printf("Paciente classificado como: %s - Tempo máximo: %d min\n", c.cor, c.tempo_maximo);
}
