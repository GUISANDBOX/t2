#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Lista.h"
#include "circulo.h"
#include "ponto.h"
#include "retangulo.h"
#include "linha.h"
#include "texto.h"
#include "poligono.h"

struct elemento{
    Item item;
    int tipo; // 0 - circulo, 1 retangulo, etc
    struct elemento *prox;
};

typedef struct elemento sNoItem;

void adicionar(Lista *f, Item item, int tipo){
    sNoItem **inicio = (sNoItem **)f;

    sNoItem *novo = (sNoItem *)malloc(sizeof(sNoItem));
    if(!novo){
        printf("Erro na alocação\n");
        return;
    }

    novo->item = item;
    novo->tipo = tipo;
    novo->prox = NULL;

    // Se a lista está vazia, novo é o primeiro
    if (*inicio == NULL) {
        *inicio = novo;
        return;
    }

    // Percorre até o último
    sNoItem *atual = *inicio;
    while (atual->prox != NULL) {
        atual = atual->prox;
    }

    // Insere no final
    atual->prox = novo;
}


Item remover(Lista *f, int *tipo) {
    sNoItem **inicio = (sNoItem **)f;

    if (*inicio == NULL) { // Evita remover de lista vazia
        printf("Lista vazia!\n");
        return NULL;
    }

    sNoItem *atual = *inicio;
    sNoItem *anterior = NULL;

    // Percorre até o último nó
    while (atual->prox != NULL) {
        anterior = atual;
        atual = atual->prox;
    }

    // Se só havia um elemento
    if (anterior == NULL) {
        *inicio = NULL; // lista agora fica vazia
    } else {
        anterior->prox = NULL; // o penúltimo vira o último
    }

    Item removido = atual->item;
    *tipo = atual->tipo;
    free(atual); // desaloca o nó removido
    return removido;
}

void exibirlista(Lista f, FILE *arqnovo){
    sNoItem *atual= (sNoItem *)f;
    while(atual!=NULL){
        if (atual->tipo==1) {
            printf("\n\nCirculo:\n");
            printCirculo(atual->item, arqnovo);
        }
        else if (atual->tipo==2) {
            printf("\n\nRetangulo:\n");
            printRetangulo(atual->item, arqnovo);
        }
        else if (atual->tipo==3) {
            printf("\n\nLinha:\n");
            printLinha(atual->item, arqnovo);
        }
        else if (atual->tipo==4) {
            printf("\n\nTexto:\n");
            printTexto(atual->item, arqnovo);
        }
        atual=atual->prox;
    }
    printf("\n");
}

Lista crialista(){
    return NULL;
}

int listavazia(Lista l) {
    sNoItem *atual= (sNoItem *)l;
    if(atual==NULL){
        return 1;
    }
    return 0;
}

int getMaiorIdLista(Lista l) {
    sNoItem *atual= (sNoItem *)l;
    int id_maior = 0;
    while(atual!=NULL){
        if (atual->tipo==1) {
            if (getIdCirculo((Circulo)atual->item) > id_maior) {
                id_maior = getIdCirculo((Circulo)atual->item);
            }
        }
        else if (atual->tipo==2) {
            if (getIdRetangulo((Retangulo)atual->item) > id_maior) {
                id_maior = getIdRetangulo((Retangulo)atual->item);
            }
        }
        else if (atual->tipo==3) {
            if (getIdLinha((Linha)atual->item) > id_maior) {
                id_maior = getIdLinha((Linha)atual->item);
            }
        }
        else if (atual->tipo==4) {
            if (getIdTexto((Texto)atual->item) > id_maior) {
                id_maior = getIdTexto((Texto)atual->item);
            }
        }
        atual=atual->prox;
    }
    return id_maior;
}



void limpaLista(Lista *l) {
    sNoItem **inicio = (sNoItem **)l;
    sNoItem *atual = *inicio;
    sNoItem *prox;

    while (atual != NULL) {
        prox = atual->prox;
        destruirItemLista(atual->item, atual->tipo);
        free(atual);
        atual = prox;
    }

    *inicio = NULL; // Define a lista como vazia após limpar
}

void destruirItemLista(Item item, int tipo) {
    switch (tipo) {
        case 1: // Circulo
            destroiCirculo((Circulo)item);
            break;
        case 2: // Retangulo
            destroiRetangulo((Retangulo)item);
            break;
        case 3: // Linha
            destroiLinha((Linha)item);
            break;
        case 4: // Texto
            destroiTexto((Texto)item);
            break;
    }
}

Lista transformaAnteparo(Lista l, int i, int j, char s, Ponto vertices[], int *qtdVertices, FILE *arqtxt) {
    sNoItem *atual  = (sNoItem *)l;
    sNoItem *anterior = NULL;
    int id = 0;
    int novo_id = getMaiorIdLista(l) + 1;
    int num = *qtdVertices;

    while (atual != NULL) {

        if (atual->tipo == 1) { // círculo
            id = getIdCirculo((Circulo)atual->item);
            if (id >= i && id <= j) {
                atual->item = transformaAnteparoCirculo((Circulo)atual->item, novo_id++, s);
                atual->tipo = 3;
                vertices[num++] = getP1Linha((Linha)atual->item);
                vertices[num++] = getP2Linha((Linha)atual->item);
                Ponto p1 = getP1Linha((Linha)atual->item);
                Ponto p2 = getP2Linha((Linha)atual->item);
                if (arqtxt) fprintf(arqtxt, "Transformou círculo id %d em anteparo id %d com pontos em %lf,%lf e %lf,%lf\n", id, novo_id - 1, getX(p1), getY(p1), getX(p2), getY(p2));
            }
            anterior = atual;
            atual = atual->prox;
        }

        else if (atual->tipo == 2) { // retângulo
            id = getIdRetangulo((Retangulo)atual->item);
            if (id >= i && id <= j) {
                char cod='o';
                if(id == -1){
                    cod = 'r';
                }

                // Guarda o próximo antes de mexer
                sNoItem *prox_old = atual->prox;

                // Aloca 4 nós, representando os 4 lados do retangulo
                sNoItem *novo1 = malloc(sizeof(sNoItem));
                sNoItem *novo2 = malloc(sizeof(sNoItem));
                sNoItem *novo3 = malloc(sizeof(sNoItem));
                sNoItem *novo4 = malloc(sizeof(sNoItem));

                // Preenche cada um
                novo1->item = transformaAnteparoRetangulo1((Retangulo)atual->item, novo_id++, cod);
                novo1->tipo = 3;
                Ponto p1_1 = getP1Linha((Linha)novo1->item);
                Ponto p2_1 = getP2Linha((Linha)novo1->item);
                vertices[num++] = p1_1;
                vertices[num++] = p2_1;

                novo2->item = transformaAnteparoRetangulo2((Retangulo)atual->item, novo_id++, cod);
                novo2->tipo = 3;
                Ponto p1_2 = getP1Linha((Linha)novo2->item);
                Ponto p2_2 = getP2Linha((Linha)novo2->item);
                vertices[num++] = p1_2;
                vertices[num++] = p2_2;

                novo3->item = transformaAnteparoRetangulo3((Retangulo)atual->item, novo_id++, cod);
                novo3->tipo = 3;
                Ponto p1_3 = getP1Linha((Linha)novo3->item);
                Ponto p2_3 = getP2Linha((Linha)novo3->item);
                vertices[num++] = p1_3;
                vertices[num++] = p2_3;

                novo4->item = transformaAnteparoRetangulo4((Retangulo)atual->item, novo_id++, cod);
                novo4->tipo = 3;
                Ponto p1_4 = getP1Linha((Linha)novo4->item);
                Ponto p2_4 = getP2Linha((Linha)novo4->item);
                vertices[num++] = p1_4;
                vertices[num++] = p2_4;

                // Liga os 4 entre si
                novo1->prox = novo2;
                novo2->prox = novo3;
                novo3->prox = novo4;
                novo4->prox = prox_old;

                // Liga com o restante da lista
                if (anterior != NULL) {
                    anterior->prox = novo1;
                } else {
                    l = (Lista)novo1;
                }

                free(atual);

                anterior = novo4;
                atual = prox_old;
                
                if (arqtxt) {
                    fprintf(arqtxt, "Transformou retângulo id %d em anteparos com ids %d, %d, %d, %d\n", id, novo_id - 4, novo_id - 3, novo_id - 2, novo_id - 1);
                    fprintf(arqtxt, "  Anteparo %d: [%lf,%lf] -> [%lf,%lf]\n", novo_id - 4, getX(p1_1), getY(p1_1), getX(p2_1), getY(p2_1));
                    fprintf(arqtxt, "  Anteparo %d: [%lf,%lf] -> [%lf,%lf]\n", novo_id - 3, getX(p1_2), getY(p1_2), getX(p2_2), getY(p2_2));
                    fprintf(arqtxt, "  Anteparo %d: [%lf,%lf] -> [%lf,%lf]\n", novo_id - 2, getX(p1_3), getY(p1_3), getX(p2_3), getY(p2_3));
                    fprintf(arqtxt, "  Anteparo %d: [%lf,%lf] -> [%lf,%lf]\n", novo_id - 1, getX(p1_4), getY(p1_4), getX(p2_4), getY(p2_4));
                }
            } else {
                anterior = atual;
                atual = atual->prox;
            }
        }

        else if (atual->tipo == 3) { // linha
            id = getIdLinha((Linha)atual->item);
            if (id >= i && id <= j) {
                atual->item = transformaAnteparoLinha((Linha)atual->item, novo_id++);
                vertices[num++] = getP1Linha((Linha)atual->item);
                vertices[num++] = getP2Linha((Linha)atual->item);
                Ponto p1 = getP1Linha((Linha)atual->item);
                Ponto p2 = getP2Linha((Linha)atual->item);
                if (arqtxt) fprintf(arqtxt, "Transformou linha id %d em anteparo id %d com pontos em %lf,%lf e %lf,%lf\n", id, novo_id - 1, getX(p1), getY(p1), getX(p2), getY(p2));
            }
            anterior = atual;
            atual = atual->prox;
        }

        else if (atual->tipo == 4) { // texto
            Texto txt = (Texto)atual->item;
            id = getIdTexto(txt);
            if (id >= i && id <= j) {
                Ponto p1_txt = getP1Texto(txt);
                Ponto p2_txt = getP2Texto(txt);
                transformaAnteparoTexto(txt, novo_id++);
                vertices[num++] = p1_txt;
                vertices[num++] = p2_txt;
                if (arqtxt) fprintf(arqtxt, "Transformou texto id %d em anteparo id %d com pontos em %lf,%lf e %lf,%lf\n", id, novo_id - 1, getX(p1_txt), getY(p1_txt), getX(p2_txt), getY(p2_txt));
            }
            anterior = atual;
            atual = atual->prox;
        }
    }

    *qtdVertices = num;
    return l;
}

void adicionaBomba(Lista *l, Ponto centro, double *menorX, double *menorY, double *maiorX, double *maiorY) {
    Texto bomba = criaTexto(centro, "red", "red", ".", 'm', "cursive", "bolder", "20", 0);
    adicionar(l, (Item)bomba, 4);
    double x = getX(centro);
    double y = getY(centro);
    if(x < *menorX) *menorX = x;
    if(y < *menorY) *menorY = y;
    if(x > *maiorX) *maiorX = x;
    if(y > *maiorY) *maiorY = y;
}

void ativarBomba(char *comando, Lista *listaOriginal, Poligono poligono,
                 double x, double y, char *cor, double dx, double dy, char *sfx, FILE *arqtxt) {
    Linha *V = getV(poligono);
    sNoItem *atual = (sNoItem *)*listaOriginal;
    sNoItem *anterior = NULL;

    // Lista separada só para os clones
    Lista listaClones = crialista();

    while (atual != NULL) {
        int bate = 0;
        int id = -1;
        char *tipo_str = "";

        if (atual->tipo == 1) {                // Círculo
            Circulo c = (Circulo)atual->item;
            bate = circuloInterceptaPoligono(c, poligono);
            id = getIdCirculo(c);
            tipo_str = "Circulo";
        }
        else if (atual->tipo == 2) {           // Retângulo
            Retangulo r = (Retangulo)atual->item;
            bate = retanguloInterceptaPoligono(r, poligono);
            id = getIdRetangulo(r);
            tipo_str = "Retangulo";
        }
        else if (atual->tipo == 3) {           // Linha
            Linha l = (Linha)atual->item;
            bate = linhaInterceptaPoligono(l, poligono);
            id = getIdLinha(l);
            tipo_str = "Linha";
        }
        else if (atual->tipo == 4) {           // Texto
            Texto t = (Texto)atual->item;
            Ponto p1texto = getP1Texto(t);
            Ponto p2texto = getP2Texto(t);
            Linha linhaTexto = criaLinha(p1texto, p2texto, "black", getIdTexto(t), 0);
            bate = linhaInterceptaPoligono(linhaTexto, poligono);
            id = getIdTexto(t);
            tipo_str = "Texto";
            destroiLinha(linhaTexto);
        }

        sNoItem *prox = atual->prox;  // guarda antes de mexer na lista

        if(atual->tipo == 3 && getcodigoLinha((Linha)atual->item) == 'r') {
            // Linhas que são anteparos do retangulo não são afetadas pela bomba
            bate = 0;
        }

        if (bate && strcmp(comando, "d") == 0) {
            printf("OBJETO ATINGIDO PELA BOMBA!\n");
            printf("BOMBA DETONADA - REMOVENDO OBJETO DA LISTA\n");
            if (arqtxt) fprintf(arqtxt, "  Destruido: %s id %d\n", tipo_str, id);

            // tira 'atual' da lista
            if (anterior != NULL) {
                anterior->prox = prox;
            } else {
                // era o primeiro nó: atualiza cabeça
                *listaOriginal = (Lista)prox;
            }

            // libera o item, se tiver função específica
            // liberaCirculo/Retangulo/Linha/Text etc, dependendo de atual->tipo

            //free(atual);         // libera o nó
            // NÃO avança 'anterior' aqui, porque ele continua apontando pro anterior válido
        } else {
            // não removeu -> pode avançar 'anterior'
            anterior = atual;
        }

        if (bate && !strcmp(comando, "p")) {
            // Alterando a cor do objeto
            if (arqtxt) fprintf(arqtxt, "  Pintado: %s id %d com cor %s\n", tipo_str, id, cor);
            
            if (atual->tipo == 1) {                // Círculo
                setCorbCirculo((Circulo)atual->item, cor);
                setCorpCirculo((Circulo)atual->item, cor);
            }
            else if (atual->tipo == 2) {           // Retângulo
                setCorbRetangulo((Retangulo)atual->item, cor);
                setCorpRetangulo((Retangulo)atual->item, cor);
            }
            else if (atual->tipo == 3) {           // Linha
                setCorLinha((Linha)atual->item, cor);
            }
            else if (atual->tipo == 4) {           // Texto
                // tratar texto, se quiser
                setCorbTexto((Texto)atual->item, cor);
                setCorpTexto((Texto)atual->item, cor);
            }
        }

        if (bate && !strcmp(comando, "cln")) {
            printf("CLONANDO obj");
            if (arqtxt) fprintf(arqtxt, "  Original: %s id %d ", tipo_str, id);
            
            // Clonando o objeto
            if (atual->tipo == 1) {                // Círculo
                Circulo c = clonecirculo((Circulo)atual->item, getMaiorIdLista(*listaOriginal) + 1);
                movecirculo(c, getXCirculo(c), getYCirculo(c), dx, dy);
                int novo_id = getIdCirculo(c);
                if (arqtxt) fprintf(arqtxt, "=> Clone: Circulo id %d\n", novo_id);
                
                adicionar(&listaClones, (Circulo)c, 1);
            }
            else if (atual->tipo == 2) {           // Retângulo
                Retangulo r = cloneretangulo((Retangulo)atual->item, getMaiorIdLista(*listaOriginal) + 1);
                moveretangulo(r, getXRetangulo(r), getYRetangulo(r), dx, dy);
                int novo_id = getIdRetangulo(r);
                if (arqtxt) fprintf(arqtxt, "=> Clone: Retangulo id %d\n", novo_id);
                
                adicionar(&listaClones, (Retangulo)r, 2);
            }
            else if (atual->tipo == 3) {           // Linha
                Linha l = cloneLinha((Linha)atual->item, getMaiorIdLista(*listaOriginal) + 1);
                movelinha(l, getX1Linha(l), getY1Linha(l), dx, dy);
                int novo_id = getIdLinha(l);
                if (arqtxt) fprintf(arqtxt, "=> Clone: Linha id %d\n", novo_id);
                
                adicionar(&listaClones, (Linha)l, 3);
            }
            else if (atual->tipo == 4) {           // Texto
                Texto t = cloneTexto((Texto)atual->item, getMaiorIdLista(*listaOriginal) + 1);
                movetexto(t, getXTexto(t), getYTexto(t), dx, dy);
                int novo_id = getIdTexto(t);
                if (arqtxt) fprintf(arqtxt, "=> Clone: Texto id %d\n", novo_id);
                
                adicionar(&listaClones, (Texto)t, 4);
                
            }
        }

        atual = prox;  // sempre avança usando o prox salvo
    }

    // Adiciona os clones no final da lista original
    if (listaClones != NULL) {
        // se quiser, pode encaixar clones no começo:
        sNoItem *ultimoClone = (sNoItem *)listaClones;
        while (ultimoClone->prox != NULL) {
            ultimoClone = ultimoClone->prox;
        }
        // liga o fim dos clones no começo da lista original
        ultimoClone->prox = (sNoItem *)*listaOriginal;
        // cabeça da lista passa a ser o primeiro clone
        *listaOriginal = listaClones;
    }
}
