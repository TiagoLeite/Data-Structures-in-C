#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

LISTA *cria()
{
    LISTA *lista = (LISTA*)malloc(sizeof(LISTA));
    if(lista == NULL)
        return NULL;
    lista->inicio = NULL;
    lista->fim = NULL;
    lista->tam = 0;
    return lista;
}

int vazia(LISTA *plista)
{
    return (plista == NULL || plista->inicio == NULL);
}

void imprimeFila(LISTA *lista)
{
    if(lista == NULL || lista->inicio == NULL)
        return;
    NO *paux = lista->inicio;
    while(paux!= NULL)
    {
        printf("%d ", paux->valorVertice);
        paux = paux->prox;
    }
}

int inserirInicio(LISTA *lista, int valorVertice)
{
    if(lista == NULL)
        return 0;
    NO *pno = (NO*)malloc(sizeof(NO));
    if(pno == NULL)
        return 0;
    pno->valorVertice = valorVertice;
    pno->prox = lista->inicio;
    lista->inicio = pno;
    (lista->tam)++;
    if(lista->fim == NULL)//vazia
        lista->fim = pno;
    return 1;
}

void esvazia(LISTA **lista) //libera memoria
{
    if(vazia(*lista))
    {
        free(*lista);
        (*lista) = NULL;
        return;
    }
    NO *prem = (*lista)->inicio;
    (*lista)->inicio = (*lista)->inicio->prox;
    free(prem);
    prem = NULL;
    esvazia(lista);
}
