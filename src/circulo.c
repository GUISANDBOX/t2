#include "circulo.h"
#include "ponto.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Criasvg.h"
#include "linha.h"

struct sCirculo {
    int id;
    Ponto centro;
    float raio;
    char corb[100];
    char corp[100];
};

Circulo criaCirculo(Ponto centro, float raio, char corb[100], char corp[100], int id) {
    struct sCirculo *c = malloc(sizeof(struct sCirculo));
    if (!c) return NULL; // segurança
    c->centro = centro;
    c->raio = raio;
    c->id = id;
    strcpy(c->corb, corb); // Cor da borda
    strcpy(c->corp, corp); // Cor de preenchimento
    return (Circulo)c;
}

Circulo movecirculo(Circulo c, double xdisp, double ydisp, double dx, double dy) {
    struct sCirculo *circ = c;
    double nx = xdisp + dx;
    double ny = ydisp + dy;
    Ponto novo = criaPonto(nx, ny);
    circ->centro = novo;
    return circ;
}

void printCirculo(Circulo c, FILE *arq) {
    struct sCirculo *circ = c;
    printf("\n\nID: %i\n", circ->id);
    printf("Centro: (%f, %f)\n", getX(circ->centro), getY(circ->centro));
    printf("Raio: %.1f \n", circ->raio);
    printf("Cores borda/preenchimento: %s/%s \n", circ->corb, circ->corp);
    printf("Área: %.2f \n", areaCirculo(c));
    if (arq!=NULL) criacirculo(circ->id, getX(circ->centro), getY(circ->centro), circ->raio, circ->corb, circ->corp, arq);
}

double areaCirculo(Circulo c) {
    struct sCirculo *circ = c;
    return 3.14159265358979323846 * circ->raio * circ->raio;
}

double getXCirculo(Circulo c) {
    struct sCirculo *circ = c;
    return getX(circ->centro);
}
//retorna a coordenada x do círculo

double getYCirculo(Circulo c) {
    struct sCirculo *circ = c;
    return getY(circ->centro);
}
//retorna a coordenada y do círculo

double getRCirculo(Circulo c) {
    struct sCirculo *circ = c;
    return circ->raio;
}
//retorna o raio do círculo

void setCorbCirculo(Circulo c, char corb[100]) {
    struct sCirculo *circ = c;
    strcpy(circ->corb, corb);
}
//altera a cor da borda do círculo

Circulo clonecirculo(Circulo c, int novo_id) {
    struct sCirculo *circ = c;
    Ponto centro_clone = criaPonto(getX(circ->centro), getY(circ->centro));
    Circulo novo = criaCirculo(centro_clone, circ->raio, circ->corp, circ->corb, novo_id);
    return novo;
}

int getIdCirculo(Circulo c) {
    struct sCirculo *circ = c;
    return circ->id;
}
//retorna o id do círculo

char* getCorbCirculo(Circulo c) {
    struct sCirculo *circ = c;
    return circ->corb;
}
//retorna a cor de borda do círculo

char* getCorpCirculo(Circulo c) {
    struct sCirculo *circ = c;
    return circ->corp;
}
//retorna a cor de preenchimento do círculo

void setCorpCirculo(Circulo c, char corp[100]) {
    struct sCirculo *circ = c;
    strcpy(circ->corp, corp);
}
//altera a cor de preenchimento do círculo

void escreveCirculoTxt(Circulo c, FILE *arq) {
    struct sCirculo *circ = c;
    fprintf(arq, "\ncirculo %i\n", circ->id);
    fprintf(arq, "ancora em (%f, %f)\n", getX(circ->centro), getY(circ->centro));
    fprintf(arq, "raio: %.1f \n", circ->raio);
    fprintf(arq, "borda: %s \n", circ->corb);
    fprintf(arq, "preenchimento: %s \n", circ->corp);
    fprintf(arq, "area: %.2f \n", areaCirculo(c));
}

void destroiCirculo(Circulo c) {
    if (c == NULL) return;
    free(c);
}

Linha transformaAnteparoCirculo(Circulo c, int novo_id, char modo) {
    struct sCirculo *circ = c;
    Ponto p1, p2;
    if (modo=='h') {
        p1 = criaPonto(getXCirculo(c)-circ->raio, getYCirculo(c));
        p2 = criaPonto(getXCirculo(c)+circ->raio, getYCirculo(c));
    }
    else {
        p1 = criaPonto(getXCirculo(c), getYCirculo(c)-circ->raio);
        p2 = criaPonto(getXCirculo(c), getYCirculo(c)+circ->raio);
    }
    Linha anteparo = criaLinha(p1, p2, circ->corb, novo_id, 1);
    defineVerticePonto(p1, 'i', 'o', 0, anteparo);
    defineVerticePonto(p2, 'f', 'o', 0, anteparo);
    return anteparo;
}