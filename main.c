#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "pacientes.h"
#include "fila.h"
#include "triagem.h"
#include "relatorio.h"

// Função para limpar o buffer do teclado
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Função para obter entrada de string com espaço
void obterString(char *buffer, int tamanho) {
    fgets(buffer, tamanho, stdin);
    buffer[strcspn(buffer, "\n")] = 0; // Remove a nova linha
}

int main() {
    cabeca filaAtendimento; // Fila principal para atendimento (prioritária)
    cabeca registroPacientes; // Lista de todos os pacientes registrados (não na fila)
    Relatorio* historicoAtendimentos = NULL; // Histórico de atendimentos concluídos

    iniciarFila(&filaAtendimento);
    iniciarRegistros(&registroPacientes);
    historicoAtendimentos = iniciarRelatorio();

    int opcao;
    pacientes* pacienteTemp = NULL; // Para gerenciar pacientes a serem cadastrados/atendidos

    do {
        printf("\n--- SIMULADOR DE ATENDIMENTO HOSPITALAR ---\n");
        printf("1. Cadastrar novo paciente\n");
        printf("2. Inserir paciente na fila de atendimento\n");
        printf("3. Atender proximo paciente\n");
        printf("4. Visualizar fila de espera\n");
        printf("5. Exibir registros de pacientes\n");
        printf("6. Imprimir relatorio de atendimentos\n");
        printf("7. Liberar filas e registros (Sair)\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao) {
            case 1: {
                char nome[200];
                char idade[4];
                char sintomas[500];

                printf("\n--- CADASTRO DE PACIENTE ---\n");
                printf("Nome do paciente: ");
                obterString(nome, sizeof(nome));
                printf("Idade do paciente: ");
                obterString(idade, sizeof(idade));
                printf("Sintomas (Ex: dor de cabeca, febre): ");
                obterString(sintomas, sizeof(sintomas));

                registraPaciente(&registroPacientes, nome, idade, sintomas);
                printf("Paciente '%s' cadastrado com sucesso nos registros.\n", nome);
                break;
            }
            case 2: {
                if (registroPacientes.tamanho == 0) {
                    printf("Nao ha pacientes registrados para inserir na fila.\n");
                    break;
                }

                printf("\n--- INSERIR PACIENTE NA FILA ---\n");
                printf("Pacientes registrados disponiveis para fila:\n");
                
                pacientes* atual = registroPacientes.inicio;
                int count = 0;
                while(atual != NULL){
                    if(!atual->emFila && !atual->atendido){ // Filtra por nao estar na fila e nao ter sido atendido
                        printf(" %d - Nome: %s, Idade: %s, Sintomas: %s\n", atual->nome, atual->idade, atual->sintomas);
                        count++;
                    }
                    atual = atual->Prox;
                }
                if(count == 0){
                    printf("Todos os pacientes registrados ja estao na fila, ja foram atendidos ou nao ha pacientes.\n");
                    break;
                }
                
                char nomeBusca[200];
                printf("Digite o nome do paciente para inserir na fila: ");
                obterString(nomeBusca, sizeof(nomeBusca));

                pacientes* pacienteEncontrado = NULL;
                atual = registroPacientes.inicio; // Reinicia a busca
                while (atual != NULL) {
                    if (strcmp(atual->nome, nomeBusca) == 0) {
                        pacienteEncontrado = atual;
                        break;
                    }
                    atual = atual->Prox;
                }

                if (pacienteEncontrado != NULL) {
                    if (pacienteEncontrado->emFila) {
                        printf("Paciente '%s' ja esta na fila de atendimento.\n", nomeBusca);
                        break;
                    }
                    if (pacienteEncontrado->atendido) { // Verifica se já foi atendido
                        printf("Paciente '%s' ja foi atendido e nao pode ser reinserido na fila.\n", nomeBusca);
                        break;
                    }

                    // Cria um NOVO paciente para a fila
                    pacientes* pacienteParaFila = (pacientes*) malloc(sizeof(pacientes));
                    if (pacienteParaFila == NULL) {
                        printf("Erro ao alocar memoria para inserir na fila.\n");
                        break;
                    }
                    // Copia os dados do paciente encontrado para o novo nó da fila
                    strcpy(pacienteParaFila->nome, pacienteEncontrado->nome);
                    strcpy(pacienteParaFila->idade, pacienteEncontrado->idade);
                    strcpy(pacienteParaFila->sintomas, pacienteEncontrado->sintomas);
                    pacienteParaFila->prioridade = 0;
                    pacienteParaFila->emFila = true; // Marca como "em fila"
                    pacienteParaFila->atendido = false; // Garante que o nó da fila não venha como atendido
                    
                    int prioridade;
                    exibir_categorias_de_risco();
                    printf("Defina a prioridade para '%s' (1-5): ", pacienteParaFila->nome);
                    scanf("%d", &prioridade);
                    limparBuffer();

                    if (prioridade >= 1 && prioridade <= 5) {
                        aplicar_classificacao(pacienteParaFila, prioridade);
                        inserirPacienteNaFila(&filaAtendimento, pacienteParaFila);
                        // Marca o paciente ORIGINAL na lista de registros como "em fila"
                        pacienteEncontrado->emFila = true;
                        printf("Paciente '%s' inserido na fila com prioridade %d.\n", pacienteParaFila->nome, prioridade);
                    } else {
                        printf("Prioridade invalida. Paciente nao inserido na fila.\n");
                        free(pacienteParaFila);
                    }
                } else {
                    printf("Paciente '%s' nao encontrado nos registros.\n", nomeBusca);
                }
                break;
            }
            case 3: {
                printf("\n--- ATENDIMENTO DE PACIENTE ---\n");
                pacientes* pacienteAtendido = atenderProximoPaciente(&filaAtendimento);
                if (pacienteAtendido != NULL) {
                    printf("Paciente '%s' (Prioridade: %d) atendido.\n", pacienteAtendido->nome, pacienteAtendido->prioridade);
                    
                    // Encontra o paciente original nos registros para desmarcar 'emFila' e marcar 'atendido'
                    pacientes* atualReg = registroPacientes.inicio;
                    while(atualReg != NULL){
                        // Compara pelo nome e verifica se ele estava na fila
                        if(strcmp(atualReg->nome, pacienteAtendido->nome) == 0 && atualReg->emFila){
                            atualReg->emFila = false;  // Desmarca como "em fila"
                            atualReg->atendido = true; // Marca como "atendido"
                            break;
                        }
                        atualReg = atualReg->Prox;
                    }

                    // Adicionar ao histórico de atendimentos
                    if (historicoAtendimentos != NULL) {
                        adicionaRelatorio(historicoAtendimentos, pacienteAtendido->nome, pacienteAtendido->idade, pacienteAtendido->sintomas, pacienteAtendido->prioridade);
                        printf("Paciente '%s' adicionado ao historico de atendimentos.\n", pacienteAtendido->nome);
                    } else {
                        printf("Erro: Historico de atendimentos nao inicializado.\n");
                    }
                    free(pacienteAtendido); // Libera a memória do paciente atendido (o nó da fila)
                } else {
                    printf("Nao ha pacientes na fila para atendimento.\n");
                }
                break;
            }
            case 4: {
                visualizarFilaDeEspera(&filaAtendimento);
                break;
            }
            case 5: {
                // Modificar imprimirRegistros para mostrar o status 'emFila' e 'atendido'
                if (registroPacientes.inicio == NULL) {
                    printf("Lista de pacientes está vazia.\n");
                } else {
                    printf("\n--- LISTA DE PACIENTES REGISTRADOS ---\n");
                    printf("Total de pacientes: %d\n\n", registroPacientes.tamanho);

                    pacientes* atual = registroPacientes.inicio;
                    int i = 1;
                    while (atual != NULL) {
                        printf("Paciente #%d\n", i);
                        printf("  Nome: %s\n", atual->nome);
                        printf("  Idade: %s\n", atual->idade);
                        printf("  Sintomas: %s\n", atual->sintomas);
                        
                        // Exibição do status
                        if (atual->atendido) {
                            printf("  Status: Atendido\n");
                        } else if (atual->emFila) {
                            printf("  Status: Na Fila de Atendimento\n");
                        } else {
                            printf("  Status: Disponivel para Fila\n");
                        }
                        printf("---------------------------\n");
                        atual = atual->Prox;
                        i++;
                    }
                }
                break;
            }
            case 6: {
                printf("\n--- RELATORIO DE ATENDIMENTOS ---\n");
                if (historicoAtendimentos != NULL) {
                    imprimirRelatorio(historicoAtendimentos);
                } else {
                    printf("Relatorio nao inicializado ou vazio.\n");
                }
                break;
            }
            case 7: {
                printf("Liberando recursos e saindo...\n");
                liberarFila(&filaAtendimento);
                liberarRegistros(&registroPacientes);
                liberarRelatorio(historicoAtendimentos);
                break;
            }
            default: {
                printf("Opcao invalida. Tente novamente.\n");
                break;
            }
        }
    } while (opcao != 7);

    return 0;
}