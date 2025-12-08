#include "ponto.h"
#include "Mergesort.h"
#include <stdlib.h>
#include <stdio.h>
#include "poligono.h"

void MergeSort(Ponto V[], int ini, int fim, int n) {
    if (fim - ini < n) {
        InsertionSort(V, ini, fim);
        return;
    }
    if (ini < fim) {
        int meio = (ini + fim) / 2;
        MergeSort(V, ini, meio, n);
        MergeSort(V, meio + 1, fim, n);
        Merge(V, ini, meio, fim, n);
    }
}

void Merge(Ponto V[], int ini, int meio, int fim, int n) {
    int i, j, k;
    int n1 = meio - ini + 1;
    int n2 = fim - meio;

    Ponto *L = malloc(n1 * sizeof(Ponto));
    Ponto *R = malloc(n2 * sizeof(Ponto));

    for (i = 0; i < n1; i++) {
        L[i] = V[ini + i];
    }
    for (j = 0; j < n2; j++) {
        R[j] = V[meio + 1 + j];
    }

    i = 0;
    j = 0;
    k = ini;

    while (i < n1 && j < n2) {
        if (comparaVertice(&L[i], &R[j]) < 0) {
            V[k] = L[i];
            i++;
        } else {
            V[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        V[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        V[k] = R[j];
        j++;
        k++;
    }

    free(L);
    free(R);
}

void InsertionSort(Ponto V[], int ini, int fim) {
    int i, j;
    Ponto key;
    for (i = ini + 1; i <= fim; i++) {
        key = V[i];
        j = i - 1;

        while (j >= ini && comparaVertice(&V[j], &key) > 0) {
            V[j + 1] = V[j];
            j = j - 1;
        }
        V[j + 1] = key;
    }
}
