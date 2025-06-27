// triagem.h
#ifndef TRIAGEM_H
#define TRIAGEM_H
#include "pacientes.h" // Para usar o tipo pacientes


typedef struct {
    int prioridade; // 1 a 5
    char cor[10];   // Vermelho, Laranja, etc.
    int tempo_maximo; // em minutos
} Classificacao;

// Função que retorna uma estrutura Classificacao baseada na entrada de prioridade
Classificacao classificar_paciente(int prioridade);

// Função que imprime as categorias disponíveis
void exibir_categorias_de_risco(void);

// Função auxiliar para converter a prioridade em cor (string)
const char* obter_cor_por_prioridade(int prioridade);

// Função auxiliar para obter o tempo máximo recomendado
int obter_tempo_por_prioridade(int prioridade);


void aplicar_classificacao(pacientes* p, int prioridade);

#endif
