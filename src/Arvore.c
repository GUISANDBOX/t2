#include "linha.h"
#include "Arvore.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

struct noarvore{
    Linha segmento;
    Arvore esq;  // em vez de struct noarvore *
    Arvore dir;  // em vez de struct noarvore *
};

typedef struct noarvore sNoArvore;

Arvore criaarvore(){
    return NULL;
}

void criaNoArvore(Arvore *a, Linha segmento, Ponto p){
    if (*a == NULL) {
        sNoArvore *novo = malloc(sizeof(sNoArvore));
        if (!novo) {
            printf("Erro na alocação\n");
            return;
        }
        novo->segmento = segmento;
        novo->esq = NULL;
        novo->dir = NULL;

        *a = novo; // conversão implícita de sNoArvore* para void*
        printf("segmento alocado na arvore\n");
        return;
    }

    // *a é Arvore (void*), então precisa de cast para acessar o nó:
    sNoArvore *atual = (sNoArvore *)(*a);

    int cmp = comparadirecao(atual->segmento, p);
    if (cmp > 0) {
        // atual->esq é Arvore (void*), então &atual->esq é Arvore* (void**),
        // que bate certinho com o parâmetro Arvore *a
        criaNoArvore(&(atual->esq), segmento, p);
    } else {
        criaNoArvore(&(atual->dir), segmento, p);
    }
}

int comparadirecao(Linha l, Ponto p){
    double xponto = getX(p);
    double yponto = getY(p);
    double x1linha = getX1Linha(l);
    double y1linha = getY1Linha(l);
    double x2linha = getX2Linha(l);
    double y2linha = getY2Linha(l);
    double D = (x1linha*y2linha*1 + x2linha*1*xponto + 1*y1linha*yponto) - (1*y2linha*xponto + x1linha*1*yponto + x2linha*y1linha*1);
    if(D > 0){
        return 1; // ponto está à esquerda da linha
    }
    else if(D < 0){
        return -1; // ponto está à direita da linha
    }
    else{
        return 0; // ponto está sobre a linha
    }
}

void printArvore(Arvore a, int nivel) {
    if (a == NULL) return;

    sNoArvore *no = (sNoArvore*)a;

    printArvore(no->dir, nivel + 1);

    for (int i = 0; i < nivel; i++) printf("   ");
    printf("SEG id=%d\n", getIdLinha(no->segmento)); // ou outro campo do segmento

    printArvore(no->esq, nivel + 1);
}

void removeNoArvore(Arvore *a, Linha segmento, Ponto p) {
    if (*a == NULL) return;

    sNoArvore *no = (sNoArvore*)(*a);

    // 1) Caso o segmento seja exatamente o que queremos remover
    if (linhasIguais(no->segmento, segmento)) {

        // Caso 1: nó sem filhos
        if (no->esq == NULL && no->dir == NULL) {
            free(no);
            *a = NULL;
            return;
        }

        // Caso 2: só filho direito
        if (no->esq == NULL) {
            *a = no->dir;
            free(no);
            return;
        }

        // Caso 3: só filho esquerdo
        if (no->dir == NULL) {
            *a = no->esq;
            free(no);
            return;
        }

        // Caso 4: dois filhos → substitui pelo menor da subárvore direita
        sNoArvore *min = minNo(no->dir);
        no->segmento = min->segmento;

        // Remove o nó duplicado
        removeNoArvore(&(no->dir), min->segmento, p);
        return;
    }

    // 2) Ainda não achou → usar comparadirecao para decidir o caminho
    int cmp = comparadirecao(no->segmento, p);

    if (cmp > 0)
        removeNoArvore(&(no->esq), segmento, p);
    else
        removeNoArvore(&(no->dir), segmento, p);
}

int linhasIguais(Linha a, Linha b) {
    return getIdLinha(a) == getIdLinha(b);
}

Arvore minNo(Arvore a) {
    if (a == NULL) return NULL;

    sNoArvore *no = (sNoArvore*)a;
    while (no->esq != NULL)
        no = (sNoArvore*)no->esq;

    return no;
}


static void segMaisProxRec(Arvore a, Ponto bomba, Ponto dir,
                           Linha *bestSeg, double *bestT, Ponto *bestY) {
    if (a == NULL) return;

    sNoArvore *no = (sNoArvore*)a;

    // visita subárvore esquerda
    segMaisProxRec(no->esq, bomba, dir, bestSeg, bestT, bestY);

    // testa segmento atual
    Ponto y;
    double t;
    if (interseccaoRaioSegmento(bomba, dir, no->segmento, &y, &t)) {
        if (t < *bestT) {
            *bestT   = t;
            *bestSeg = no->segmento;
            if (bestY) *bestY = y;
        }
    }

    // visita subárvore direita
    segMaisProxRec(no->dir, bomba, dir, bestSeg, bestT, bestY);
}


Linha segAtivoMaisProx(Arvore a, Ponto bomba, Ponto v, Ponto *yOut) {
    Linha bestSeg = NULL;
    double bestT = 1e100;
    segMaisProxRec(a, bomba, v, &bestSeg, &bestT, yOut);
    return bestSeg;
}


int encoberto(Arvore ativos, Ponto bomba, Ponto v) {
    Ponto y;
    Linha s = segAtivoMaisProx(ativos, bomba, v, &y);
    if (s == NULL) return 0; // nada intercepta

    double distBv = distanciaPontos(bomba, v);
    double distBy = distanciaPontos(bomba, y);

    return distBy < distBv - 1e-6; // um eps pra evitar bug numérico
}

double distanciaPontos(Ponto a, Ponto b) {
    double dx = getX(b) - getX(a);
    double dy = getY(b) - getY(a);
    return sqrt(dx*dx + dy*dy);
}

int interseccaoRaioSegmento(Ponto origem, Ponto dir,
                            Linha seg, Ponto *pOut, double *tOut) {
    // raio: origem + t * d, t >= 0
    double ox = getX(origem), oy = getY(origem);
    double dx = getX(dir) - ox;
    double dy = getY(dir) - oy;

    Ponto a = getP1Linha(seg);
    Ponto b = getP2Linha(seg);
    double ax = getX(a), ay = getY(a);
    double bx = getX(b), by = getY(b);

    double sx = bx - ax;
    double sy = by - ay;

    // resolver: origem + t*d = a + u*s
    double det = dx * (-sy) - dy * (-sx); // dx*(-sy) - dy*(-sx) = dx*(-sy) + dy*sx

    if (fabs(det) < 1e-9) return 0; // paralelo ou quase

    double rx = ax - ox;
    double ry = ay - oy;

    double t = (rx * (-sy) - ry * (-sx)) / det;
    double u = (dx * ry - dy * rx) / det;

    if (t < 0) return 0;      // interseção "atrás" da origem do raio
    if (u < 0 || u > 1) return 0;  // fora do segmento

    if (pOut) {
        double ix = ox + t * dx;
        double iy = oy + t * dy;
        *pOut = criaPonto(ix, iy); // ou sua função correspondente
    }
    if (tOut) *tOut = t;

    return 1;
}
