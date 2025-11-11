#include<stdio.h>
#include<stdlib.h>
#include "ponto.h"

struct sPonto {
    float x;
    float y;
};

Ponto criaPonto(float x, float y) {
    struct sPonto *p = malloc(sizeof(struct sPonto));
    if (!p) return NULL; // segurança
    p->x = x;
    p->y = y;
    return (Ponto)p;
}

void printPonto(Ponto p) {
    struct sPonto *ponto = p;
    printf("(%.1f, %.1f)\n", ponto->x, ponto->y);
}

float getX(Ponto p) {
    struct sPonto *ponto = p;
    return ponto->x;
}

float getY(Ponto p) {
    struct sPonto *ponto = p;
    return ponto->y;
}