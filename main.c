#include "pacientes.h"

int main() {
    cabeca lista_de_pacientes;

    iniciarRegistros(&lista_de_pacientes);

    printf("Registrando pacientes...\n");
    registraPaciente(&lista_de_pacientes, "Joao da Silva", "45", "Febre e dor de cabeça");
    registraPaciente(&lista_de_pacientes, "Maria Oliveira", "32", "Tosse e dor de garganta");
    registraPaciente(&lista_de_pacientes, "Carlos Pereira", "68", "Pressão alta");
    
    imprimirRegistros(&lista_de_pacientes);

    liberarRegistros(&lista_de_pacientes);
    
    imprimirRegistros(&lista_de_pacientes);

    return 0;
}