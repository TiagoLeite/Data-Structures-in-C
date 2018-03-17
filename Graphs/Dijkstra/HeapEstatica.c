#include "HeapEstatica.h"
#include <stdlib.h>
#define TAM 10000 //tamanho maximo da heap

struct heap_estatica
{
	ITEM * vetor[TAM];
  	int fim;
};

HEAP_ESTATICA *criar_heap()
{
	HEAP_ESTATICA *heap = (HEAP_ESTATICA *) malloc(sizeof (HEAP_ESTATICA));
  	if (heap == NULL)
  		return NULL;
    heap->fim = -1;
  	return heap;
}

void apagar_heap(HEAP_ESTATICA **heap)
{
	int i = 0;
 	for (i = 0; i < (*heap)->fim; i++)
 	{
    	apagar_item(&((*heap)->vetor[i]));
  	}
  	free(*heap);
  	*heap = NULL;
}

void troca(HEAP_ESTATICA *heap, int i, int j)
{
	ITEM *temp = heap->vetor[i];
  	heap->vetor[i] = heap->vetor[j];
  	heap->vetor[j] = temp;
}

void fix_up(HEAP_ESTATICA *heap)
{
	int pos = heap->fim;
	int pai = (pos-1)/2;
	while (pos > 0 && heap->vetor[pos]->chave < heap->vetor[pai]->chave)
	{
	   troca(heap, pos, pai);
	   pos = pai;
	   pai = (pai-1)/2;
	}
}

int enfileirar(HEAP_ESTATICA *heap, ITEM *item)
{
  	if(cheia(heap))
  		return 0;
	heap->fim++;
	heap->vetor[heap->fim] = item;
	fix_up(heap);
	return 1;
}

void fix_down(HEAP_ESTATICA *heap)
{
  	int pos = 0;
  	while (pos <= heap->fim / 2)
  	{
    	int filhoesq = 2*pos+1;
    	int filhodir = 2*pos+2;
    	int menorfilho;
    	if (filhodir <= heap->fim && heap->vetor[filhoesq]->chave > heap->vetor[filhodir]->chave)
      		menorfilho = filhodir;
    	else
      		menorfilho = filhoesq;
	    if(heap->vetor[pos]->chave <= heap->vetor[menorfilho]->chave)
	    	break;
	    troca(heap, pos, menorfilho);
	    pos = menorfilho;
  	}
}

ITEM *desenfileirar(HEAP_ESTATICA *heap)
{
	if(vazia(heap))
		return NULL;
	ITEM *item = heap->vetor[0]; // = raiz
	heap->vetor[0] = heap->vetor[heap->fim];
	heap->fim--;
	fix_down(heap);
	return item;
}

int cheia(HEAP_ESTATICA *heap)
{
	return (heap->fim == TAM - 1);
}

int vazia(HEAP_ESTATICA *heap) {
  return (heap->fim == -1);
}

int tamanho(HEAP_ESTATICA *heap)
{
	return heap->fim + 1;
}