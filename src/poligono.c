#include "ponto.h"
#include "linha.h"
#include "poligono.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Mergesort.h"
#include "Arvore.h"

Ponto bomba;

struct sPoligono {
    int n;
    Ponto *vertices;
    Linha V[10000];
    int vcount;
};

Linha* getV(Poligono p) {
    struct sPoligono *pol = (struct sPoligono*)p;
    return pol->V;
}

int getVCount(Poligono p) {
    struct sPoligono *pol = (struct sPoligono*)p;
    return pol->vcount;
}

Poligono criaPoligono(int n, Ponto vertices[]) {
    struct sPoligono *pol = malloc(sizeof(struct sPoligono));
    pol->n = 0;
    pol->vertices = malloc(n * sizeof(Ponto));
    pol->vcount = 0;
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

Linha raio(Ponto bomba, Ponto v) {
    return criaLinha(bomba, v, "white", 0, 0);
}

int orientacao(Ponto a, Ponto b, Ponto c) {
    double ax = getX(a), ay = getY(a);
    double bx = getX(b), by = getY(b);
    double cx = getX(c), cy = getY(c);

    double val = (bx - ax) * (cy - ay) - (by - ay) * (cx - ax);

    if (val > 0)  return 1;
    if (val < 0)  return -1;
    return 0;
}

int pontoNoSegmento(Ponto a, Ponto b, Ponto p) {
    double ax = getX(a), ay = getY(a);
    double bx = getX(b), by = getY(b);
    double px = getX(p), py = getY(p);

    return (px >= fmin(ax, bx) && px <= fmax(ax, bx) &&
            py >= fmin(ay, by) && py <= fmax(ay, by));
}

int segmentosInterceptam(Ponto a, Ponto b, Ponto c, Ponto d) {
    int o1 = orientacao(a, b, c);
    int o2 = orientacao(a, b, d);
    int o3 = orientacao(c, d, a);
    int o4 = orientacao(c, d, b);

    if (o1 != o2 && o3 != o4)
        return 1;

    if (o1 == 0 && pontoNoSegmento(a, b, c)) return 1;
    if (o2 == 0 && pontoNoSegmento(a, b, d)) return 1;
    if (o3 == 0 && pontoNoSegmento(c, d, a)) return 1;
    if (o4 == 0 && pontoNoSegmento(c, d, b)) return 1;

    return 0;
}

Arvore insertVerticesarvore(Arvore ativos, Poligono poligono){
    struct sPoligono *pol = poligono;
    Ponto biombo = pol->vertices[0];     // s0.ini na figura

    for (int i = 0; i < pol->n; i++) {
        if(gettipoPonto(pol->vertices[i])=='i'){
            Linha seg = (Linha)getSegmento(pol->vertices[i]);
            criaNoArvore(&ativos,seg,pol->vertices[i]);
            if (!encoberto(ativos, bomba, pol->vertices[i])) {
                Ponto y;
                Linha s = segAtivoMaisProx(ativos, bomba, pol->vertices[i], &y);

                // insira [biombo, y] em V
                Linha l1 = criaLinha(biombo, y,"gray", 0, 1);
                pol->V[pol->vcount++] = l1;

                // insira [y, v] em V
                Linha l2 = criaLinha(y, pol->vertices[i],"gray", 0, 1);
                pol->V[pol->vcount++] = l2;

                biombo = pol->vertices[i];
            }

        }
        else{
            Linha seg = (Linha)getSegmento(pol->vertices[i]);
            removeNoArvore(&ativos,seg,pol->vertices[i]);
            if (!encoberto(ativos, bomba, pol->vertices[i])) {
                Ponto y;
                Linha s = segAtivoMaisProx(ativos, bomba, pol->vertices[i], &y);

                // insira [biombo, y] em V
                Linha l1 = criaLinha(biombo, y,"gray", 0, 1);
                pol->V[pol->vcount++] = l1;

                // insira [y, v] em V
                Linha l2 = criaLinha(y, pol->vertices[i],"gray", 0, 1);
                pol->V[pol->vcount++] = l2;

                biombo = pol->vertices[i];
            }
        }
    }
    printf("Regiao de visibilidade\n");
    for (int i = 0; i < pol->vcount; i++) {
        printLinha(pol->V[i], NULL);
    }   
    
    return ativos;
}


