#ifndef QRY_H
#define QRY_H

#include <stdio.h>
#include "Lista.h"
#include "retangulo.h"
#include "circulo.h"
#include "linha.h"
#include "texto.h"
#include <math.h>

void processaQry(FILE *fileq, Lista listasaida, FILE *filesaidaquery, Lista listaOriginal, FILE *arqtxt);
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

#endif