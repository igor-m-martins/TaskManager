#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct Node {
    int id;
    char data[100];
    struct Node* prev;
    struct Node* next;
};

void insertEnd(struct Node** head_ref, int id, char* newData){
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->id = id;
    strcpy(newNode->data, newData);
    newNode->next = NULL;

    if (*head_ref == NULL) {
        newNode->prev = NULL;
        *head_ref = newNode;
        return;
    }

    struct Node* current = *head_ref;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = newNode;
    newNode->prev = current;
}

void removeNodeById(struct Node** head_ref, int id){
    if (*head_ref == NULL)
        return;

    struct Node* current = *head_ref;

    while (current != NULL && current->id != id) {
        current = current->next;
    }

    if (current == NULL) {
        printf("\n[-] Tarefa com ID %d nao encontrada.\n", id);
        return;
    }

    if (*head_ref == current) {
        *head_ref = current->next;
    }

    if (current->prev != NULL) {
        current->prev->next = current->next;
    }

    if (current->next != NULL) {
        current->next->prev = current->prev;
    }

    free(current);
    printf("\n[+] Tarefa ID %d removida com sucesso!\n", id);
}

void printList(struct Node* node){
    if (node == NULL) {
        printf("\n[!] Nenhuma tarefa cadastrada.\n");
        return;
    }

    printf("\n=== LISTA DE TAREFAS ===\n");
    while (node != NULL){
        printf("ID: %d | Tarefa: %s\n", node->id, node->data);
        node = node->next;
    }
    printf("========================\n");
}

int main(){
    struct Node* head = NULL;
    bool running = true;
    int next_id = 1;
    
    while (running == true){
        printf("\n1 - Adicionar tarefa\t2 - Exibir Tarefas\n3 - Remover Tarefa\t0 - Sair\n=> ");
        char opt_buffer[10];
        char task[100];
        int opt;
        
        fgets(opt_buffer, sizeof(opt_buffer), stdin);
        opt = atoi(opt_buffer);
        
        if (opt == 1){
            printf("\nAdicione a tarefa: ");
            fgets(task, sizeof(task), stdin);
            task[strcspn(task, "\n")] = '\0';
            insertEnd(&head, next_id, task);
            printf("\n[+] Nova tarefa adicionada com ID %d!\n", next_id);
            next_id++;
        }
        if (opt == 2){
            printList(head);
        }
        if (opt == 3){
            if (head == NULL) {
                printf("\nA lista esta vazia!\n");
                continue;
            }

            printList(head);
            char id_buffer[10];
            printf("\nDigite o ID da tarefa que deseja remover: ");
            fgets(id_buffer, sizeof(id_buffer), stdin);
            int idToRemove = atoi(id_buffer);

            removeNodeById(&head, idToRemove);
        }
        if (opt == 0){
            running = false;
        }
    }

    //libera a memoria apos finalizar
    while (head != NULL) {
        struct Node* temp = head;
        head = head->next;
        free(temp);
    }
    
    return 0;
}
