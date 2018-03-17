#include <stdio.h>
#include <stdlib.h>
#include "matrizEsparsa.h"

struct celula
{
	int lin, col;
	double valor;
	struct celula *dir; //direita
	struct celula *bxo; //baixo
};

struct matrizEsparsa
{
	CELULA **linhas, **colunas;
	int nlin, ncol;
};

MATESPARSA *cria(int lin, int col)
{
	int i;
	if(lin<1 || col<1)
		return NULL;
	MATESPARSA *matriz = (MATESPARSA*)malloc(sizeof(MATESPARSA));
	CELULA *cabeca; //nó cabeça
	if(matriz == NULL)
		return NULL;
	matriz->linhas = (CELULA**)malloc(lin*sizeof(CELULA*));
	matriz->colunas = (CELULA**)malloc(col*sizeof(CELULA*));
	matriz->nlin = lin;
	matriz->ncol = col;
	for(i=0; i<lin; i++) //coloca os nós cabeças nas listas
	{
		cabeca = (CELULA*)malloc(sizeof(CELULA));
		cabeca->dir = NULL;
		matriz->linhas[i] = cabeca;
	}
	for(i=0; i<col; i++)
	{
		cabeca = (CELULA*)malloc(sizeof(CELULA));
		cabeca->bxo = NULL;
		matriz->colunas[i] = cabeca;
	}

	return matriz;
}

double get(MATESPARSA *mat, int i, int j)  
{
	if(mat == NULL || i < 0 || j < 0 || i >= mat->nlin)
		return 0.0;
	CELULA *paux = mat->linhas[i]->dir; //começa a busca pela linha
	while(paux!=NULL && paux->col != j)
		paux = paux->dir; //vai percorrendo as colunas
	if(paux == NULL)
		return 0.0;
	return paux->valor;
}

int set(MATESPARSA *mat, int i, int j, double value) //seta um valor na matriz
{
	if(mat == NULL || i < 0 || i >= mat->nlin || j < 0 || j >= mat->ncol)
		return 0;
	CELULA *paux = mat->linhas[i]; //aponta pro nó cabeça
	CELULA *pnova = (CELULA*)malloc(sizeof(CELULA));

	//acertando o local de inserção, na linha:
	if(paux->dir == NULL) //se for o primeiro elemento da lista
	{
		paux->dir = pnova;
		pnova->dir = NULL;
	}
	else
	{
		while(paux->dir != NULL && paux->dir->col < j) //percorre a linha em busca da posição correta
			paux = paux->dir;
		if(paux->dir == NULL) //se estiver no fim da lista
		{
			paux->dir = pnova;
			pnova->dir = NULL;
		}
		else if(paux->dir->col == j) //se já houver um valor no local indicado, substitui só o valor
		{	
			paux->dir->valor = value;
			free(pnova); //libera a nova célula, ja que não vai mais ser usada
			return 1;
		}
		else //se estiver em algum lugar no meio da linha
		{
			pnova->dir = paux->dir;
			paux->dir = pnova;
		}
	}
	pnova->lin = i;
	pnova->col = j;
	pnova->valor = value;

	//acertando o local de inserção, na coluna
	paux = mat->colunas[j];
	while(paux->bxo != NULL && paux->bxo->lin < i) //percorre a coluna em busca da posição correta
		paux = paux->bxo;

	if(paux->bxo == NULL) //se for o primeiro da coluna
	{
		paux->bxo = pnova;
		pnova->bxo = NULL;
	}
	else
	{
		while(paux->bxo != NULL && paux->bxo->lin < i) //percorre a coluna em busca da posição correta
			paux = paux->bxo;
		if(paux->bxo == NULL) //se estiver no fim da coluna
		{
			paux->bxo = pnova;
			pnova->bxo = NULL;
		}
		else //se estiver em algum lugar no meio da coluna
		{
			pnova->bxo = paux->bxo;
			paux->bxo = pnova;
		}
	}
	return 1;
}

MATESPARSA *add(MATESPARSA *matA, MATESPARSA *matB)
{
	MATESPARSA *mat;
	CELULA *pauxA, *pauxB; //ponteiros auxiliares para percorrer as matrizes A e B
	int i, j;
	if(matA == NULL || matB == NULL)
		return NULL;
	if( matA->nlin != matB->nlin || matA->ncol != matB->ncol) //formatos diferentes de matrizes
		return NULL;
	mat = cria(matA->nlin, matA->ncol); //cria a matriz resultante
	if(mat == NULL)
		return NULL;
	for(i=0; i < mat->nlin; i++) //para variar as linhas das matrizes A e B
	{
		pauxA = matA->linhas[i]->dir;
		pauxB = matB->linhas[i]->dir;
		for(j=0; j < mat->ncol; j++) //para variar as colunas de A e B 
		{
			if(pauxA != NULL && pauxB != NULL)
			{
				if( (pauxA->lin == pauxB->lin) && (pauxA->col == pauxB->col) && (pauxA->valor + pauxB->valor != 0) ) //se os elementos de A e B tiverem a mesma linha, mesma coluna e não somarem zero
				{
					set(mat, pauxA->lin, pauxA->col, pauxA->valor + pauxB->valor);//cria a célula na matriz resultante
					pauxA = pauxA->dir;
					pauxB = pauxB->dir;
				}
				else
				{
					if(pauxA->col < pauxB->col) //nesse caso, cria na matriz resultante uma célula igual a da matriz A
					{
						set(mat, pauxA->lin, pauxA->col, pauxA->valor);
						pauxA = pauxA->dir;
					}
					else if(pauxB->col < pauxA->col)
					{
						set(mat, pauxB->lin, pauxB->col, pauxB->valor); //cria na matriz resultante uma célula igual a da matriz B
						pauxB = pauxB->dir;
					}
				}
			}
			else if(pauxA != NULL) //cria na matriz resultante uma célula igual a da matriz A
			{
				set(mat, pauxA->lin, pauxA->col, pauxA->valor);
				pauxA = pauxA->dir;
			}
			else if(pauxB != NULL) //cria na matriz resultante uma célula igual a da matriz B
			{
				set(mat, pauxB->lin, pauxB->col, pauxB->valor);
				pauxB = pauxB->dir;
			}
			
		}

	}
	return mat;
}

MATESPARSA *mult(MATESPARSA *matA, MATESPARSA *matB)
{
	MATESPARSA *mat;
	CELULA *pauxA, *pauxB; //ponteiros auxiliares para percorrer as matrizes A e B
	double soma;
	int i, j;
	if(matA == NULL || matB == NULL || (matA->ncol != matB->nlin))
		return NULL;
	mat = cria(matA->nlin, matB->ncol);
	for(i=0; i < matA->nlin; ++i) //varia as linhas de A
	{
		pauxA = matA->linhas[i]->dir;
		if(matA->linhas[i]->dir != NULL)
		{
			for(j=0; j < matB->ncol; ++j) //varia as colunas de B
			{
				pauxB = matB->colunas[j]->bxo;
				soma = 0;
				while(pauxA != NULL && pauxB != NULL)
				{
					if(pauxA->col == pauxB->lin)//a coluna do elemento de A deve coincidir com a linha do elemento de B, para que haja a multiplicação dos elementos 
					{
						soma += (pauxA->valor)*(pauxB->valor);
						pauxA = pauxA->dir;
						pauxB = pauxB->bxo;
					}
					else if(pauxA->col < pauxB->lin)
						pauxA = pauxA->dir;
					else
						pauxB = pauxB->bxo;
				}
				if(soma != 0)
				{
					set(mat, i, j, soma);
				}
				pauxA = matA->linhas[i]->dir;//recomeça na linha, para calcular o próximo elemento
			}
		}
	}
	return mat;
}

void print(MATESPARSA *mat)
{
	if(mat == NULL)
		return;
	int i;
	for(i=0; i < mat->nlin; i++)
	{
		CELULA *paux = mat->linhas[i]->dir;
		while(paux != NULL)
		{
			if(paux->valor != 0)
			printf("%d %d: %.2lf\n", paux->lin, paux->col, paux->valor);
			paux = paux->dir;
		}
	}
}

void apagar(MATESPARSA **mat)
{
	if(mat == NULL || *mat == NULL)
		return;
	CELULA *paux, *prem; //ponteiro auxiliar e ponteiro de remoção
	int i;
	for(i=0; i < (*mat)->nlin; ++i) //vai apagando as linhas
	{
		paux = (*mat)->linhas[i];
		while(paux != NULL)
		{	
			prem = paux;
			paux = paux->dir;
			free(prem);
		}
	}
	for ( i=0; i < (*mat)->ncol; ++i) //apaga os nós cabeças das colunas
	{
		paux = (*mat)->colunas[i];
		free(paux);
	}
	free( (*mat)->linhas );
	free( (*mat)->colunas);
	free(*mat);
	*mat = NULL;
}
