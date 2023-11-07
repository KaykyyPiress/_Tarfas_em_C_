#ifndef UNTITLED1_BIBLIOTECA_H
#define UNTITLED1_BIBLIOTECA_H

struct tarefa {
    int prioridade;
    char descricao[300];
    char categoria[100];
    char estado[20]; // New field for task state
};

void salvar_tarefas(struct tarefa tarefas[], int numero_tarefas);

int carregar_tarefas(struct tarefa tarefas[]);

void adicionar_tarefas(struct tarefa tarefas[], int *numero_tarefas);

void deletar_tarefas(struct tarefa tarefas[], int *numero_tarefas);

void alterar_tarefas(struct tarefa tarefas[], int numero_tarefas);

void listar_prioridade(struct tarefa tarefas[], int numero_tarefas);

void listar_tarefas(struct tarefa tarefas[], int numero_tarefas, int max_caracteres);

#endif //UNTITLED1_BIBLIOTECA_H