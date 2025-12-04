#include<stdio.h>
#include<stdlib.h>
#include "ponto.h"

struct sPonto {
    float x;
    float y;
    char tipo; // i ou f
    Segmento pSeg;
    char codigo; // o, a ou r
    double angulo;
};

Ponto criaPonto(float x, float y) {
    struct sPonto *p = malloc(sizeof(struct sPonto));
    if (!p) return NULL; // segurança
    p->x = x;
    p->y = y;
    p->tipo = 'i';
    p->pSeg = NULL;
    p->codigo = 'o';
    p->angulo = 0;
    return (Ponto)p;
}

void defineVerticePonto(Ponto p, char tipo, char codigo, double angulo, Segmento pSeg) {
    struct sPonto *ponto = p;
    ponto->tipo = tipo;
    ponto->codigo = codigo;
    ponto->angulo = angulo;
    ponto->pSeg = pSeg;
}

void defineAngulo(Ponto p, double ang) {
    struct sPonto *ponto = p;
    ponto->angulo = ang;
}

void printPonto(Ponto p) {
    struct sPonto *ponto = p;
    printf("(%.1f, %.1f) | [%lf, %c, %c] ", ponto->x, ponto->y, ponto->angulo, ponto->tipo, ponto->codigo);
}

float getX(Ponto p) {
    struct sPonto *ponto = p;
    return ponto->x;
}

float getY(Ponto p) {
    struct sPonto *ponto = p;
    return ponto->y;
}

double getAngulo(Ponto p) {
    struct sPonto *ponto = p;
    return ponto->angulo;
}

Segmento getSegmento(Ponto p) {
    struct sPonto *ponto = p;
    return ponto->pSeg;
}