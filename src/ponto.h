#ifndef PONTO_H
#define PONTO_H
//programa para pontos.

typedef void* Ponto;
//define o tipo Ponto

typedef void *Segmento;
//define o tipo Segmento

Ponto criaPonto(float x, float y);
//cria o ponto com suas informações

void printPonto(Ponto p);
//imprime as informações do ponto

float getX(Ponto p);
//retorna a coordenada x do ponto

float getY(Ponto p);
//retorna a coordenada y do ponto

void defineVerticePonto(Ponto p, char tipo, char codigo, double angulo, Segmento pSeg);
//define as informações do ponto vertice

void defineAngulo(Ponto p, double ang);
//define o angulo do ponto

double getAngulo(Ponto p);
//retorna o angulo do ponto

Segmento getSegmento(Ponto p);
//retorna o segmento associado ao ponto

char gettipoPonto(Ponto p);
//retorna o tipo do ponto

#endif