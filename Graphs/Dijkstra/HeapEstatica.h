#ifndef HEAPESTATICA_H
#define	HEAPESTATICA_H
#include "Item.h"

typedef struct heap_estatica HEAP_ESTATICA;

HEAP_ESTATICA *criar_heap();
void apagar_heap(HEAP_ESTATICA **heap);
int enfileirar(HEAP_ESTATICA *heap, ITEM *item);
ITEM *desenfileirar(HEAP_ESTATICA *heap);
int cheia(HEAP_ESTATICA *heap);
int vazia(HEAP_ESTATICA *heap);
int tamanho(HEAP_ESTATICA *heap);

#endif

