#include <stdio.h>
#include "funcoes.h"

int main() {
    struct tarefa tarefas[100]; // Cria um array de tarefas
    int numero_tarefas = carregar_tarefas(tarefas); // Carrega as tarefas do arquivo binário

    int opcao;
    do {
        printf("\nSelecione uma opcao:\n");
        printf("1. Adicionar tarefa\n");
        printf("2. Deletar tarefa\n");
        printf("3. Listar todas as tarefas\n");
        printf("4. Alterar tarefas\n");
        printf("5. Filtros\n");
        printf("9. Sair\n");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                adicionar_tarefas(tarefas, &numero_tarefas); // Adiciona uma nova tarefa
                break;
            case 2:
                deletar_tarefas(tarefas, &numero_tarefas); // Apaga uma tarefa existente
                break;
            case 3:
                listar_tarefas(tarefas, numero_tarefas, 20); // Lista todas as tarefas
                break;
            case 4:
                alterar_tarefas(tarefas, numero_tarefas); // Altera uma tarefa existente
                break;
            default:
                printf("Opcao invalida.\n"); // Exibe uma mensagem de erro caso digite uma opção errada
        }
    } while(opcao != 9);

    return 0; // Finaliza o programa
}