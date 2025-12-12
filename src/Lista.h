#ifndef LISTA
#define LISTA
#include "ponto.h"
#include "poligono.h"
#include <stdio.h>

//programa para listas.

typedef void* Item; // Define que cada item da lista é uma lista genérica
typedef void* Lista; // Define o tipo Lista

Lista crialista();
//cria a lista

void adicionar(Lista *l, Item item, int tipo);
// Adiciona um item na Lista

Item remover(Lista *l, int *tipo);
// Remove o elemento do fim da lista.

void exibirlista(Lista l, FILE *arqnovo);
//exibe os elementos da lista.

int listavazia(Lista l);
//verifica se a lista está vazia

int getMaiorIdLista(Lista l);
//retorna o maior id presente na lista

void limpaLista(Lista *l);
//limpa a lista

void destruirItemLista(Item item, int tipo);
//destrói um item da lista de acordo com seu tipo

Lista transformaAnteparo(Lista l, int i, int j, char s, Ponto *vertices, int *qtdVertices, FILE *arqtxt);
//transforma os anteparos circulos e retangulos em linhas

void adicionaBomba(Lista *l, Ponto centro, double *menorX, double *menorY, double *maiorX, double *maiorY);
//adiciona uma bomba (texto) na lista

void ativarBomba(char *comando, Lista *listaOriginal, Poligono poligono,
                 double x, double y, char *cor, double dx, double dy, char *sfx, FILE *arqtxt);
//ativa a bomba, verificando colisões e aplicando os efeitos

#endif