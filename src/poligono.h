#ifndef POLIGONO_H
#define POLIGONO_H
#include "ponto.h"

typedef void* Poligono;

Poligono criaPoligono(int n, Ponto *vertices);

void insertVertice(Poligono poligono, Ponto vertice);

void atualizaAngulosVertice(Poligono poligono, Ponto base);

int comparaVertice(const void *a, const void *b);

void ordenarVerticesPorAngulo(Poligono poligono, char ordenacao, int n);

void printVertices(Poligono poligono);

// Helpers geométricos
int pontoEstaDentroPoligono(Poligono poligono, Ponto p);
int segmentoIntersecionaPoligono(Linha s, Poligono poligono);

#endif

