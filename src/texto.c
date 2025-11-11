#include "texto.h"
#include "ponto.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Criasvg.h"

struct sTexto {
    int id;
    Ponto ponto;
    char corb[100];
    char corp[100];
    char txto[100];
    char ancora;
    char currentFFamily[10];
    char currentFWeight[10];
    char currentFSize[10];
};

Texto criaTexto(Ponto ponto, char corb[], char corp[], char txto[], char a, char currentFFamily[], char currentFWeight[], char currentFSize[], int id) {
    struct sTexto *t = malloc(sizeof(struct sTexto));
    if (!t) return NULL; // segurança
    t->ponto = ponto;
    t->id = id;
    t->ancora = a;
    strcpy(t->corb, corb); // Cor da borda
    strcpy(t->corp, corp); // Cor de preenchimento
    strcpy(t->txto, txto); // Texto
    strcpy(t->currentFFamily, currentFFamily);
    strcpy(t->currentFWeight, currentFWeight);
    strcpy(t->currentFSize, currentFSize);
    return (Texto)t;
}

Texto movetexto(Texto t, double xdisp, double ydisp, double dx, double dy) {
    struct sTexto *tex = t;
    double nx = xdisp + dx;
    double ny = ydisp + dy;
    Ponto novo = criaPonto(nx, ny);
    tex->ponto = novo;
    return tex;
}

void printTexto(Texto t, FILE *arq) {
    struct sTexto *tex = t;
    printf("\n\nID: %i\n", tex->id);
    printf("Âncora: (%f, %f)\n", getX(tex->ponto), getY(tex->ponto));
    printf("Cores borda/preenchimento: %s/%s \n", tex->corb, tex->corp);
    printf("Texto: %s \n", tex->txto);
    printf("Família/Peso/Tamanho: %s/%s/%s \n", tex->currentFFamily, tex->currentFWeight, tex->currentFSize);
    criatexto(tex->id, getX(tex->ponto), getY(tex->ponto), tex->corb, tex->corp, tex->ancora, tex->txto, tex->currentFFamily, tex->currentFWeight, tex->currentFSize, arq);
}

double getAreaTexto(Texto t) {
    struct sTexto *tex = t;
    return 20*strlen(tex->txto);
}
//retorna a área do texto

double getXTexto(Texto c) {
    struct sTexto *tex = c;
    return getX(tex->ponto);
}
//retorna a coordenada x

double getYTexto(Texto c) {
    struct sTexto *tex = c;
    return getY(tex->ponto);
}
//retorna a coordenada y

Texto cloneTexto(Texto t, int novo_id) {
    struct sTexto *tex = t;
    Ponto ponto_clone = criaPonto(getX(tex->ponto), getY(tex->ponto));
    Texto novo_texto = criaTexto(ponto_clone, tex->corp, tex->corb, tex->txto, tex->ancora, tex->currentFFamily, tex->currentFWeight, tex->currentFSize, novo_id);
    return novo_texto;
}

char *getCorbTexto(Texto t) {
    struct sTexto *tex = t;
    return tex->corb;
}
//retorna a cor de borda do texto

char *getCorpTexto(Texto t) {
    struct sTexto *tex = t;
    return tex->corp;
}
//retorna a cor de preenchimento do texto

void setCorbTexto(Texto t, char corb[100]) {
    struct sTexto *tex = t;
    strcpy(tex->corb, corb);
}
//altera a cor de borda do texto

void setCorpTexto(Texto t, char corp[100]) {
    struct sTexto *tex = t;
    strcpy(tex->corp, corp);
}
//altera a cor de preenchimento do texto

void escreveTextoTxt(Texto t, FILE *arq) {
    struct sTexto *tex = t;
    fprintf(arq, "\ntexto %i\n", tex->id);
    fprintf(arq, "Âncora: (%f, %f)\n", getX(tex->ponto), getY(tex->ponto));
    fprintf(arq, "Cores borda/preenchimento: %s/%s \n", tex->corb, tex->corp);
    fprintf(arq, "Texto: %s \n", tex->txto);
    fprintf(arq, "Família/Peso/Tamanho: %s/%s/%s \n", tex->currentFFamily, tex->currentFWeight, tex->currentFSize);
    fprintf(arq, "Area: %lf \n", getAreaTexto(tex));
}

Ponto getP1Texto(Texto t) {
    struct sTexto *tex = t;
    int comp = strlen(tex->txto);
    double xt = getX(tex->ponto);
    double yt = getY(tex->ponto);
    if (tex->ancora == 'i') {
        return criaPonto(xt, yt);
    } else if (tex->ancora == 'f') {
        return criaPonto( xt - 10.0 * comp, yt);
    } else if (tex->ancora == 'm') {
        return criaPonto(xt - 10.0 * comp/2, yt);
    }
}

Ponto getP2Texto(Texto t) {
    struct sTexto *tex = t;
    int comp = strlen(tex->txto);
    double xt = getX(tex->ponto);
    double yt = getY(tex->ponto);
    if (tex->ancora == 'i') {
        return criaPonto(xt + 10.0 * comp, yt);
    } else if (tex->ancora == 'f') {
        return criaPonto(xt, yt);
    } else if (tex->ancora == 'm') {
        return criaPonto(xt + 10.0 * comp/ 2, yt);
    }
}

int getIdTexto(Texto t) {
    struct sTexto *tex = t;
    return tex->id;
}

void destroiTexto(Texto t) {
    if (t == NULL) return;
    free(t);
}