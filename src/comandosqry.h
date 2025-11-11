#ifndef QRY_H
#define QRY_H

#include <stdio.h>
#include "Fila.h"
#include "Pilha.h"
#include "disparador.h"
#include "retangulo.h"
#include "circulo.h"
#include "linha.h"
#include "texto.h"
#include <math.h>

void processaQry(FILE *fileq, Fila filasaida, FILE *filesaidaquery, Fila filaOriginal, FILE *arqtxt);
//processa os comandos do arquivo .qry

int retangulosSobrepoem(Retangulo r1, Retangulo r2);
//verifica se dois retângulos se sobrepoem

int circulosSobrepoem(Circulo c1, Circulo c2);
//verifica se dois círculos se sobrepoem

int circuloRetanguloSobrepoem(Circulo c, Retangulo r);
//verifica se um círculo e um retângulo se sobrepoem

Fila executaCalc(Fila filasaida, Fila filaOriginal, FILE *filesaidaquery, FILE *arqtxt, int *totaldeformasesmagadas, int *totaldeformasclonadas, double *pontuacaofinal);
//executa a função calc
 
int linhasSobrepoem(Item l1, Item l2, int tipo1, int tipo2);
//verifica se duas linhas/textos se sobrepoem

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

int retanguloLinhaSobrepoem(Retangulo r, Item l, int tipo_l);
//verifica se um retângulo e uma linha/texto se sobrepoem

int circuloLinhaSobrepoem(Circulo c, Item l, int tipo_l);
//verifica se um círculo e uma linha/texto se sobrepoem

int getIdLinhaOuTexto(Item li, int tipo_i);
//retorna o id de um item de linha ou texto

#endif