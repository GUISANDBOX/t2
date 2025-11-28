#include "retangulo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Criasvg.h"
#include "linha.h"
#include "ponto.h"

struct sRetangulo {
    int id;
    double x;
    double y;
    double w;
    double h;
    char corb[100];
    char corp[100];
};

Retangulo criaRetangulo(double x, double y, double w, double h, char corb[100], char corp[100], int id) {
    struct sRetangulo *r = malloc(sizeof(struct sRetangulo));
    r->id = id;
    r->x = x;
    r->y = y;
    r->w = w;
    r->h = h;
    strcpy(r->corb, corb); // Cor da borda
    strcpy(r->corp, corp); // Cor de preenchimento
    return r;
}

Retangulo moveretangulo(Retangulo r, double xdisp, double ydisp, double dx, double dy) {
    struct sRetangulo *ret = r;
    ret->x = xdisp + dx;
    ret->y = ydisp + dy;
    return ret;
}

void printRetangulo(Retangulo r, FILE *arq) {
    struct sRetangulo *ret = r;
    printf("\n\nID: %i\n", ret->id);
    printf("Ancora: %lf %lf\n", ret->x, ret->y);
    printf("Largura/altura: %lf %lf\n", ret->w, ret->h);
    printf("Cores borda/preenchimento: %s/%s \n", ret->corb, ret->corp);
    printf("Área: %.2f \n", areaRetangulo(r));
    if (arq!=NULL) criaretangulo(ret->id, ret->x, ret->y, ret->w, ret->h, ret->corb, ret->corp, arq);
}

double areaRetangulo(Retangulo r) {
    struct sRetangulo *ret = r;
    return ret->w * ret->h;
}

double getXRetangulo(Retangulo r) {
    struct sRetangulo *ret = r;
    return ret->x;
}
//retorna a coordenada x do retângulo  


double getYRetangulo(Retangulo r) {
    struct sRetangulo *ret = r;
    return ret->y;
}
//retorna a coordenada y do retângulo


double getWRetangulo(Retangulo r)  {
    struct sRetangulo *ret = r;
    return ret->w;
}
//retorna a largura do retângulo


double getHRetangulo(Retangulo r) {
    struct sRetangulo *ret = r;
    return ret->h;
}
//retorna a altura do retângulo

int getIdRetangulo(Retangulo r) {
    struct sRetangulo *ret = r;
    return ret->id;
}
//retorna o id do retângulo

char* getCorbRetangulo(Retangulo r) {
    struct sRetangulo *ret = r;
    return ret->corb;
}
//retorna a cor de borda do retângulo

char* getCorpRetangulo(Retangulo r) {
    struct sRetangulo *ret = r;
    return ret->corp;
}
//retorna a cor de preenchimento do retângulo

void setCorbRetangulo(Retangulo r, char corb[100]) {
    struct sRetangulo *ret = r;
    strcpy(ret->corb, corb);
}
//altera a cor de borda do retângulo

void setCorpRetangulo(Retangulo r, char corp[100]) {
    struct sRetangulo *ret = r;
    strcpy(ret->corp, corp);
}
//altera a cor de preenchimento do retângulo

Retangulo cloneretangulo(Retangulo r, int id_novo) {
    struct sRetangulo *ret = r;
    return criaRetangulo(ret->x, ret->y, ret->w, ret->h, ret->corb, ret->corp, id_novo);
}

void escreveRetanguloTxt(Retangulo r, FILE *arq) {
    struct sRetangulo *ret = r;
    fprintf(arq, "retangulo  %d\n", ret->id);
    fprintf(arq, "ancora: (%.2lf, %.2lf)\n", ret->x, ret->y);
    fprintf(arq, "largura: %.2lf\natura: %.2lf\n", ret->w, ret->h);
    fprintf(arq, "borda: %s\n", ret->corb);
    fprintf(arq, "preenchimento: %s\n", ret->corp);
    fprintf(arq, "area: %.2f\n", areaRetangulo(r));
    fprintf(arq, "\n");
}

void destroiRetangulo(Retangulo r) {
    if (r == NULL) return;
    free(r);
}

Linha transformaAnteparoRetangulo1(Retangulo r, int novo_id, char codigo) {
    struct sRetangulo *ret = r;
    Ponto p1 = criaPonto(ret->x, ret->y);
    Ponto p2 = criaPonto(ret->x + ret->w, ret->y);
    Linha anteparo = criaLinha(p1, p2, getCorbRetangulo(r), novo_id, 1);
    defineVerticePonto(p1, 'i', codigo, 0, anteparo);
    defineVerticePonto(p2, 'f', codigo, 0, anteparo);
    return anteparo;
}

Linha transformaAnteparoRetangulo2(Retangulo r, int novo_id, char codigo) {
    struct sRetangulo *ret = r;
    Ponto p1 = criaPonto(ret->x + ret->w, ret->y);
    Ponto p2 = criaPonto(ret->x + ret->w, ret->y + ret->h);
    Linha anteparo = criaLinha(p1, p2, getCorbRetangulo(r), novo_id, 1);
    defineVerticePonto(p1, 'i', codigo, 0, anteparo);
    defineVerticePonto(p2, 'f', codigo, 0, anteparo);
    return anteparo;
}
Linha transformaAnteparoRetangulo3(Retangulo r, int novo_id, char codigo) {
    struct sRetangulo *ret = r;
    Ponto p1 = criaPonto(ret->x + ret->w, ret->y + ret->h);
    Ponto p2 = criaPonto(ret->x, ret->y + ret->h);
    Linha anteparo = criaLinha(p1, p2, getCorbRetangulo(r), novo_id, 1);
    defineVerticePonto(p1, 'i', codigo, 0, anteparo);
    defineVerticePonto(p2, 'f', codigo, 0, anteparo);
    return anteparo;
}

Linha transformaAnteparoRetangulo4(Retangulo r, int novo_id, char codigo) {
    struct sRetangulo *ret = r;
    Ponto p1 = criaPonto(ret->x, ret->y + ret->h);
    Ponto p2 = criaPonto(ret->x, ret->y);
    Linha anteparo = criaLinha(p1, p2, getCorbRetangulo(r), novo_id, 1);
    defineVerticePonto(p1, 'i', codigo, 0, anteparo);
    defineVerticePonto(p2, 'f', codigo, 0, anteparo);
    return anteparo;
}
