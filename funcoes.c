#include "stdio.h"
#include "funcoes.h"
#include <stdlib.h>

// Salva as tarefas em um arquivo
void salvar_tarefas(struct tarefa tarefas[], int numero_tarefas) {
    FILE *fp;
    fp = fopen("tarefas.bin", "wb");
    if(fp == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    }
    fwrite(tarefas, sizeof(struct tarefa), numero_tarefas, fp);
    fclose(fp);
}

// Carrega as informações do arquivo
int carregar_tarefas(struct tarefa tarefas[]) {
    FILE *fp;
    int numero_tarefas = 0;
    fp = fopen("tarefas.bin", "rb");
    if(fp != NULL) {
        while(fread(&tarefas[numero_tarefas], sizeof(struct tarefa), 1, fp) == 1) {
            numero_tarefas++;
        }
        fclose(fp);
    }
    return numero_tarefas;
}

// Adiciona uma nova tarefa à lista
void adicionar_tarefas(struct tarefa tarefas[], int *numero_tarefas) {
    if(*numero_tarefas >= 100) { // Verifica se o limite de tarefas foi atingido
        printf("Limite de tarefas atingido.\n");
        return;
    }
    printf("Digite a prioridade da tarefa (0-10): ");
    scanf("%d", &tarefas[*numero_tarefas].prioridade);
    printf("Digite a descricao da tarefa: ");
    scanf(" %[^\n]s", tarefas[*numero_tarefas].descricao);
    printf("Digite a categoria da tarefa: ");
    scanf(" %[^\n]s", tarefas[*numero_tarefas].categoria);
    (*numero_tarefas)++;
    salvar_tarefas(tarefas, *numero_tarefas); // Salva as tarefas atualizadas no arquivo binário
}

// Apaga uma tarefa da lista
void deletar_tarefas(struct tarefa tarefas[], int *numero_tarefas) {
    int i, indice;
    printf("Digite o indice da tarefa a ser deletada: ");
    scanf(" %d", &indice);
    if(indice >= 0 && indice < *numero_tarefas) {
        for(i = indice; i < *numero_tarefas - 1; i++) {
            tarefas[i] = tarefas[i+1];
        }
        (*numero_tarefas)--;
        salvar_tarefas(tarefas, *numero_tarefas);
    } else {
        printf("Indice invalido.\n");
    }
}
// função para ordenar as tarefas por ordem de prioridade
void listar_prioridade(struct tarefa tarefas[], int numero_tarefas) {
    int i, j;
    struct tarefa organizar;
    for (i = 0; i < numero_tarefas - 1; i++) {
        for (j = 0; j < numero_tarefas - i - 1; j++) {
            if (tarefas[j].prioridade > tarefas[j + 1].prioridade) {
                organizar = tarefas[j];
                tarefas[j] = tarefas[j + 1];
                tarefas[j + 1] = organizar;
            }
        }
    }
}

void listar_tarefas(struct tarefa tarefas[], int numero_tarefas, int max_caracteres) {
    int i;
    listar_prioridade(tarefas, numero_tarefas); // Classifica as tarefas por prioridade
    printf("Lista de tarefas:\n");
    printf("| %-5s | %-10s | %-*s | %-*s |\n", "ID", "Prioridade", max_caracteres, "Descricao", max_caracteres, "Categoria");
    for(i = 0; i < numero_tarefas; i++) {
        printf("| %-5d | %-10d | %-*.*s | %-*.*s |\n", i, tarefas[i].prioridade, max_caracteres, max_caracteres, tarefas[i].descricao, max_caracteres, max_caracteres, tarefas[i].categoria);
    }
}

// Altera uma tarefa existente
void alterar_tarefas(struct tarefa tarefas[], int numero_tarefas) {
    int indice;
    printf("Digite o indice da tarefa a ser alterada: ");
    scanf(" %d", &indice);
    if(indice >= 0 && indice < numero_tarefas) {
        int opcao;
        printf("Selecione o campo que deseja alterar:\n");
        printf("1. Prioridade\n");
        printf("2. Descricao\n");
        printf("3. Categoria\n");
        scanf("%d", &opcao);
        switch(opcao) {
            case 1:
                printf("Digite a nova prioridade: ");
                scanf("%d", &tarefas[indice].prioridade);
                break;
            case 2: {
                printf("Digite a nova descricao: ");
                scanf(" %[^\n]s", tarefas[indice].descricao);
                break;
            }
            case 3: {
                printf("Digite a nova categoria: ");
                scanf(" %[^\n]s", tarefas[indice].categoria);
                break;
            }
            default:
                printf("Opcao invalida.\n");
        }
        salvar_tarefas(tarefas, numero_tarefas);
    } else {
        printf("Indice invalido.\n");
    }
}

void exportar_tarefas_por_prioridade(struct tarefa tarefas[], int numero_tarefas, int prioridade) {
    printf("Tarefas com prioridade %d:\n", prioridade);
    printf("| %-5s | %-10s | %-*s | %-*s |\n", "ID", "Prioridade", 20, "Descricao", 20, "Categoria");
    for(int i = 0; i < numero_tarefas; i++) {
        if(tarefas[i].prioridade == prioridade) {
            printf("| %-5d | %-10d | %-*.*s | %-*.*s |\n", i, tarefas[i].prioridade, 20, 20, tarefas[i].descricao, 20, 20, tarefas[i].categoria);
        }
    }

    FILE *fp;
    fp = fopen("tarefas_por_prioridade.txt", "w");
    if(fp == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    }
    for(int i = 0; i < numero_tarefas; i++) {
        if(tarefas[i].prioridade == prioridade) {
            fprintf(fp, "%d, %s, %s, %s\n", tarefas[i].prioridade, tarefas[i].categoria, tarefas[i].estado, tarefas[i].descricao);
        }
    }
    fclose(fp);
}

void exportar_tarefas_por_categoria(struct tarefa tarefas[], int numero_tarefas, const char categoria[]) {
    printf("Tarefas com categoria %s:\n", categoria);
    printf("| %-5s | %-10s | %-*s | %-*s |\n", "ID", "Prioridade", 20, "Descricao", 20, "Categoria");
    for(int i = 0; i < numero_tarefas; i++) {
        if(strcmp(tarefas[i].categoria, categoria) == 0) {
            printf("| %-5d | %-10d | %-*.*s | %-*.*s |\n", i, tarefas[i].prioridade, 20, 20, tarefas[i].descricao, 20, 20, tarefas[i].categoria);
        }
    }

    FILE *fp;
    fp = fopen("tarefas_por_categoria.txt", "w");
    if(fp == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    }
    for(int i = 0; i < numero_tarefas; i++) {
        if(strcmp(tarefas[i].categoria, categoria) == 0) {
            fprintf(fp, "%d, %s, %s, %s\n", tarefas[i].prioridade, tarefas[i].categoria, tarefas[i].estado, tarefas[i].descricao);
        }
    }
    fclose(fp);
}
