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

Lista processaGeo(FILE *arqgeo, Lista lista, FILE *arqsvg, double *menorXp, double *menorYp, double *maiorXp, double *maiorYp) {
    char comando[32];
    int z, i;
    float x, y, x1, x2, y1, y2, r;
    char corb[100], corp[100], cor[100], txto[100], fFamily[100], fWeight[100], fSize[100];
    char a;
    double menorX=1000000, menorY=1000000, maiorX=-1000000, maiorY=-1000000;

    fprintf(arqsvg, "<svg xmlns:svg=\"http://www.w3.org/2000/svg\" xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\">\n");

    do {
        z = fscanf(arqgeo, " %31s", comando);
        if (z != 1) break;

        if (comando[0] == 'c') {
            fscanf(arqgeo, "%d %f %f %f %s %s", &i, &x, &y, &r, corb, corp);
            Ponto p = criaPonto(x, y);
            Circulo c = criaCirculo(p, r, corb, corp, i);
            adicionar(&lista, c, 1);
            if(x - r < menorX) menorX = x - r;
            if(y - r < menorY) menorY = y - r;
            if(x + r > maiorX) maiorX = x + r;
            if(y + r > maiorY) maiorY = y + r;
        }
        else if (comando[0] == 'r') {
            double rx, ry, rw, rh;
            fscanf(arqgeo, "%d %lf %lf %lf %lf %s %s", &i, &rx, &ry, &rw, &rh, corb, corp);
            Retangulo r = criaRetangulo(rx, ry, rw, rh, corb, corp, i);
            adicionar(&lista, r, 2);
            if(rx < menorX) menorX = rx;
            if(ry < menorY) menorY = ry;
            if(rx + rw > maiorX) maiorX = rx + rw;
            if(ry + rh > maiorY) maiorY = ry + rh;
        }
        else if (comando[0] == 'l') {
            fscanf(arqgeo, "%d %f %f %f %f %s", &i, &x1, &y1, &x2, &y2, cor);
            Ponto p1 = criaPonto(x1, y1);
            Ponto p2 = criaPonto(x2, y2);
            Linha lin = criaLinha(p1, p2, cor, i, 0);
            adicionar(&lista, lin, 3);
            if(x1 < menorX) menorX = x1;
            if(x2 < menorX) menorX = x2;
            if(y1 < menorY) menorY = y1;
            if(y2 < menorY) menorY = y2;
            if(x1 > maiorX) maiorX = x1;
            if(x2 > maiorX) maiorX = x2;
            if(y1 > maiorY) maiorY = y1;
            if(y2 > maiorY) maiorY = y2;
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
                adicionar(&lista, text, 4);
                if(x < menorX) menorX = x;
                if(y < menorY) menorY = y;
                if(x > maiorX) maiorX = x;
                if(y > maiorY) maiorY = y;
            }
        }
    } while (1);

    exibirlista(lista, arqsvg);
    fprintf(arqsvg, "</svg>\n");

    *menorXp = menorX;
    *menorYp = menorY;
    *maiorXp = maiorX;
    *maiorYp = maiorY;

    return lista;
}