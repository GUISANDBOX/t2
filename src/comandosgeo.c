#include "comandosgeo.h"
#include "ponto.h"
#include "circulo.h"
#include "retangulo.h"
#include "linha.h"
#include "texto.h"
#include <string.h>

static char currentFFamily[100] = "sans";
static char currentFWeight[100] = "normal";
static char currentFSize[100] = "12"; 

Fila processaGeo(FILE *arqgeo, Fila fila, FILE *arqsvg) {
    char comando[32];
    int z, i;
    float x, y, x1, x2, y1, y2, r;
    char corb[100], corp[100], cor[100], txto[100], fFamily[100], fWeight[100], fSize[100];
    char a;

    fprintf(arqsvg, "<svg xmlns:svg=\"http://www.w3.org/2000/svg\" xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\">\n");

    do {
        z = fscanf(arqgeo, " %31s", comando);
        if (z != 1) break;

        if (comando[0] == 'c') {
            fscanf(arqgeo, "%d %f %f %f %s %s", &i, &x, &y, &r, corb, corp);
            Ponto p = criaPonto(x, y);
            Circulo c = criaCirculo(p, r, corb, corp, i);
            adicionar(&fila, c, 1);
        }
        else if (comando[0] == 'r') {
            double rx, ry, rw, rh;
            fscanf(arqgeo, "%d %lf %lf %lf %lf %s %s", &i, &rx, &ry, &rw, &rh, corb, corp);
            Retangulo r = criaRetangulo(rx, ry, rw, rh, corb, corp, i);
            adicionar(&fila, r, 2);
        }
        else if (comando[0] == 'l') {
            fscanf(arqgeo, "%d %f %f %f %f %s", &i, &x1, &y1, &x2, &y2, cor);
            Ponto p1 = criaPonto(x1, y1);
            Ponto p2 = criaPonto(x2, y2);
            Linha lin = criaLinha(p1, p2, cor, i, 0);
            adicionar(&fila, lin, 3);
        }
        else if (comando[0] == 't') {
            if (comando[1] == 's') {
                fscanf(arqgeo, "%s %s %s", fFamily, fWeight, fSize);
                if (strcmp(fWeight, "n") == 0) strcpy(fWeight, "normal");
                else if (strcmp(fWeight, "b") == 0) strcpy(fWeight, "bold");
                else if (strcmp(fWeight, "b+") == 0) strcpy(fWeight, "bolder");
                else if (strcmp(fWeight, "l") == 0) strcpy(fWeight, "lighter");
                strcpy(currentFFamily, fFamily);
                strcpy(currentFWeight, fWeight);
                strcpy(currentFSize, fSize);
            }
            else {
                fscanf(arqgeo, "%d %f %f %s %s %c", &i, &x, &y, corb, corp, &a);
                fgets(txto, sizeof(txto), arqgeo);
                Ponto pt = criaPonto(x, y);
                Texto text = criaTexto(pt, corb, corp, txto, a, currentFFamily, currentFWeight, currentFSize, i);
                adicionar(&fila, text, 4);
            }
        }
    } while (1);

    exibirfila(fila, arqsvg);
    fprintf(arqsvg, "</svg>\n");
    return fila;
}