#include <stdio.h>

void criacirculo(int i, double x, double y, double r, char corb[], char corp[], FILE *f){

    fprintf(f,"<circle r=\"%lf\" cx=\"%lf\" cy=\"%lf\" fill-opacity=\"0.5\" stroke=\"%s\" fill=\"%s\" />\n",r,x,y,corb,corp);
}

void criaretangulo(int i, double x, double y, double w, double h, char corb[], char corp[], FILE *f) {

    fprintf(f,"<rect x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" fill-opacity=\"0.5\" stroke=\"%s\" fill=\"%s\" />\n",x,y,w,h,corb,corp);
}

void crialinha(int i, double x1, double y1, double x2, double y2, char cor[], FILE *f){
    fprintf(f,"<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" fill-opacity=\"0.5\" stroke=\"%s\" />\n",x1,y1,x2,y2,cor);
}

void criatexto(int i, double x, double y, char corb[], char corp[], char a, char txto[], char currentFFamily[], char currentFWeight[], char currentFSize[], FILE *f){
    if (a=='i') {
        fprintf(f,"<text x=\"%lf\" y=\"%lf\" stroke=\"%s\" fill=\"%s\" fill-opacity=\"0.5\" text-anchor=\"start\" font-family=\"%s\" font-weight=\"%s\" font-size=\"%s\" >%s</text>\n",x,y,corb,corp,currentFFamily,currentFWeight,currentFSize,txto);
    }
    else if (a=='f') {
        fprintf(f,"<text x=\"%lf\" y=\"%lf\" stroke=\"%s\" fill=\"%s\" fill-opacity=\"0.5\" text-anchor=\"end\" font-family=\"%s\" font-weight=\"%s\" font-size=\"%s\" >%s</text>\n",x,y,corb,corp,currentFFamily,currentFWeight,currentFSize,txto);
    }
    else {
        fprintf(f,"<text x=\"%lf\" y=\"%lf\" stroke=\"%s\" fill=\"%s\" fill-opacity=\"0.5\" text-anchor=\"middle\" font-family=\"%s\" font-weight=\"%s\" font-size=\"%s\" >%s</text>\n",x,y,corb,corp,currentFFamily,currentFWeight,currentFSize,txto);
    }
}