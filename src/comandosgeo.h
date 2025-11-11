#ifndef GEO_H
#define GEO_H

#include <stdio.h>
#include "Fila.h"

/* Processa os comandos do arquivo .geo e adiciona os elementos na fila */
Fila processaGeo(FILE *arqgeo, Fila fila, FILE *arqsvg);

#endif