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
        printf("6. Listar por prioridade\n");
        printf("7. Listar por categoria\n");
        printf("8. Listar por prioridade e categoria\n");
        printf("9. Sair\n");
        scanf("%d", &opcao);

        switch (opcao) {
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
            case 5: {
                int filtro;
                printf("\nSelecione um filtro:\n");
                printf("1. Filtrar tarefas por prioridade\n");
                printf("2. Filtrar tarefas por estado\n");
                printf("3. Filtrar tarefas por categoria\n");
                printf("4. Filtrar tarefas por prioridade e categoria\n");
                scanf("%d", &filtro);

                switch (filtro) {
                    case 1: {
                        int prioridade;
                        printf("Digite a prioridade desejada: ");
                        scanf("%d", &prioridade);
                        filtrar_tarefas_por_prioridade(tarefas, numero_tarefas, prioridade);
                        listar_tarefas(tarefas, numero_tarefas, 20);
                        break;
                    }
                    case 2: {
                        char estado[20];
                        printf("Digite o estado desejado: ");
                        scanf(" %[^\n]s", estado);
                        // Filtrar tarefas por estado
                        // Código específico para filtrar tarefas por estado
                        break;
                    }
                    case 3: {
                        char categoria[100];
                        printf("Digite a categoria desejada: ");
                        scanf(" %[^\n]s", categoria);
                        // Filtrar tarefas por categoria
                        // Código específico para filtrar tarefas por categoria
                        break;
                    }
                    case 4: {
                        int prioridade;
                        printf("Digite a prioridade desejada: ");
                        scanf("%d", &prioridade);
                        char categoria[100];
                        printf("Digite a categoria desejada: ");
                        scanf(" %[^\n]s", categoria);
                        // Filtrar tarefas por prioridade e categoria
                        // Código específico para filtrar tarefas por prioridade e categoria
                        break;
                    }
                    default:
                        printf("Opcao invalida.\n");
                }
                break;
              
            case 6:
              {
                  int prioridade;
                  printf("Digite a prioridade para exportar as tarefas: ");
                  scanf("%d", &prioridade);
                  exportar_tarefas_por_prioridade(tarefas, numero_tarefas, prioridade);
                  printf("Tarefas exportadas com sucesso.\n");
                  break;
              }

            case 7:
              {
                  char categoria[100];
                  printf("Digite a categoria para exportar as tarefas: ");
                  scanf(" %[^\n]s", categoria);
                  exportar_tarefas_por_categoria(tarefas, numero_tarefas, categoria);
                  printf("Tarefas exportadas com sucesso.\n");
                  break;
              }
            
            case 8:
              {
                  int prioridade;
                  char categoria[100];
                  printf("Digite a prioridade para exportar as tarefas: ");
                  scanf("%d", &prioridade);
                  printf("Digite a categoria para exportar as tarefas: ");
                  scanf(" %[^\n]s", categoria);
                  exportar_tarefas_por_prioridade_e_categoria(tarefas, numero_tarefas, prioridade, categoria);
                  printf("Tarefas exportadas com sucesso.\n");
                  break;
              }
            
               default:
                printf("Opcao invalida.\n"); // Exibe uma mensagem de erro caso digite uma opção errada
            
        }
    } while(opcao != 9);

    return 0; // Finaliza o programa
    }
}