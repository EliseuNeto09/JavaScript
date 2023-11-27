#include <stdio.h>
#include <stdlib.h>


typedef struct Node {
    int dados;
    struct Node* proximo;
} Node;


void push(Node** topo, int novodados) {
    Node* novoNode = (Node*)malloc(sizeof(Node));
    novoNode->dados = novodados;
    novoNode->proximo = *topo;
    *topo = novoNode;
}


void printList(Node* topo) {
    Node* atual = topo;
    while (atual != NULL) {
        printf("%d ", atual->dados);
        atual = atual->proximo;
    }
    printf("\n");
}


void invertList(Node** topo) {
    Node* anterior = NULL;
    Node* atual = *topo;
    Node* proximo = NULL;

    while (atual != NULL) {
        proximo = atual->proximo; 
        atual->proximo = anterior; 
        anterior = atual;        
        atual = proximo;        
    }

    *topo = anterior; 
}


int main() {
    Node* topo = NULL;

    
    push(&topo, 1);
    push(&topo, 2);
    push(&topo, 3);
    push(&topo, 4);

    printf("Lista original: ");
    printList(topo);

    
    invertList(&topo);

    printf("Lista invertida: ");
    printList(topo);

    return 0;
}
