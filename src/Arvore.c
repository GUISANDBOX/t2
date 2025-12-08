#include "linha.h"
#include "Arvore.h"
#include <stdio.h>
#include <stdlib.h>

struct noarvore{
    Linha segmento;
    struct noarvore *esq;
    struct noarvore *dir;
};

typedef struct noarvore sNoArvore;

Arvore criaarvore(){
    return NULL;
}

void criaNoArvore(Arvore *a, Linha segmento, Ponto p){
    if(*a == NULL){
        sNoArvore *novo = malloc(sizeof(sNoArvore));
        if (!novo) {
            printf("Erro na alocação\n");
            return;
        }
        novo->segmento = segmento;
        novo->esq = NULL;
        novo->dir = NULL;
        *a = novo;
        return;
    }
    sNoArvore *atual = *a;
    int cmp = comparadirecao(atual->segmento, p);
    if(cmp > 0){
        criaNoArvore(&(atual->esq), segmento, p);
    }
    else{
        criaNoArvore(&(atual->dir), segmento, p);
    }
}

int comparadirecao(Linha l, Ponto p){
    double xponto = getX(p);
    double yponto = getY(p);
    double x1linha = getX1Linha(l);
    double y1linha = getY1Linha(l);
    double x2linha = getX2Linha(l);
    double y2linha = getY2Linha(l);
    double D = (x1linha*y2linha*1 + x2linha*1*xponto + 1*y1linha*yponto) - (1*y2linha*xponto + x1linha*1*yponto + x2linha*y1linha*1);
    if(D > 0){
        return 1; // ponto está à esquerda da linha
    }
    else if(D < 0){
        return -1; // ponto está à direita da linha
    }
    else{
        return 0; // ponto está sobre a linha
    }
}