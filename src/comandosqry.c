#include "comandosqry.h"
#include <string.h>
#include <stdio.h>
#include "retangulo.h"
#include "circulo.h"
#include "linha.h"
#include "texto.h"
#include "ponto.h"
#include <math.h>
#include "disparador.h"

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
void processaQry(FILE *fileq, Fila filasaida, FILE *filesaidaquery, Fila filaOriginal, FILE *arqtxt) {
    Disparador listadisp[100];
    Pilha listacarr[100];
    char comando[32];
    int z, i, j, n, tipo;
    int iesq, idir;
    float x, y, x1, y1, x2, y2;
    char a;
    char mododisp; 

    
    int totaldeinstrucoes = 0;
    int totaldedisparos = 0;
    int totaldeformasesmagadas = 0;
    int totaldeformasclonadas = 0;  
    double pontuacaofinal = 0.0;

    // Inicializa as pilhas
    for (j=0; j<100; j++) {
        listacarr[j] = criapilha(0);
    }

    fprintf(filesaidaquery, "<svg xmlns:svg=\"http://www.w3.org/2000/svg\" xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\">\n");
    printf("Iniciando processamento do QRY\n");
    do {
        z = fscanf(fileq, " %31s", comando);
        if (z != 1) break;

        printf("LIDO %s\n", comando);

        if (!strcmp(comando, "pd")) {
            fscanf(fileq, "%d %f %f", &i, &x, &y);
            listadisp[i] = criaDisparador(i, x, y);
            printf("Disparador %d criado!\n", iddisparador(listadisp[i]));
            totaldeinstrucoes++;
        }
        else if (!strcmp(comando, "lc")) {
            fscanf(fileq, "%d %d", &i, &n);
            printf("Inicializando carregador!\n");
            fprintf(arqtxt, "[*] lc %d %d\n", i, n);
            Pilha pilha = criapilha(0);
            Item item;
            for (j=0; j<n; j++) {
                item = remover(&filaOriginal, &tipo);
                empilha(&pilha, item, tipo);
                escreveItemTxt(item, tipo, arqtxt);
            }
            printf("Pilha %d carregada!\n", i);
            listacarr[i] = pilha;
            totaldeinstrucoes++;
        }
        else if (!strcmp(comando, "atch")) {
            fscanf(fileq, "%d %d %d", &i, &iesq, &idir);
            printf("Encaixando disparadores!\n");
            encaixar(listadisp[i], listacarr[iesq], listacarr[idir]);
            printf("Encaixe realizado!\n");
            totaldeinstrucoes++;
        }
        else if (!strcmp(comando, "rjd")) {
            fscanf(fileq, "%i %c %f %f %f %f", &i, &a, &x1, &y1, &x2, &y2);
            printf("REALIZANDO RAJADA\n");
            Pilha pilhadodisparador;
            
            pilhadodisparador = (a=='d') ? getPilhaEsq(listadisp[i]) : getPilhaDir(listadisp[i]);
            
            while(!pilhavazia(pilhadodisparador)) {
                pilhadodisparador = botao(listadisp[i], a);
                printf("Disparando um objeto: %d\n", tipoatualnodisparo(listadisp[i]));
                // TODO verificar se é para escrever o item antes de disparar ou depois do disparo na sua posição final
                escreveItemTxt(itemAtualNoDisparo(listadisp[i]), tipoatualnodisparo(listadisp[i]), arqtxt);
                adicionar(&filasaida, disparar(listadisp[i], x1, y1), tipoatualnodisparo(listadisp[i]));
                x1 += x2;
                y1 += y2;
                totaldedisparos++;
            }
            totaldeinstrucoes++;
        }
        else if (!strcmp(comando, "shft")) {
            fscanf(fileq, "%i %c %i", &i, &a, &n);
            printf("REALIZANDO SHIFT\n");
            fprintf(arqtxt, "[*] shft %d %c %d\n", i, a, n);
            for (j=0; j<n; j++) {
                botao(listadisp[i], a);
            }
            escreveItemTxt(itemAtualNoDisparo(listadisp[i]), tipoatualnodisparo(listadisp[i]), arqtxt);
            printf("SHIFT REALIZADO PARA %c\n", a);
            totaldeinstrucoes++;
        }
        else if (!strcmp(comando, "dsp")) {
            double nx, ny;
            fscanf(fileq, "%i %lf %lf %c", &i, &nx, &ny, &mododisp);
            printf("Disparando um objeto: %d\n", tipoatualnodisparo(listadisp[i]));
            fprintf(arqtxt, "[*] dsp %d %.2lf %.2lf %c\n", i, nx, ny, mododisp);
            escreveItemTxt(itemAtualNoDisparo(listadisp[i]), tipoatualnodisparo(listadisp[i]), arqtxt);
            Item itemdisparado = disparar(listadisp[i], nx, ny);
            int tipodisparado = tipoatualnodisparo(listadisp[i]);
            adicionar(&filasaida, itemdisparado, tipodisparado);
            fprintf(arqtxt,"Posicao apos disparo: (%.2lf, %.2lf)\n\n", getXDisparador(listadisp[i]) + nx, getYDisparador(listadisp[i]) + ny);
            totaldeinstrucoes++;
            totaldedisparos++;
        }
        else if (!strcmp(comando, "calc")) {
            printf("REALIZANDO CALC\n");
            filaOriginal = executaCalc(filasaida, filaOriginal, filesaidaquery, arqtxt, &totaldeformasesmagadas, &totaldeformasclonadas, &pontuacaofinal);
            totaldeinstrucoes++;
        }
    } while (1);

    exibirfila(filaOriginal, filesaidaquery);
    fprintf(filesaidaquery, "</svg>\n");
    fprintf(arqtxt, "\nPontuação final: %lf\nNúmero total de instruções executadas: %d\nNúmero total de disparos: %d\nNúmero total de formas esmagadas: %d\nNúmero total de formas clonadas: %d", pontuacaofinal, totaldeinstrucoes, totaldedisparos, totaldeformasesmagadas, totaldeformasclonadas);

}