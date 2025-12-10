#ifndef POLIGONO_H
#define POLIGONO_H
#include "ponto.h"
#include "Arvore.h"

typedef void* Poligono;

Poligono criaPoligono(int n, Ponto *vertices);

void insertVertice(Poligono poligono, Ponto vertice);

void atualizaAngulosVertice(Poligono poligono, Ponto base);

int comparaVertice(const void *a, const void *b);

void ordenarVerticesPorAngulo(Poligono poligono, char ordenacao, int n);

void printVertices(Poligono poligono);

Arvore insertVerticesarvore(Arvore a, Poligono poligono);
Linha raio(Ponto bomba, Ponto v);
int orientacao(Ponto a, Ponto b, Ponto c);
int pontoNoSegmento(Ponto a, Ponto b, Ponto p);
int segmentosInterceptam(Ponto a, Ponto b, Ponto c, Ponto d);
Linha* getV(Poligono p);
int getVCount(Poligono p);
#endif