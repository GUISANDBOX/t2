#ifndef CRIASVG
#define CRIASVG

//programa para criar arquivos SVG.

void criacirculo(int i, double x, double y, double r, char corb[], char corp[], FILE *f);
//cria um círculo com identificador 'i' centrado em (x,y) e de raio 'r'. 'corb' é a cor da borda e 'corp' é a cor do preenchimento.

void criaretangulo(int i, double x, double y, double w, double h, char corb[], char corp[], FILE *f);
//cria um retângulo com identificador 'i', onde (x,y) é sua âncora, 'w' é a largura e 'h' é a altura. 'corb' é a cor da borda e 'corp' é a cor do preenchimento.

void crialinha(int i, double x1, double y1, double x2, double y2, char cor[], int anteparo, FILE *f);
//cria uma linha com identificador 'i', onde (x1,y1) é uma extremidade e (x2,y2) é a outra. 'cor' é a sua cor.

void criatexto(int i, double x, double y, char corb[], char corp[], char a, char txto[], char currentFFamily[], char currentFWeight[], char currentFSize[], FILE *f);
//cria o texto 'txto' com identificador 'i' na posição (x,y). 'a' é a posição da âncora, aceitando "i"(início), "m"(meio) ou "f"(fim). 'corb' é a cor da borda e 'corp' é a cor do preenchimento. 'currentFFamily', 'currentFWeight' e 'currentFSize' são, respectivamente, a família, o peso e o tamanho da fonte.

void criapoligonoSvg(int i, double pontos[][2], int n, char corb[], char corp[], FILE *f);
//cria um polígono com identificador 'i', definido por 'n' pontos

#endif