#ifndef ITEM_H
#define	ITEM_H

typedef struct
{
	int chave;
  	int valor;
}ITEM;

ITEM *criar_item(int chave, int valor);
void apagar_item(ITEM **item);
void imprimir_item(ITEM *item);
int getValorItem(ITEM *item);
int getChaveItem(ITEM *item);

#endif

