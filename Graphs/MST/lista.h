#ifndef LISTA_H
#define LISTA_H

typedef struct no 
{
	int valorVertice;
	struct no *prox;
}NO;

typedef struct
{
	NO *inicio, *fim;
	int tam;
}LISTA;

LISTA *cria();
int vazia(LISTA *plista);
void imprimeFila(LISTA *lista);
int inserirInicio(LISTA *lista, int valorVertice);
void esvazia(LISTA **lista);

#endif
