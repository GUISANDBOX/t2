#ifndef QRY_H
#define QRY_H

#include <stdio.h>
#include "Lista.h"
#include "retangulo.h"
#include "circulo.h"
#include "linha.h"
#include "texto.h"
#include <math.h>

void processaQry(FILE *fileq, FILE *filesaidaquery, Lista listaOriginal, FILE *arqtxt, char ordenacao, int n, double menorX, double menorY, double maiorX, double maiorY, char *dirsaidabase);
//processa os comandos do arquivo .qry

int linhaOuTexto(int tipo);
//verifica se o tipo é linha ou texto

Ponto getP1Item(Item item, int tipo);
//retorna o ponto 1 de um item de linha ou texto

Ponto getP2Item(Item item, int tipo);
//retorna o ponto 2 de um item de linha ou texto

double areaLinha(Item item, int tipo);
//retorna a area de um item de linha ou texto

char *getCorbLinha(Item item, int tipo);
//retorna a cor de borda de um item de linha ou texto

char *getCorpLinha(Item item, int tipo);
//retorna a cor de preenchimento de um item de linha ou texto

int getIdLinhaOuTexto(Item li, int tipo_i);
//retorna o id de um item de linha ou texto

void criarVisibilidade(char *comando, Poligono poligono, FILE *filesaidaquery, Lista *listaOriginal, double x, double y, char *cor, double dx, double dy, char *sfx, char *dirsaidabase, FILE *arqtxt);
//cria a visibilidade a partir de um polígono e ativa a bomba

#endif