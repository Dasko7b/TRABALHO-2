// triagem.h
// Nome: Pedro Henrique Moreira da Silva 
// Função: cabeçalho do arquivo triagem.c 

#ifndef TRIAGEM_H
#define TRIAGEM_H

typedef struct {
    int prioridade; 
    char cor[10];   
    int tempo_maximo; 
} Classificacao;

// Função que retorna uma estrutura Classificacao baseada na entrada de prioridade
Classificacao classificar_paciente(int prioridade);

// Função que imprime as categorias disponíveis
void exibir_categorias_de_risco(void);

// Função auxiliar para converter a prioridade em cor (string)
const char* obter_cor_por_prioridade(int prioridade);

// Função auxiliar para obter o tempo máximo recomendado
int obter_tempo_por_prioridade(int prioridade);

#endif
