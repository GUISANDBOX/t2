#include "ponto.h"
#include "linha.h"
#include "poligono.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Mergesort.h"

Ponto bomba;

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
    bomba=base;
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

int comparaVertice(const void *a, const void *b) {
    const Ponto *p1 = (const Ponto *)a;
    const Ponto *p2 = (const Ponto *)b;

    double ang1 = getAngulo(*p1);
    double ang2 = getAngulo(*p2);

    if (ang1 < ang2) return -1;
    if (ang1 > ang2) return 1;
    if (ang1 == ang2) {
        // Se os ângulos forem iguais, ordenar pela distância ao ponto base (bomba)
        double dx1 = getX(*p1) - getX(bomba);
        double dy1 = getY(*p1) - getY(bomba);
        double dist1 = sqrt(dx1 * dx1 + dy1 * dy1);

        double dx2 = getX(*p2) - getX(bomba);
        double dy2 = getY(*p2) - getY(bomba);
        double dist2 = sqrt(dx2 * dx2 + dy2 * dy2);

        if (dist1 < dist2) return 1;
        if (dist1 > dist2) return -1;
        if (dist1 == dist2) {
            if (gettipoPonto(*p1) == 'i' && gettipoPonto(*p2) == 'f') return -1;
            if (gettipoPonto(*p1) == 'f' && gettipoPonto(*p2) == 'i') return 1;
            if (gettipoPonto(*p1) == gettipoPonto(*p2)) return 0;
        }
    }
    return 0;
}

void ordenarVerticesPorAngulo(Poligono poligono, char ordenacao, int n) {
    struct sPoligono *pol = poligono;
    if(ordenacao == 'q'){
        qsort(pol->vertices, pol->n, sizeof(Ponto), comparaVertice);
        return;
    }
    else{
        MergeSort(pol->vertices, 0, pol->n - 1, n);
    }
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