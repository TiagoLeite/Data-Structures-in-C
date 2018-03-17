#include "grafo.h"
#include "HeapEstatica.h"
#include "Item.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct vertice
{
	int ligacao, peso; //ligacao: flag que indice se há ligacao entre dois vertices
};

struct grafoMatriz
{
	VERTICE **mat;
	int direcionado;
};

GRAFOMATRIZ* criaGrafoMatriz(int numVert, int direcionado) //cria o grafo
{
	int i, j;
	GRAFOMATRIZ *graf = (GRAFOMATRIZ*)malloc(sizeof(GRAFOMATRIZ));
	if(graf == NULL)
		return NULL;
	graf->mat = (VERTICE**)malloc(numVert*sizeof(VERTICE*));
	if(graf->mat == NULL)
		return NULL;
	
	for(i = 0; i < numVert; ++i)
	{
		graf->mat[i] = (VERTICE*)malloc((numVert+1)*sizeof(VERTICE));
		if(graf->mat[i] == NULL)
			return NULL;
	}

	for (i = 0; i < numVert; ++i)//inicializa a matriz com zeros (= sem ligacao)
		for (j = 0; j < numVert; ++j)
			graf->mat[i][j].ligacao = 0;

	if(direcionado)
		graf->direcionado = 1;
	else
		graf->direcionado = 0;

	return graf;
}

GRAFOMATRIZ *apagaGrafoMatriz(GRAFOMATRIZ *graf, int numVert)//apaga o grafo, liberando memoria
{
	int i;
	if(graf == NULL)
		return NULL;
	for (i = 0; i < numVert; ++i)
		free(graf->mat[i]);
	free(graf->mat);
	free(graf);
	graf = NULL;
	return graf;
}

int addArestaMat(GRAFOMATRIZ *graf, int x, int y, int peso) //adiociona aresta
{
	if(graf == NULL)
		return 0;
	graf->mat[x][y].ligacao = 1;
	graf->mat[x][y].peso = peso;
	if(!(graf->direcionado)) //se nao for direcioando, adiciona mutuamente
	{
		graf->mat[y][x].ligacao = 1; //seta ligacao como verdadeiro (=> há ligação)
		graf->mat[y][x].peso = peso;  //atribui o peso
	}
	return 1;
}

int* Dijkstra(int numVert, GRAFOMATRIZ *graf, int vOrigem)
{
	int i, j;
	int *dist = (int*)malloc(numVert*sizeof(int));
	int *pred = (int*)malloc(numVert*sizeof(int));
	if(dist == NULL || pred == NULL)
		return NULL;
	for(i=0; i < numVert; i++)
	{
		dist[i] = INT_MAX;
		pred[i] = -1;
	}

	dist[vOrigem] = 0;
	HEAP_ESTATICA *heap = criar_heap();

	for(i=0; i < numVert; i++)
		enfileirar(heap, criar_item(dist[i], i));//cria item na heap como a chave sendo a distancia e valor sendo o numero do vertice
	
	while(!vazia(heap))
	{
		ITEM *u = desenfileirar(heap);
		for(j=0; j < numVert; j++) //percorre os vertices ligados a u
		{
			if( graf->mat[getValorItem(u)][j].ligacao) //se ha ligacao entre os vertivces
			{
				if( dist[getValorItem(u)] == INT_MAX)
					continue; 
				if( dist[getValorItem(u)] + graf->mat[getValorItem(u)][j].peso < dist[j] )
				{
					dist[j] = dist[getValorItem(u)]  + graf->mat[getValorItem(u)][j].peso;
					pred[j] = getValorItem(u); //atualiza vetor predecessor
					enfileirar(heap, criar_item(dist[j], j));
				}
			}
		}
		apagar_item(&u); //pra liberar memoria
	}
	free(dist);
	free(heap);
	return pred; //retorna o vetor predecessor
}
