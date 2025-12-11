#include <stdio.h>
#include <string.h>

void criacirculo(int i, double x, double y, double r, char corb[], char corp[], FILE *f){

    fprintf(f,"<circle id=\"%d\" r=\"%lf\" cx=\"%lf\" cy=\"%lf\" fill-opacity=\"0.5\" stroke=\"%s\" fill=\"%s\" />\n",i,r,x,y,corb,corp);
}

void criaretangulo(int i, double x, double y, double w, double h, char corb[], char corp[], FILE *f) {

    fprintf(f,"<rect id=\"%d\" x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" fill-opacity=\"0.5\" stroke=\"%s\" fill=\"%s\" />\n",i,x,y,w,h,corb,corp);
}

void crialinha(int i, double x1, double y1, double x2, double y2, char cor[], int anteparo, FILE *f){
    int strokeWidth = 1;
    if (anteparo==1) {
        strokeWidth = 2;
    }
    fprintf(f,"<line id=\"%d\" x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" fill-opacity=\"0.5\" stroke=\"%s\" stroke-width=\"%d\"/>\n",i,x1,y1,x2,y2,cor, strokeWidth);
}

void criatexto(int i, double x, double y, char corb[], char corp[], char a, char txto[], char currentFFamily[], char currentFWeight[], char currentFSize[], FILE *f){
    if (!strcmp(currentFFamily, "sans")) {
        strcpy(currentFFamily, "sans-serif");
    }
    if (a=='i') {
        fprintf(f,"<text id=\"%d\" x=\"%lf\" y=\"%lf\" stroke=\"%s\" fill=\"%s\" fill-opacity=\"0.5\" text-anchor=\"start\" font-family=\"%s\" font-weight=\"%s\" font-size=\"%s\" >%s</text>\n",i,x,y,corb,corp,currentFFamily,currentFWeight,currentFSize,txto);
    }
    else if (a=='f') {
        fprintf(f,"<text id=\"%d\" x=\"%lf\" y=\"%lf\" stroke=\"%s\" fill=\"%s\" fill-opacity=\"0.5\" text-anchor=\"end\" font-family=\"%s\" font-weight=\"%s\" font-size=\"%s\" >%s</text>\n",i,x,y,corb,corp,currentFFamily,currentFWeight,currentFSize,txto);
    }
    else {
        fprintf(f,"<text id=\"%d\" x=\"%lf\" y=\"%lf\" stroke=\"%s\" fill=\"%s\" fill-opacity=\"0.5\" text-anchor=\"middle\" font-family=\"%s\" font-weight=\"%s\" font-size=\"%s\" >%s</text>\n",i,x,y,corb,corp,currentFFamily,currentFWeight,currentFSize,txto);
    }
}

void criapoligonoSvg(int i, double pontos[][2], int n, char corb[], char corp[], FILE *f){
    fprintf(f,"<polygon id=\"%d\" points=\"",i);
    for (int j=0; j<n; j++){
        fprintf(f,"%lf,%lf ",pontos[j][0], pontos[j][1]);
    }
    fprintf(f,"\" fill-opacity=\"0.5\" stroke=\"%s\" fill=\"%s\" />\n",corb,corp);
}