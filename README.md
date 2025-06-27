# Atendimento Hospitalar por Classificação de Risco 
## Descrição do Projeto
Este projeto consiste no desenvolvimento de uma aplicação em linguagem C para simular e gerenciar o Atendimento Hospitalar por Classificação de Risco, 
fundamentado no Protocolo de Manchester. O objetivo principal é aplicar de forma funcional os conceitos de estruturas de dados, como filas de prioridade, 
para organizar, manipular e exibir informações de pacientes em um ambiente hospitalar.
Os atendimentos seguem a ordem de prioridade. 
O sistema deve gerar relatórios de paciente atendidos por prioridade, tempo médio de espera por categoria e total de pacientes por nível de risco

## Funcionalidades Implementadas:
- [ ] Cadastrar paciente (nome, idade, sintomas) 
- [ ]	Classificar paciente na triagem com prioridade (1 a 5) e inserir na fila
- [ ]   Atender próximo paciente com maior prioridade
- [ ]	Visualizar fila de espera atual por ordem de prioridade
- [ ] Gerar relatório de atendimentos com: Pacientes atendidos por prioridade,Tempo médio de espera por categoria,Total de pacientes por cor/nível de risco

## Estrutura dos Arquivos do Projeto

O projeto está organizado nos seguintes arquivos principais:

* `main.c`: Contém a **lógica principal** e o controle do sistema, exibindo o menu de opções, recebendo a interação do usuário e chamando as funções dos demais módulos.
* `fila.c`: Implementação das funções relacionadas à **fila circular de espera**, como registrar chegada de pacientes, remover da fila após atendimento e listar a fila atual.
* `fila.h`: Cabeçalho de `fila.c`, contendo as **definições das estruturas de dados** da fila e os **protótipos** das funções de fila.
* `pacientes.c`: Implementação das funções relacionadas ao **cadastro, atualização e listagem de pacientes**, armazenados em uma **lista encadeada**.
* `pacientes.h`: Cabeçalho de `pacientes.c`, com as **structs** dos pacientes e os protótipos das funções.
* `relatorio.c`: Contém as funções para **gerar relatórios** do sistema, como histórico de pacientes atendidos, estatísticas e exportação de dados.
* `relatorio.h`: Cabeçalho de `relatorio.c`, contendo as definições e protótipos das funções de relatório.
* `triagem.c`: Implementação da lógica de **triagem de pacientes**, que define prioridades de atendimento com base nos sintomas, idade ou outros critérios.
* `triagem.h`: Cabeçalho de `triagem.c`, com definições de níveis de prioridade, structs auxiliares e protótipos das funções de triagem.
* `README.md`: Este arquivo, com **instruções de uso, descrição técnica e informações de autoria**.
* `diario_de_bordo.pdf`: Documento entregue junto ao projeto, contendo **relatos semanais do desenvolvimento**, divisão de tarefas, dificuldades encontradas, soluções aplicadas e explicações de trechos de código.

## Como Compilar e Executar

1.  **Compilação:**
    ```bash
    gcc main.c fila.c pacientes.c relatorio.c triagem.c -o main.exe
    ```
2.  **Execução:**
    ```bash
    ./main.exe
    ```

Certifique-se de que todas as dependências (bibliotecas padrão do C) estejam disponíveis no seu sistema.

## Autoria

Este projeto foi desenvolvido por:

* [Bruno Pedron Rupaner] -> main.c
* [Dyego Dasko] -> pacientes.c e pacientes.h
* [Matheus José Chaves de Lima] -> fila.c e fila.h
* [Pedro Henrique Moreira da Silva] -> triagem.c e triagem.h
* [Thiago de Lima de Assis Cordeiro] -> ralatorio.c e relatorio.h