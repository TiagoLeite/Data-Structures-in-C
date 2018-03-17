#ifndef GRAFO_H
#define GRAFO_H

#include "lista.h"

typedef struct vertice VERTICE;
typedef struct grafoMatriz GRAFOMATRIZ;

GRAFOMATRIZ* criaGrafoMatriz(int numVert, int direcionado);
GRAFOMATRIZ *apagaGrafoMatriz(GRAFOMATRIZ *graf, int numVert);
int addArestaMat(GRAFOMATRIZ *graf, int x, int y, int peso);
int Prim(GRAFOMATRIZ *graf, int numVert);

#endif