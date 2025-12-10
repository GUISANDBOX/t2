#ifndef ARVORE
#define ARVORE
#include "linha.h"
#include "ponto.h"

typedef void* Arvore; // Define o tipo Arvore

Arvore criaarvore();

void criaNoArvore(Arvore *a, Linha segmento, Ponto p);

int comparadirecao(Linha l, Ponto p);

void printArvore(Arvore a, int nivel);

void removeNoArvore(Arvore *a, Linha segmento, Ponto p);

int linhasIguais(Linha a, Linha b);

Arvore minNo(Arvore a);

static void segMaisProxRec(Arvore a, Ponto bomba, Ponto dir,
                           Linha *bestSeg, double *bestT, Ponto *bestY);

Linha segAtivoMaisProx(Arvore a, Ponto bomba, Ponto v, Ponto *yOut);
int encoberto(Arvore ativos, Ponto bomba, Ponto v);
double distanciaPontos(Ponto a, Ponto b);
int interseccaoRaioSegmento(Ponto origem, Ponto dir,
                            Linha seg, Ponto *pOut, double *tOut);
#endif 