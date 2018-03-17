#include "Item.h"
#include <stdlib.h>
#include <stdio.h>

ITEM *criar_item(int chave, int valor)
{
    ITEM *item = (ITEM *)malloc(sizeof(ITEM));
    item->chave = chave;
    item->valor = valor;
    return item;
}

int getValorItem(ITEM *item)
{
	return item->valor;
}

void apagar_item(ITEM **item)
{
  if (item != NULL)
  {
    free(*item);
    *item = NULL;
  }
}
