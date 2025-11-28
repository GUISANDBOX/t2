#ifndef GEO_H
#define GEO_H

#include <stdio.h>
#include "Lista.h"

/* Processa os comandos do arquivo .geo e adiciona os elementos na lista */
Lista processaGeo(FILE *arqgeo, Lista lista, FILE *arqsvg);

#endif