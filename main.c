#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "pacientes.h"
#include "fila.h"
#include "triagem.h"
#include "relatorio.h"

//limpar buffer teclado
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

//obter string com espaço
void obterString(char *buffer, int tamanho) {
    fgets(buffer, tamanho, stdin);
    buffer[strcspn(buffer, "\n")] = 0;
}

int main() {
    cabeca filaAtendimento;
    cabeca registroPacientes;
    Relatorio* historicoAtendimentos = NULL;

    iniciarFila(&filaAtendimento);
    iniciarRegistros(&registroPacientes);
    historicoAtendimentos = iniciarRelatorio();

    int opcao;
    pacientes* pacienteTemp = NULL;

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
            //verificacao pacientes na fila
                if (registroPacientes.tamanho == 0) {
                    printf("Nao ha pacientes registrados para inserir na fila.\n");
                    break;
                }

                printf("\n--- INSERIR PACIENTE NA FILA ---\n");
                printf("Pacientes registrados disponiveis para fila:\n");
                
                pacientes* atual = registroPacientes.inicio;
                int count = 0;
                while(atual != NULL){
                    if(!atual->emFila && !atual->atendido){
                        printf(" %d - Nome: %s, Idade: %s, Sintomas: %s\n", atual->nome, atual->idade, atual->sintomas);
                        count++;
                    }
                    atual = atual->Prox;
                }
                if(count == 0){
                    printf("Todos os pacientes registrados ja estao na fila, ja foram atendidos ou nao ha pacientes.\n");
                    break;
                }
            
            //busca paciente por nome
                char nomeBusca[200];
                printf("Digite o nome do paciente para inserir na fila: ");
                obterString(nomeBusca, sizeof(nomeBusca));

                pacientes* pacienteEncontrado = NULL;
                atual = registroPacientes.inicio;
                while (atual != NULL) {
                    if (strcmp(atual->nome, nomeBusca) == 0) {
                        pacienteEncontrado = atual;
                        break;
                    }
                    atual = atual->Prox;
                }
            
                //verifica se o paciente ja foi atendido ou esta na fila
                if (pacienteEncontrado != NULL) {
                    if (pacienteEncontrado->emFila) {
                        printf("Paciente '%s' ja esta na fila de atendimento.\n", nomeBusca);
                        break;
                    }
                    if (pacienteEncontrado->atendido) {
                        printf("Paciente '%s' ja foi atendido e nao pode ser reinserido na fila.\n", nomeBusca);
                        break;
                    }

                    //adiciona os dados do paciente para a fila
                    pacientes* pacienteParaFila = (pacientes*) malloc(sizeof(pacientes));
                    if (pacienteParaFila == NULL) {
                        printf("Erro ao alocar memoria para inserir na fila.\n");
                        break;
                    }

                    strcpy(pacienteParaFila->nome, pacienteEncontrado->nome);
                    strcpy(pacienteParaFila->idade, pacienteEncontrado->idade);
                    strcpy(pacienteParaFila->sintomas, pacienteEncontrado->sintomas);
                    pacienteParaFila->prioridade = 0;
                    pacienteParaFila->emFila = true;
                    pacienteParaFila->atendido = false;
                    
                    //adiciona a prioridade do paciente
                    int prioridade;
                    exibir_categorias_de_risco();
                    printf("Defina a prioridade para '%s' (1-5): ", pacienteParaFila->nome);
                    scanf("%d", &prioridade);
                    limparBuffer();

                    if (prioridade >= 1 && prioridade <= 5) {
                        aplicar_classificacao(pacienteParaFila, prioridade);
                        inserirPacienteNaFila(&filaAtendimento, pacienteParaFila);
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

                //verifica se tem pacientes na lista
                if (pacienteAtendido != NULL) {
                    printf("Paciente '%s' (Prioridade: %d) atendido.\n", pacienteAtendido->nome, pacienteAtendido->prioridade);
                    
                    pacientes* atualReg = registroPacientes.inicio;
                    while(atualReg != NULL){
                        if(strcmp(atualReg->nome, pacienteAtendido->nome) == 0 && atualReg->emFila){
                            atualReg->emFila = false;
                            atualReg->atendido = true;
                            break;
                        }
                        atualReg = atualReg->Prox;
                    }

                    //adiciona no histórico
                    if (historicoAtendimentos != NULL) {
                        adicionaRelatorio(historicoAtendimentos, pacienteAtendido->nome, pacienteAtendido->idade, pacienteAtendido->sintomas, pacienteAtendido->prioridade);
                        printf("Paciente '%s' adicionado ao historico de atendimentos.\n", pacienteAtendido->nome);
                    } else {
                        printf("Erro: Historico de atendimentos nao inicializado.\n");
                    }
                    free(pacienteAtendido);
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
                //imprimir registro de paciente
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