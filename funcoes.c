#include "stdio.h"
#include "funcoes.h"
#include <stdlib.h>
#include <string.h>

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
void adicionar_tarefas(struct tarefa tarefas[], int *numero_tarefas){
    if(*numero_tarefas >= 100) {
        printf("Limite de tarefas atingido.\n");
        return;
    }
    printf("Digite a prioridade da tarefa (0-10): ");
    scanf("%d", &tarefas[*numero_tarefas].prioridade);
    printf("Digite a descricao da tarefa: ");
    scanf(" %[^\n]s", tarefas[*numero_tarefas].descricao);
    printf("Digite a categoria da tarefa: ");
    scanf(" %[^\n]s", tarefas[*numero_tarefas].categoria);

    while (1){
    printf("Digite o estado da tarefa (Completo, Em andamento, Nao iniciado): ");
    scanf(" %[^\n]s", tarefas[*numero_tarefas].estado);
    if (strcmp(tarefas[*numero_tarefas].estado, "Completo") == 0 || strcmp(tarefas[*numero_tarefas].estado, "Em andamento") == 0 || strcmp(tarefas[*numero_tarefas].estado, "Nao iniciado") == 0) {
                break;
            } else {
                printf("Estado inválido. Por favor, digite novamente.\n");
            }
        }
        (*numero_tarefas)++;
        salvar_tarefas(tarefas, *numero_tarefas);
        printf("Tarefa Criada");
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

// Altera uma tarefa da lista
void alterar_tarefas(struct tarefa tarefas[], int numero_tarefas) {
    int indice;
    printf("Digite o indice da tarefa a ser alterada: ");
    scanf("%d", &indice);
    if(indice >= 0 && indice < numero_tarefas) {
        printf("Digite o campo a ser alterado (prioridade, descricao, categoria, estado): ");
        char campo[20];
        scanf("%s", campo);
        if (strcmp(campo, "prioridade") == 0) {
            printf("Digite a nova prioridade: ");
            scanf("%d", &tarefas[indice].prioridade);
        } else if (strcmp(campo, "descricao") == 0) {
            printf("Digite a nova descricao: ");
            scanf(" %[^\n]s", tarefas[indice].descricao);
        } else if (strcmp(campo, "categoria") == 0) {
            printf("Digite a nova categoria: ");
            scanf(" %[^\n]s", tarefas[indice].categoria);
        } else if (strcmp(campo, "estado") == 0) {
            printf("Digite o novo estado: ");
            scanf(" %[^\n]s", tarefas[indice].estado);
        }
        salvar_tarefas(tarefas, numero_tarefas);
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
    printf("| %-5s | %-10s | %-*s | %-*s | %-*s\n", "ID", "Prioridade", max_caracteres, "Descricao", max_caracteres, "Categoria", max_caracteres, "Estado");
    for(i = 0; i < numero_tarefas; i++) {
        printf("| %-5d | %-10d | %-*.*s | %-*.*s | %-*.*s\n", i, tarefas[i].prioridade, max_caracteres, max_caracteres, tarefas[i].descricao, max_caracteres, max_caracteres, tarefas[i].categoria, max_caracteres, max_caracteres, tarefas[i].estado);
    }
}

void filtrar_tarefas_por_prioridade(struct tarefa tarefas[], int numero_tarefas, int prioridade) {
    printf("Tarefas com prioridade %d:\n", prioridade);
    for (int i = 0; i < numero_tarefas; i++) {
        if (tarefas[i].prioridade == prioridade) {
            printf("Descricao: %s\n", tarefas[i].descricao);
            printf("Categoria: %s\n", tarefas[i].categoria);
            printf("Estado: %s\n", tarefas[i].estado);
        }
    }
}