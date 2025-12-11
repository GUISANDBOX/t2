#ifndef TEXTO_H
#define TEXTO_H
#include "ponto.h"
#include <stdio.h>

//programa para textos.

typedef void* Texto;
//define o tipo Texto

Texto criaTexto(Ponto ponto, char corb[], char corp[], char txto[], char a, char currentFFamily[], char currentFWeight[], char currentFSize[], int id) ;
//cria o texto com suas informações

void printTexto(Texto t, FILE *arq);
//imprime informações do texto

Texto movetexto(Texto r, double xdisp, double ydisp, double dx, double dy);
//move o texto para uma nova posição

double getAreaTexto(Texto t);
//retorna a área do texto

double getXTexto(Texto c);
//retorna a coordenada x

double getYTexto(Texto c);
//retorna a coordenada y

Texto cloneTexto(Texto t, int novo_id);
//clona o texto

char *getCorbTexto(Texto t);
//retorna a cor de borda do texto

char *getCorpTexto(Texto t);
//retorna a cor de preenchimento do texto

void setCorbTexto(Texto t, char corb[100]);
//altera a cor de borda do texto

void setCorpTexto(Texto t, char corp[100]);
//altera a cor de preenchimento do texto

void escreveTextoTxt(Texto t, FILE *arq);
//escreve o texto em um arquivo txt

Ponto getP1Texto(Texto t);
//retorna o ponto 1 do texto

Ponto getP2Texto(Texto t);
//retorna o ponto 2 do texto

int getIdTexto(Texto t);
//retorna o id do texto

void destroiTexto(Texto t);
//libera a memória do texto

#endif