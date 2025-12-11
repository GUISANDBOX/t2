#include "comandosqry.h"
#include <string.h>
#include <stdio.h>
#include "retangulo.h"
#include "circulo.h"
#include "linha.h"
#include "texto.h"
#include "ponto.h"
#include "poligono.h"
#include <math.h>
#include "Arvore.h"
#include "Criasvg.h"

void escreveItemTxt(Item item, int tipo, FILE *arqtxt) {
    if (tipo == 1) { // Circulo
        Circulo c = (Circulo)item;
        escreveCirculoTxt(c, arqtxt);
    } else if (tipo == 2) { // Retangulo
        Retangulo r = (Retangulo)item;
        escreveRetanguloTxt(r, arqtxt);
    } else if (tipo == 3) { // Linha
        Linha l = (Linha)item;
        escreveLinhaTxt(l, arqtxt);
    } else if (tipo == 4) { // Texto
        Texto t = (Texto)item;
        escreveTextoTxt(t, arqtxt);
    }
}

Ponto getP1Item(Item item, int tipo) {
    if (tipo == 3) { // Linha
        Linha l = (Linha)item;
        return criaPonto(getX1Linha(l), getY1Linha(l));
    }
    else if (tipo == 4) {
        Texto t = (Texto)item;
        return getP1Texto(t);
    }
    return NULL; // Outros tipos não possuem ponto 1
}

Ponto getP2Item(Item item, int tipo) {
    if (tipo == 3) { // Linha
        Linha l = (Linha)item;
        return criaPonto(getX2Linha(l), getY2Linha(l));
    }
    else if (tipo == 4) {
        Texto t = (Texto)item;
        return getP2Texto(t);
    }
    return NULL; // Outros tipos não possuem ponto 1
}

double areaLinha(Item item, int tipo) {
    if (tipo == 3) { // Linha
        Linha l = (Linha)item;
        return getAreaLinha(l);
    }
    else if (tipo == 4) {
        Texto t = (Texto)item;
        return getAreaTexto(t);
    }
    return 0.0; // Outros tipos não possuem área de linha
}

char *getCorbLinha(Item item, int tipo) {
    if (tipo == 3) { // Linha
        Linha l = (Linha)item;
        return getCorLinha(l);
    }
    else if (tipo == 4) {
        Texto t = (Texto)item;
        return getCorbTexto(t);
    }
    return NULL; // Outros tipos não possuem cor de linha
}


char *getCorpLinha(Item item, int tipo) {
    if (tipo == 3) { // Linha
        Linha l = (Linha)item;
        return getCorLinha(l);
    }
    else if (tipo == 4) {
        Texto t = (Texto)item;
        return getCorpTexto(t);
    }
    return NULL; // Outros tipos não possuem cor de linha
}

int getIdLinhaOuTexto(Item li, int tipo_i) {
    if (tipo_i == 3) { // Linha
        Linha l = (Linha)li;
        return getIdLinha(l);
    }
    else if (tipo_i == 4) {
        Texto t = (Texto)li;
        return getIdTexto(t);
    }
    return -1; // Outros tipos não possuem id de linha ou texto
}

/**
 * O arqtxt é o arquivo txt de saída para comandos qry que precisem escrever nele.
 */
void processaQry(FILE *fileq, FILE *filesaidaquery, Lista listaOriginal, FILE *arqtxt, char ordenacao, int N) {
    char comando[32];
    int comandoaux, i, j, n;
    double x, y, dx, dy;
    char a,s;
    char sfx[100], cor[100];
    Ponto vertices[10000];
    int qtdVertices = 0;
    Poligono poligono;
    Arvore arvore=criaarvore();

    fprintf(filesaidaquery, "<svg xmlns:svg=\"http://www.w3.org/2000/svg\" xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\">\n");
    printf("Iniciando processamento do QRY\n");
    do {
        comandoaux = fscanf(fileq, " %31s", comando);
        if (comandoaux != 1) break;

        printf("LIDO %s\n", comando);

        if (!strcmp(comando, "a")) {
            fscanf(fileq, "%d %d %c", &i, &j, &s);
            fprintf(arqtxt, "[*] a %d %d %c\n", i, j, s);
            listaOriginal = transformaAnteparo(listaOriginal, i, j, s, vertices, &qtdVertices);
            listaOriginal = transformaAnteparo(listaOriginal, -1, -1, s, vertices, &qtdVertices);
            poligono = criaPoligono(qtdVertices, vertices);
        }
        else if (!strcmp(comando, "d")) {
            fscanf(fileq, "%lf %lf %s", &x, &y, sfx);
            fprintf(arqtxt, "[*] d %lf %lf %s\n", x, y, sfx);
            Ponto bomba = criaPonto(x, y);
            adicionaBomba(&listaOriginal, bomba);
            atualizaAngulosVertice(poligono, bomba);
            ordenarVerticesPorAngulo(poligono, ordenacao, N);
            printVertices(poligono);
            arvore=insertVerticesarvore(arvore,poligono);
            printArvore(arvore,0);
            criarVisibilidade(comando, poligono, filesaidaquery, &listaOriginal, x, y, cor, dx, dy, sfx);
        }
        else if (!strcmp(comando, "p")) {
            fscanf(fileq, "%lf %lf %s %s", &x, &y, cor, sfx);
            fprintf(arqtxt, "[*] p %lf %lf %s %s\n", x, y, cor, sfx);
            Ponto bomba = criaPonto(x, y);
            adicionaBomba(&listaOriginal, bomba);
            atualizaAngulosVertice(poligono, bomba);
            ordenarVerticesPorAngulo(poligono, ordenacao, N);
            printVertices(poligono);
            arvore=insertVerticesarvore(arvore,poligono);
            printArvore(arvore,0);
            criarVisibilidade(comando, poligono, filesaidaquery, &listaOriginal, x, y, cor, dx, dy, sfx);
        }
        else if (!strcmp(comando, "cln")) {
            fscanf(fileq, "%lf %lf %lf %lf %s", &x, &y, &dx, &dy, sfx);
            fprintf(arqtxt, "[*] cln %lf %lf %lf %lf %s\n", x, y, dx, dy, sfx);
            Ponto bomba = criaPonto(x, y);
            adicionaBomba(&listaOriginal, bomba);
            atualizaAngulosVertice(poligono, bomba);
            ordenarVerticesPorAngulo(poligono, ordenacao, N);
            printVertices(poligono);
            arvore=insertVerticesarvore(arvore,poligono);
            printArvore(arvore,0);
            criarVisibilidade(comando, poligono, filesaidaquery, &listaOriginal, x, y, cor, dx, dy, sfx);
        }
    } while (1);

    

    exibirlista(listaOriginal, filesaidaquery);

    fprintf(filesaidaquery, "</svg>\n");
}


void  criarVisibilidade(char *comando, Poligono poligono, FILE *filesaidaquery, Lista *listaOriginal, double x, double y, char *cor, double dx, double dy, char *sfx) {
    // Insere o V dentro da lista original
    Linha *V = getV(poligono);
    int VCount = getVCount(poligono);
    double matrizPontos[10000][2];
    int i;
    for (i = 0; i < VCount; i++) {
        Ponto p1 = getP1Linha(V[i]), p2 = getP2Linha(V[i]);
        matrizPontos[i][0] = getX(p1);
        matrizPontos[i][1] = getY(p1);
    }
    criapoligonoSvg(-1, matrizPontos, VCount, "black", "gray", filesaidaquery);
    ativarBomba(comando, listaOriginal, poligono, x, y, cor, dx, dy, sfx);
}
