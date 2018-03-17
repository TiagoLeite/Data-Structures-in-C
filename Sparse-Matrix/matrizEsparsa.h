#ifndef MATRIZ_ESPARSA_H
#define MATRIZ_ESPARSA_H

typedef struct celula CELULA;
typedef struct matrizEsparsa MATESPARSA;

MATESPARSA *cria(int lin, int col);
double get(MATESPARSA *mat, int i, int j);
int set(MATESPARSA *mat, int i, int j, double value);
MATESPARSA *add(MATESPARSA *matA, MATESPARSA *matB);
MATESPARSA *mult(MATESPARSA *matA, MATESPARSA *matB);
void print(MATESPARSA *mat);
void apagar(MATESPARSA **mat);

#endif