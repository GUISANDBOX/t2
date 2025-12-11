#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Lista.h"
#include "circulo.h"
#include "ponto.h"
#include "retangulo.h"
#include "linha.h"
#include "texto.h"
#include "poligono.h"

struct elemento{
    Item item;
    int tipo; // 0 - circulo, 1 retangulo, etc
    struct elemento *prox;
};

typedef struct elemento sNoItem;

void adicionar(Lista *f, Item item, int tipo){
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


Item remover(Lista *f, int *tipo) {
    sNoItem **inicio = (sNoItem **)f;

    if (*inicio == NULL) { // Evita remover de lista vazia
        printf("Lista vazia!\n");
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
        *inicio = NULL; // lista agora fica vazia
    } else {
        anterior->prox = NULL; // o penúltimo vira o último
    }

    Item removido = atual->item;
    *tipo = atual->tipo;
    free(atual); // desaloca o nó removido
    return removido;
}

void exibirlista(Lista f, FILE *arqnovo){
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

Lista crialista(){
    return NULL;
}

int listavazia(Lista l) {
    sNoItem *atual= (sNoItem *)l;
    if(atual==NULL){
        return 1;
    }
    return 0;
}

int getMaiorIdLista(Lista l) {
    sNoItem *atual= (sNoItem *)l;
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



void limpaLista(Lista *l) {
    sNoItem **inicio = (sNoItem **)l;
    sNoItem *atual = *inicio;
    sNoItem *prox;

    while (atual != NULL) {
        prox = atual->prox;
        destruirItemLista(atual->item, atual->tipo);
        free(atual);
        atual = prox;
    }

    *inicio = NULL; // Define a lista como vazia após limpar
}

void destruirItemLista(Item item, int tipo) {
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

Lista transformaAnteparo(Lista l, int i, int j, char s, Ponto vertices[], int *qtdVertices) {
    sNoItem *atual  = (sNoItem *)l;
    sNoItem *anterior = NULL;
    int id = 0;
    int novo_id = getMaiorIdLista(l) + 1;
    int num = *qtdVertices;

    while (atual != NULL) {

        if (atual->tipo == 1) { // círculo
            id = getIdCirculo((Circulo)atual->item);
            if (id >= i && id <= j) {
                atual->item = transformaAnteparoCirculo((Circulo)atual->item, novo_id++, s);
                atual->tipo = 3;
                vertices[num++] = getP1Linha((Linha)atual->item);
                vertices[num++] = getP2Linha((Linha)atual->item);
            }
            anterior = atual;
            atual = atual->prox;
        }

        else if (atual->tipo == 2) { // retângulo
            id = getIdRetangulo((Retangulo)atual->item);
            if (id >= i && id <= j) {
                char cod='o';
                if(id == -1){
                    cod = 'r';
                }

                // Guarda o próximo antes de mexer
                sNoItem *prox_old = atual->prox;

                // Aloca 4 nós, representando os 4 lados do retangulo
                sNoItem *novo1 = malloc(sizeof(sNoItem));
                sNoItem *novo2 = malloc(sizeof(sNoItem));
                sNoItem *novo3 = malloc(sizeof(sNoItem));
                sNoItem *novo4 = malloc(sizeof(sNoItem));

                // Preenche cada um
                novo1->item = transformaAnteparoRetangulo1((Retangulo)atual->item, novo_id++, cod);
                novo1->tipo = 3;
                vertices[num++] = getP1Linha((Linha)novo1->item);
                vertices[num++] = getP2Linha((Linha)novo1->item);

                novo2->item = transformaAnteparoRetangulo2((Retangulo)atual->item, novo_id++, cod);
                novo2->tipo = 3;
                vertices[num++] = getP1Linha((Linha)novo2->item);
                vertices[num++] = getP2Linha((Linha)novo2->item);

                novo3->item = transformaAnteparoRetangulo3((Retangulo)atual->item, novo_id++, cod);
                novo3->tipo = 3;
                vertices[num++] = getP1Linha((Linha)novo3->item);
                vertices[num++] = getP2Linha((Linha)novo3->item);

                novo4->item = transformaAnteparoRetangulo4((Retangulo)atual->item, novo_id++, cod);
                novo4->tipo = 3;
                vertices[num++] = getP1Linha((Linha)novo4->item);
                vertices[num++] = getP2Linha((Linha)novo4->item);

                // Liga os 4 entre si
                novo1->prox = novo2;
                novo2->prox = novo3;
                novo3->prox = novo4;
                novo4->prox = prox_old;

                // Liga com o restante da lista
                if (anterior != NULL) {
                    anterior->prox = novo1;
                } else {
                    // atual era o primeiro elemento da lista
                    l = (Lista)novo1;   // agora a cabeça é o novo1
                }

                // (Opcional) liberar o nó antigo do retângulo
                // liberaRetangulo((Retangulo)atual->item); // se tiver função
                free(atual);

                // IMPORTANTE: agora o "anterior" passa a ser o último dos novos
                anterior = novo4;
                // e o "atual" passa a ser o próximo antigo
                atual = prox_old;
            } else {
                // não transforma, só segue
                anterior = atual;
                atual = atual->prox;
            }
        }

        else if (atual->tipo == 3) { // linha
            id = getIdLinha((Linha)atual->item);
            if (id >= i && id <= j) {
                atual->item = transformaAnteparoLinha((Linha)atual->item, novo_id++);
                vertices[num++] = getP1Linha((Linha)atual->item);
                vertices[num++] = getP2Linha((Linha)atual->item);
            }
            anterior = atual;
            atual = atual->prox;
        }

        else if (atual->tipo == 4) { // texto
            id = getIdTexto((Texto)atual->item);
            if (id >= i && id <= j) {
                // ainda não faz nada
            }
            anterior = atual;
            atual = atual->prox;
        }
    }

    *qtdVertices = num;
    return l;
}

void adicionaBomba(Lista *l, Ponto centro) {
    Texto bomba = criaTexto(centro, "red", "red", ".", 'm', "cursive", "bolder", "20", 0);
    adicionar(l, (Item)bomba, 4);
}

void ativarBomba(char *comando, Lista *listaOriginal, Poligono poligono,
                 double x, double y, char *cor, double dx, double dy, char *sfx) {
    Linha *V = getV(poligono);
    sNoItem *atual = (sNoItem *)*listaOriginal;
    sNoItem *anterior = NULL;

    while (atual != NULL) {
        int bate = 0;

        if (atual->tipo == 1) {                // Círculo
            Circulo c = (Circulo)atual->item;
            bate = circuloInterceptaPoligono(c, poligono);
        }
        else if (atual->tipo == 2) {           // Retângulo
            Retangulo r = (Retangulo)atual->item;
            bate = retanguloInterceptaPoligono(r, poligono);
        }
        else if (atual->tipo == 3) {           // Linha
            Linha l = (Linha)atual->item;
            bate = linhaInterceptaPoligono(l, poligono);
        }
        else if (atual->tipo == 4) {           // Texto
            // tratar texto, se quiser
        }

        sNoItem *prox = atual->prox;  // guarda antes de mexer na lista

        if (bate && strcmp(comando, "d") == 0) {
            printf("OBJETO ATINGIDO PELA BOMBA!\n");
            printf("BOMBA DETONADA - REMOVENDO OBJETO DA LISTA\n");

            // tira 'atual' da lista
            if (anterior != NULL) {
                anterior->prox = prox;
            } else {
                // era o primeiro nó: atualiza cabeça
                *listaOriginal = (Lista)prox;
            }

            // libera o item, se tiver função específica
            // liberaCirculo/Retangulo/Linha/Text etc, dependendo de atual->tipo

            //free(atual);         // libera o nó
            // NÃO avança 'anterior' aqui, porque ele continua apontando pro anterior válido
        } else {
            // não removeu -> pode avançar 'anterior'
            anterior = atual;
        }

        if (bate && !strcmp(comando, "p")) {
            // Alterando a cor do objeto
            if (atual->tipo == 1) {                // Círculo
                setCorbCirculo((Circulo)atual->item, cor);
                setCorpCirculo((Circulo)atual->item, cor);
            }
            else if (atual->tipo == 2) {           // Retângulo
                setCorbRetangulo((Retangulo)atual->item, cor);
                setCorpRetangulo((Retangulo)atual->item, cor);
            }
            else if (atual->tipo == 3) {           // Linha
                setCorLinha((Linha)atual->item, cor);
            }
            else if (atual->tipo == 4) {           // Texto
                // tratar texto, se quiser
                setCorbTexto((Texto)atual->item, cor);
                setCorpTexto((Texto)atual->item, cor);
            }
        }

        if (bate && !strcmp(comando, "cln")) {
            // Clonando o objeto
            if (atual->tipo == 1) {                // Círculo
                Circulo c = clonecirculo((Circulo)atual->item, getMaiorIdLista(*listaOriginal) + 1);
                Ponto centro = criaPonto(getXCirculo(c) + dx, getYCirculo(c) + dy);
                
                adicionar(listaOriginal, (Item)c, 1);
            }
            else if (atual->tipo == 2) {           // Retângulo
                Retangulo r = cloneretangulo((Retangulo)atual->item, getMaiorIdLista(*listaOriginal) + 1);
                
                adicionar(listaOriginal, (Item)r, 2);
            }
            else if (atual->tipo == 3) {           // Linha
                Linha l = cloneLinha((Linha)atual->item, getMaiorIdLista(*listaOriginal) + 1);

                adicionar(listaOriginal, (Item)l, 3);
            }
            else if (atual->tipo == 4) {           // Texto
                // tratar texto, se quiser
                
            }
        }

        atual = prox;  // sempre avança usando o prox salvo
    }
}
