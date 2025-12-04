#include "ponto.h"
#ifndef POLIGONO_H
#define POLIGONO_H

typedef void* Poligono;

Poligono criaPoligono(int n, Ponto *vertices);

void insertVertice(Poligono poligono, Ponto vertice);

void atualizaAngulosVertice(Poligono poligono, Ponto base);

int comparaAngulo(const void *a, const void *b);

void ordenarVerticesPorAngulo(Poligono poligono);

void printVertices(Poligono poligono);

#endif

