#ifndef MERGESORT_H
#define MERGESORT_H
#include "ponto.h"

//programa para ordenação por mergesort e insertion sort.

void MergeSort(Ponto V[], int ini, int fim, int n);
//função principal do mergesort

void Merge(Ponto V[], int ini, int meio, int fim, int n);
//função que faz a intercalação dos vetores

void InsertionSort(Ponto V[], int ini, int fim);
//função do insertion sort

#endif