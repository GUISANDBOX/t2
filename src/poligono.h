#include "ponto.h"
#ifndef POLIGONO_H
#define POLIGONO_H

typedef void* Poligono;

Poligono criaPoligono(int n, Ponto *vertices);

void insertVertice(Poligono poligono, Ponto vertice);

void atualizaAngulosVertice(Poligono poligono, Ponto base);
#endif

