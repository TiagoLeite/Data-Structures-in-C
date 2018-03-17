#include "HeapEstatica.h"
#include "grafo.h"
#include <stdio.h>
#include <stdlib.h>

void imprimeCaminho(int *pred, int orig, int dest, int *flag);

int main(int argc, char** argv) 
{
	GRAFOMATRIZ *graf;
  	HEAP_ESTATICA *heap; 
  	int nVertices, nArestas, x, y, peso, i, flag;
  	int *pred;  //predecessor

  	scanf("%d %d", &nVertices, &nArestas);
	graf = criaGrafoMatriz(nVertices, 1); //1 significa digrafo
	
	for(i = 0; i < nArestas; ++i) //adicionar arestas: (x -> y) e (y -> x)
	{
		scanf("%d %d %d", &x, &y, &peso);
		addArestaMat(graf, x, y, peso);
	}

	while(scanf("%d %d", &x, &y) != EOF)
	{
		pred = Dijkstra(nVertices, graf, x);
		flag  = 1; 				//flag que indica ausencia de caminho
		imprimeCaminho(pred, x, y, &flag);
		printf("\n");
		free(pred);
	}
	graf = apagaGrafoMatriz(graf, nVertices);
  	return 0;
}

void imprimeCaminho(int *pred, int orig, int dest, int *flag)
{
	int temp;
	if(dest == orig)
	{
		printf("%d ", orig);
		return;
	}
	if(pred[dest] == -1)
	{
		*flag = 0;
		return;
	}
	temp = dest;
	dest = pred[dest];
	imprimeCaminho(pred, orig, dest, flag);
	if(flag)
		printf("%d ", temp);
}
