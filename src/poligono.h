#ifndef POLIGONO_H
#define POLIGONO_H
#include "ponto.h"
#include "Arvore.h"
#include "circulo.h"
#include "retangulo.h"
#include "linha.h"

typedef void* Poligono;
//define o tipo Poligono

Poligono criaPoligono(int n, Ponto *vertices);
//cria o poligono com seus vertices

void insertVertice(Poligono poligono, Ponto vertice);
//insere um vertice no poligono

void atualizaAngulosVertice(Poligono poligono, Ponto base);
//atualiza os angulos dos vertices do poligono em relacao a base

int comparaVertice(const void *a, const void *b);
//compara dois vertices para ordenação

void ordenarVerticesPorAngulo(Poligono poligono, char ordenacao, int n);
//ordena os vertices do poligono por angulo

void printVertices(Poligono poligono);
//imprime os vertices do poligono

Arvore insertVerticesarvore(Arvore a, Poligono poligono);
//insere os vertices do poligono na arvore de segmentos ativos

Linha raio(Ponto bomba, Ponto v);
//cria o raio entre a bomba e o vertice v

int orientacao(Ponto a, Ponto b, Ponto c);
//retorna a orientacao dos pontos a, b e c

int pontoNoSegmento(Ponto a, Ponto b, Ponto p);
//verifica se o ponto p esta no segmento ab

int segmentosInterceptam(Ponto a, Ponto b, Ponto c, Ponto d);
//verifica se os segmentos ab e cd se interceptam

Linha* getV(Poligono p);
//retorna o vetor de linhas do poligono

int getVCount(Poligono p);
//retorna a quantidade de linhas do vetor V do poligono

int pontoDentroPoligono(Ponto p, Poligono poligono);
//verifica se o ponto p esta dentro do poligono

int linhaInterceptaPoligono(Linha l, Poligono poligono);
//verifica se a linha l intercepta o poligono

int retanguloInterceptaPoligono(Retangulo r, Poligono poligono);
//verifica se o retangulo r intercepta o poligono

double distPontoSegmento(Ponto p, Ponto a, Ponto b);
//retorna a distancia do ponto p ao segmento ab

int circuloInterceptaPoligono(Circulo c, Poligono poligono);
//verifica se o circulo c intercepta o poligono

#endif