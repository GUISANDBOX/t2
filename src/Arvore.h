#ifndef ARVORE
#define ARVORE
#include "linha.h"
#include "ponto.h"

//programa para árvore de segmentos ativos.

typedef void* Arvore; // Define o tipo Arvore

Arvore criaarvore();
//cria a árvore

void criaNoArvore(Arvore *a, Linha segmento, Ponto p);
//cria um nó na árvore

int comparadirecao(Linha l, Ponto p);
//compara a direção de uma linha em relação a um ponto

void printArvore(Arvore a, int nivel);
//imprime a árvore

void removeNoArvore(Arvore *a, Linha segmento, Ponto p);
//remove um nó da árvore

int linhasIguais(Linha a, Linha b);
//compara se duas linhas são iguais

Arvore minNo(Arvore a);
//retorna o nó com o menor valor da árvore

static void segMaisProxRec(Arvore a, Ponto bomba, Ponto dir,
                           Linha *bestSeg, double *bestT, Ponto *bestY);
                           //função recursiva para encontrar o segmento ativo mais próximo

Linha segAtivoMaisProx(Arvore a, Ponto bomba, Ponto v, Ponto *yOut);
//retorna o segmento ativo mais próximo ao raio

int encoberto(Arvore ativos, Ponto bomba, Ponto v);
//verifica se o ponto v está encoberto por algum segmento ativo

double distanciaPontos(Ponto a, Ponto b);
//retorna a distância entre dois pontos

int interseccaoRaioSegmento(Ponto origem, Ponto dir,
                            Linha seg, Ponto *pOut, double *tOut);
//verifica a interseção entre o raio e um segmento

#endif 