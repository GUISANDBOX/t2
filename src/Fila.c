#include <stdio.h>
#include <stdlib.h>
#include "Fila.h"
#include "circulo.h"
#include "retangulo.h"
#include "linha.h"
#include "texto.h"

struct elemento{
    Item item;
    int tipo; // 0 - circulo, 1 retangulo, etc
    struct elemento *prox;
};

typedef struct elemento sNoItem;

void adicionar(Fila *f, Item item, int tipo){
    sNoItem **inicio = (sNoItem **)f;

    sNoItem *novo = (sNoItem *)malloc(sizeof(sNoItem));
    if(!novo){
        printf("Erro na alocação\n");
        return;
    }

    novo->item = item;
    novo->tipo = tipo;
    novo->prox = NULL;

    // Se a lista está vazia, novo é o primeiro
    if (*inicio == NULL) {
        *inicio = novo;
        return;
    }

    // Percorre até o último
    sNoItem *atual = *inicio;
    while (atual->prox != NULL) {
        atual = atual->prox;
    }

    // Insere no final
    atual->prox = novo;
}


Item remover(Fila *f, int *tipo) {
    sNoItem **inicio = (sNoItem **)f;

    if (*inicio == NULL) { // Evita remover de fila vazia
        printf("Fila vazia!\n");
        return NULL;
    }

    sNoItem *atual = *inicio;
    sNoItem *anterior = NULL;

    // Percorre até o último nó
    while (atual->prox != NULL) {
        anterior = atual;
        atual = atual->prox;
    }

    // Se só havia um elemento
    if (anterior == NULL) {
        *inicio = NULL; // fila agora fica vazia
    } else {
        anterior->prox = NULL; // o penúltimo vira o último
    }

    Item removido = atual->item;
    *tipo = atual->tipo;
    free(atual); // desaloca o nó removido
    return removido;
}

void exibirfila(Fila f, FILE *arqnovo){
    sNoItem *atual= (sNoItem *)f;
    while(atual!=NULL){
        if (atual->tipo==1) {
            printf("\n\nCirculo:\n");
            printCirculo(atual->item, arqnovo);
        }
        else if (atual->tipo==2) {
            printf("\n\nRetangulo:\n");
            printRetangulo(atual->item, arqnovo);
        }
        else if (atual->tipo==3) {
            printf("\n\nLinha:\n");
            printLinha(atual->item, arqnovo);
        }
        else if (atual->tipo==4) {
            printf("\n\nTexto:\n");
            printTexto(atual->item, arqnovo);
        }
        atual=atual->prox;
    }
    printf("\n");
}

Fila criafila(){
    return NULL;
}

int filavazia(Fila f) {
    sNoItem *atual= (sNoItem *)f;
    if(atual==NULL){
        return 1;
    }
    return 0;
}

int getMaiorIdFIla(Fila f) {
    sNoItem *atual= (sNoItem *)f;
    int id_maior = 0;
    while(atual!=NULL){
        if (atual->tipo==1) {
            if (getIdCirculo((Circulo)atual->item) > id_maior) {
                id_maior = getIdCirculo((Circulo)atual->item);
            }
        }
        else if (atual->tipo==2) {
            if (getIdRetangulo((Retangulo)atual->item) > id_maior) {
                id_maior = getIdRetangulo((Retangulo)atual->item);
            }
        }
        else if (atual->tipo==3) {
            if (getIdLinha((Linha)atual->item) > id_maior) {
                id_maior = getIdLinha((Linha)atual->item);
            }
        }
        else if (atual->tipo==4) {
            if (getIdTexto((Texto)atual->item) > id_maior) {
                id_maior = getIdTexto((Texto)atual->item);
            }
        }
        atual=atual->prox;
    }
    return id_maior;
}



void limpaFila(Fila *f) {
    sNoItem **inicio = (sNoItem **)f;
    sNoItem *atual = *inicio;
    sNoItem *prox;

    while (atual != NULL) {
        prox = atual->prox;
        destruirItemFila(atual->item, atual->tipo);
        free(atual);
        atual = prox;
    }

    *inicio = NULL; // Define a fila como vazia após limpar
}

void destruirItemFila(Item item, int tipo) {
    switch (tipo) {
        case 1: // Circulo
            destroiCirculo((Circulo)item);
            break;
        case 2: // Retangulo
            destroiRetangulo((Retangulo)item);
            break;
        case 3: // Linha
            destroiLinha((Linha)item);
            break;
        case 4: // Texto
            destroiTexto((Texto)item);
            break;
    }
}
void transformaAnteparo(Fila f, int i, int j, char s) {
    sNoItem *atual= (sNoItem *)f;
    int id = 0;
    int novo_id = getMaiorIdFIla(f) + 1;
    while(atual!=NULL){
        if (atual->tipo==1) {
            id = getIdCirculo((Circulo)atual->item);
            if (id>=i && id<=j) {
                atual->item = transformaAnteparoCirculo((Linha)atual->item, novo_id++, s);
                atual->tipo = 3; // Muda o tipo para linha
            }
        }
        else if (atual->tipo==2) {
            id = getIdRetangulo((Retangulo)atual->item);
            if (id>=i && id<=j) {
                
            }
        }
        else if (atual->tipo==3) {
            id = getIdLinha((Linha)atual->item);
            if (id>=i && id<=j) {
                atual->item = transformaAnteparoLinha((Linha)atual->item, novo_id++);
            }
        }
        else if (atual->tipo==4) {
            id = getIdTexto((Texto)atual->item);
            if (id>=i && id<=j) {
                
            }
        }
        atual=atual->prox;
        
    }
    return;
}