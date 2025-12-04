#include "ponto.h"
#include "linha.h"
#include "poligono.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct sPoligono {
    int n;
    Ponto *vertices;
};

Poligono criaPoligono(int n, Ponto vertices[]) {
    struct sPoligono *pol = malloc(sizeof(struct sPoligono));
    pol->n = 0;
    pol->vertices = malloc(n * sizeof(Ponto));
    int i;
    for (i=0; i<n; i++) {
        insertVertice(pol, vertices[i]);
    }
    return (Poligono)pol;
}

void insertVertice(Poligono poligono, Ponto vertice) {
    struct sPoligono *pol = poligono;
    pol->vertices[pol->n] = vertice;
    pol->n = pol->n + 1;
}

void atualizaAngulosVertice(Poligono poligono, Ponto base) {
    struct sPoligono *pol = poligono;
    //printf("Angulo de %d vertices\n", pol->n);
    for (int i = 0; i < pol->n; i++) {
        if (base != NULL) {
            double dx = getX(pol->vertices[i]) - getX(base);
            double dy = getY(pol->vertices[i]) - getY(base);
            double angulo = atan2(dy, dx) * (180.0 / 3.14159265358979323846); // Convertendo para graus
            if (angulo<0) angulo += 360.0;
            defineAngulo(pol->vertices[i], angulo);
        } else {
            // Se base for NULL, apenas recalcula o ângulo em relação à origem (0,0)
            double dx = getX(pol->vertices[i]);
            double dy = getY(pol->vertices[i]);
            double angulo = atan2(dy, dx) * (180.0 / 3.14159265358979323846); // Convertendo para graus
            if (angulo<0) angulo += 360.0;
            defineAngulo(pol->vertices[i], angulo);
        }
        //printPonto(pol->vertices[i]);
    }
}

int comparaAngulo(const void *a, const void *b) {
    const Ponto *p1 = (const Ponto *)a;
    const Ponto *p2 = (const Ponto *)b;

    double ang1 = getAngulo(*p1);
    double ang2 = getAngulo(*p2);

    if (ang1 < ang2) return -1;
    if (ang1 > ang2) return 1;
    return 0;
}

void ordenarVerticesPorAngulo(Poligono poligono) {
    struct sPoligono *pol = poligono;
    qsort(pol->vertices, pol->n, sizeof(Ponto), comparaAngulo);
}

void printVertices(Poligono poligono) {
    struct sPoligono *pol = poligono;
    printf("Angulo de %d vertices\n", pol->n);
    for (int i = 0; i < pol->n; i++) {
        printPonto(pol->vertices[i]);
        Linha seg = (Linha)getSegmento(pol->vertices[i]);
        printf(" - Segmento: %i", getIdLinha(seg));
        printf("\n");
    }
}
