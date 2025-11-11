#ifndef RET_H
#define RET_H
#include<stdio.h>

//programa para retângulos.

typedef void *Retangulo;

Retangulo criaRetangulo(double x, double y, double w, double h, char corb[100], char corp[100], int id);
//cria o retângulo com suas informações

void printRetangulo(Retangulo r, FILE *arq);
//imprime as informações do retângulo

Retangulo moveretangulo(Retangulo r, double xdisp, double ydisp, double dx, double dy);
//move o retângulo para uma nova posição

double areaRetangulo(Retangulo r);
//calcula a área do retângulo

double areaRetangulo(Retangulo r);
//calcula a área do retângulo

double getXRetangulo(Retangulo r);
//retorna a coordenada x do retângulo  

double getYRetangulo(Retangulo r);
//retorna a coordenada y do retângulo

double getWRetangulo(Retangulo r);
//retorna a largura do retângulo

double getHRetangulo(Retangulo r);
//retorna a altura do retângulo

int getIdRetangulo(Retangulo r);
//retorna o id do retângulo

char* getCorbRetangulo(Retangulo r);
//retorna a cor de borda do retângulo

char* getCorpRetangulo(Retangulo r);
//retorna a cor de preenchimento do retângulo

void setCorbRetangulo(Retangulo r, char corb[100]);
//altera a cor de borda do retângulo

void setCorpRetangulo(Retangulo r, char corp[100]);
//altera a cor de preenchimento do retângulo

Retangulo cloneretangulo(Retangulo r, int id_novo);
//clona o retângulo

void escreveRetanguloTxt(Retangulo r, FILE *arq);
//escreve o retângulo em um arquivo txt

void destroiRetangulo(Retangulo r);
//libera memória do retângulo

#endif