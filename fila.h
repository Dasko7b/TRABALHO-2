#ifndef FILA_H
#define FILA_H

#include "pacientes.h" 
#include "relatorio.h"
#include <stdbool.h>   

// Função responsável por iniciar fila vazia:
void iniciarFila(cabeca* fila);

// Função que verifica se a fila está vazia:
bool filaEstaVazia(cabeca* fila);

// Função que insere um paciente mantendo a ordem de prioridade:
int inserirPacienteNaFila(cabeca* fila, pacientes* novoPaciente);

// Função que remove e retorna o paciente de maior prioridade:
pacientes* atenderProximoPaciente(cabeca* fila, Relatorio* relatorio);

// Função que exibe todos os pacientes na fila:
void visualizarFilaDeEspera(cabeca* fila);

// Função que libera memória alocada pela fila:
int liberarFila(cabeca* fila);

#endif
