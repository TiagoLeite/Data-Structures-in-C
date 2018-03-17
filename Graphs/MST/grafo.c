#include "grafo.h"
#include "lista.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define BRANCO 0
#define PRETO 2

struct vertice
{
	int ligacao, cor, peso;
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
	for (i = 0; i < numVert; ++i)//inicializa a matriz com zeros e cores dos vertices como branco
	{
		graf->mat[i][numVert].cor = BRANCO; //cor vai usar no prim
		for (j = 0; j < numVert; ++j)
		{
			graf->mat[i][j].ligacao = 0;
		}
	}
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
		graf->mat[y][x].ligacao = 1;
		graf->mat[y][x].peso = peso;
	}
	return 1;
}

int Prim(GRAFOMATRIZ *graf, int numVert)
{
	NO *no;  //para percorrer os nós da lista
	int menorPeso, menorVertice;
	int i, menorSoma = 0;
	LISTA *lista = cria(); //lista para armazenar os vertices já usados (pretos)
	if(lista == NULL)
		return -1;

	inserirInicio(lista, 0); //começa do vertice zero
	graf->mat[0][numVert].cor = PRETO;

	while(lista->tam < numVert)
	{
		no = lista->inicio;
		menorPeso = 2147483647;
		while(no != NULL) //percorre a lista de vertices verificando a proxima aresta com menor peso a escolher
		{
			for(i=0 ; i < numVert; i++)
			{
				if(graf->mat[no->valorVertice][i].ligacao && (graf->mat[no->valorVertice][i].peso < menorPeso) && graf->mat[i][numVert].cor == BRANCO )
				{
					menorPeso =  graf->mat[no->valorVertice][i].peso;
					menorVertice = i;
				}
			}
			no = no->prox;
		}
		graf->mat[menorVertice][numVert].cor = PRETO;
		menorSoma += menorPeso;
		inserirInicio(lista, menorVertice); //cada vertice preto entra na lista
	}
	esvazia(&lista);
	return menorSoma; //retorna a soma dos pesos das arestas da arvore geradora minima
}
