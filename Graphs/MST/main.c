#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"
#include "lista.h"

int main(int argc, char const *argv[])
{
	int vertices, arestas;
	int i, x, y, peso, menorSoma, pesoTotal=0;

	GRAFOMATRIZ *graf; //grafo como matriz de adjacencias

	scanf("%d %d", &vertices, &arestas);

	graf = criaGrafoMatriz(vertices, 0); // 0 significa grafo nao direcionado

	for(i = 0; i < arestas; ++i) //adicionar arestas: (x -> y) e (y -> x)
	{
		scanf("%d %d %d", &x, &y, &peso);
		addArestaMat(graf, x, y, peso);
		pesoTotal += peso;
	}
	menorSoma = Prim(graf, vertices);
	apagaGrafoMatriz(graf, vertices);
	printf("%d %d\n", pesoTotal, menorSoma);
	return 0;
}
