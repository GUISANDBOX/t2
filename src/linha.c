#include "linha.h"
#include "ponto.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "Criasvg.h"

struct sLinha {
    int id;
    Ponto p1;
    Ponto p2;
    char cor[100];
};

Linha criaLinha(Ponto p1, Ponto p2, char cor[100], int id) {
    struct sLinha *l = malloc(sizeof(struct sLinha));
    if (!l) return NULL; // segurança
    l->p1 = p1;
    l->p2 = p2;
    l->id = id;
    strcpy(l->cor, cor); // Cor
    return (Linha)l;
}

Linha movelinha(Linha l, double xdisp, double ydisp, double dx, double dy) {
    struct sLinha *lin = l;
    double nx = xdisp + dx;
    double ny = ydisp + dy;

    double x1 = getX(lin->p1);
    double y1 = getY(lin->p1);
    double x2 = getX(lin->p2);
    double y2 = getY(lin->p2);

    double deltaX, deltaY;
    Ponto novoMenor, novoOutro;

    if (x1 < x2 || (x1 == x2 && y1 <= y2)) {
        /* p1 é o menor */
        deltaX = x2 - x1;
        deltaY = y2 - y1;
        novoMenor = criaPonto(nx, ny);
        novoOutro = criaPonto(nx + deltaX, ny + deltaY);
        lin->p1 = novoMenor;
        lin->p2 = novoOutro;
    }
    else {
        /* p2 é o menor */
        deltaX = x1 - x2;
        deltaY = y1 - y2;
        novoMenor = criaPonto(nx, ny);
        novoOutro = criaPonto(nx + deltaX, ny + deltaY);
        lin->p2 = novoMenor;
        lin->p1 = novoOutro;
    }   
    return lin;
}

void printLinha(Linha l, FILE *arq) {
    struct sLinha *lin = l;
    printf("\n\nID: %i\n", lin->id);
    printf("P1: (%f, %f)\n", getX(lin->p1), getY(lin->p1));
    printf("P2: (%f, %f)\n", getX(lin->p2), getY(lin->p2));
    printf("Cor: %s \n", lin->cor);
    crialinha(lin->id, getX(lin->p1), getY(lin->p1), getX(lin->p2), getY(lin->p2), lin->cor, arq);
}

double getAreaLinha(Linha l) {
    struct sLinha *lin = l;
    double dx = getX(lin->p2) - getX(lin->p1);
    double dy = getY(lin->p2) - getY(lin->p1);
    double comprimento = sqrt(dx * dx + dy * dy);
    double area = 2.0 * comprimento;  // "área" definida como 2x o comprimento
    return area;

}
//retorna a área da linha 

double getX1Linha(Linha l) {
    struct sLinha *lin = l;
    return getX(lin->p1);
}
//retorna a coordenada x do ponto 1 da linha

double getY1Linha(Linha l) {
    struct sLinha *lin = l;
    return getY(lin->p1);
}
//retorna a coordenada y do ponto 1 da linha

double getX2Linha(Linha l) {
    struct sLinha *lin = l;
    return getX(lin->p2);
}
//retorna a coordenada x do ponto 2 da linha

double getY2Linha(Linha l) {
    struct sLinha *lin = l;
    return getY(lin->p2);
}
//retorna a coordenada y do ponto 2 da linha

char* getCorLinha(Linha l) {
    struct sLinha *lin = l;
    return lin->cor;
}
//retorna a cor da linha

void setCorLinha(Linha l, char cor[]) {
    struct sLinha *lin = l;
    strcpy(lin->cor, cor);
}
//altera a cor da linha

Linha cloneLinha(Linha l, int novo_id) {
    struct sLinha *lin = l;
    Ponto p1_clone = criaPonto(getX(lin->p1), getY(lin->p1));
    Ponto p2_clone = criaPonto(getX(lin->p2), getY(lin->p2));
    Linha nova_linha = criaLinha(p1_clone, p2_clone, lin->cor, novo_id);
    return nova_linha;
}

void escreveLinhaTxt(Linha l, FILE *arq) { 
    struct sLinha *lin = l;
    fprintf(arq, "\nlinha %i\n", lin->id);
    fprintf(arq, "P1: (%f, %f)\n", getX(lin->p1), getY(lin->p1));
    fprintf(arq, "P2: (%f, %f)\n", getX(lin->p2), getY(lin->p2));
    fprintf(arq, "Cor: %s \n", lin->cor);
    fprintf(arq, "Area: %lf \n", getAreaLinha(lin));
}

int getIdLinha(Linha l) {
    struct sLinha *lin = l;
    return lin->id;
}

void destroiLinha(Linha l) {
    if (l == NULL) return;
    free(l);
}