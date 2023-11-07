//
// Created by unifkapaula on 19/09/2023.
//

#ifndef UNTITLED1_BIBLIOTECA_H
#define UNTITLED1_BIBLIOTECA_H

struct tarefa {
    int prioridade;
    char descricao[300];
    char categoria[100];
    int max_caracteres[20];
};


void salvar_tarefas(struct tarefa tarefas[], int numero_tarefas);

int carregar_tarefas(struct tarefa tarefas[]);

void adicionar_tarefas(struct tarefa tarefas[], int *numero_tarefas);

void deletar_tarefas(struct tarefa tarefas[], int *numero_tarefas);

void listar_prioridade(struct tarefa tarefas[], int numero_tarefas);

void listar_tarefas(struct tarefa tarefas[], int numero_tarefas, int max_caracteres);

#endif //UNTITLED1_BIBLIOTECA_H
