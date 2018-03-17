#include <stdlib.h>
#include "vector.h"

struct vector 
{
    int last, capacity;
    ITEM **items;
};

Vector *vector_new(int capacity) 
{
    if(capacity <= 0)
        return NULL;
    Vector *pVec = (Vector*)malloc(sizeof(Vector));
    if(pVec == NULL)
        return NULL;
    pVec->items = (ITEM**)malloc(capacity*sizeof(ITEM*)); //aloca dinamicamente o vetor de ponteiros
    if(pVec->items == NULL)
        return NULL;
    pVec->last = -1;
    pVec->capacity = capacity;
    return pVec;  
}

void vector_free(Vector **vec) 
{
    int i;
    if(vec == NULL || *vec == NULL)
        return;
    for(i=0; i <= (*vec)->last; i++)
    {
        free((*vec)->items[i]);    //libera a memoria onde estava cada item armazenado
    }
    free( (*vec)->items );         //libera a memoria onde o ponteiro "items" apontava
    free(*vec);                    //libera a memoria do Vector apontado por vec 
    *vec = NULL;
}

int vector_size(const Vector *vec) 
{
    if(vec == NULL)
        return 0;
    return ( (vec->last) + 1);   //retorna o numero de elementos armazenados: soma 1 ao (vec->last) pois este começa do -1
}

int vector_capacity(const Vector *vec) 
{
    if(vec == NULL)
        return 0;
    return ( vec->capacity );
}

int vector_empty(const Vector *vec) 
{
    if(vec == NULL || vec->last ==-1)
        return 1;
    return 0;
}

int vector_add(Vector *vec, ITEM *item) 
{
    if(item == NULL)
        return 0;
    if(vec == NULL)
    {
        item_free(&item);  //libera a regiao de memoria que armazenava o item
        return 0;
    }
    if( vector_size(vec) == vector_capacity(vec)-1 )  //se for encher a capacidade do Vector...
    {
        (vec->capacity) *= 2;                         //...dobra seu tamanho
        vec->items = (ITEM**)realloc(vec->items, (vec->capacity)*sizeof(ITEM*) );  //realoca a memoria, agora com o dobro da capacidade
        vec->items[(vec->last)+1] = item;    //salva o item no Vector
        (vec->last)++;
        return 1;
    }
    //se nao encher o Vector, apenas acrescenta o item
    vec->items[(vec->last)+1] = item;
    (vec->last)++;
    return 1;
}

ITEM *vector_remove(Vector *vec, int key) {
    int i, j;
    ITEM *p;    //para retornar o item
    if(vec == NULL)
        return NULL;
    for(i=0; i <= (vec->last); i++)
    {
        if( vec->items[i]->key == key ) //procura pela key
        {   
            p = vec->items[i];  //"salva" o item em p
            for(j=i; j< vec->last; j++)
            {
                vec->items[j] = vec->items[j+1]; //os elementos posteriores ao elemento removido são deslocados de 1 unidade para "trás"
            }
            vec->items[vec->last] = NULL;
            (vec->last)--;
            return p;
        }
    }
    return NULL; //se nao achar a key
}

ITEM *vector_get(const Vector *vec, int key) {
    int i;
    if(vec == NULL)
        return NULL;
    for(i=0; i <= (vec->last); i++)
    {
        if( vec->items[i]->key == key )
        {   
            return (vec->items[i]); //retorna o item com a key procurada
        }
    }
    return NULL; //se nao encontrar a key
}

ITEM *vector_at(const Vector *vec, int pos) {
    if(vec == NULL || pos < 0 || pos > (vec->last) )
        return NULL;
    return vec->items[pos];  //retorna o item situado em dada posicao
}

Vector *vector_copy(Vector *dst, const Vector *src) {
    int i, add; //esse "add" serve apenas para chamar a funcao "vector_add"
    if(dst == NULL || src == NULL)
        return NULL;
    for(i=0; i<= dst->last; i++)
    {
        item_free( &(dst->items[i]) );  //libera os itens previamente presentes no Vector de destino
    }
    dst->last  = -1;
    for (i=0; i<= src->last ; i++)
    {
       add = vector_add(dst, item_copy(src->items[i])); //adiciona cada item de src ao dst 
    }
    return dst;
}

Vector *vector_rev(Vector *rev, const Vector *vec) {
    int i, add;
    if(rev == NULL || vec == NULL)
        return NULL;
    for(i=0; i<= rev->last; i++)
    {
        item_free( &(rev->items[i]) );
    }
    rev->last = -1;
    for (i=0; i<= vec->last ; i++)
    {
       add = vector_add(rev, item_copy(vec->items[(vec->last) - i]));  //adiciona os itens de vec ao rev, em ordem contrária 
    }
    return rev;
}

Vector *vector_cat(const Vector *vec1, const Vector *vec2, Vector *cat) {
    int i, add;
    if(vec1 == NULL || vec2 == NULL || cat == NULL)
        return NULL;
    cat = vector_copy(cat, vec1);  //primeiro copia os itens de vec1 ao cat, usando a funcao já pronta "vector_copy"
    for(i=0; i<= vec2->last; i++)
    {
        if( vector_size(cat) == vector_capacity(cat)-1 )
        {
            (cat->capacity) *= 2;  //dobra a capacidade de cat se for necessário
            cat->items = (ITEM**)realloc(cat->items, (cat->capacity)*sizeof(ITEM*) );
            cat->items[(cat->last)+1] = item_copy(vec2->items[i]);  //copia o item de vec2 ao cat
            (cat->last)++;
        }
        else
            add = vector_add(cat, item_copy(vec2->items[i]));  //copia o item de vec2 ao cat
    }
    return cat;
}

void vector_print(const Vector *vec) {
    if (vec != NULL) {
        int i;
        for (i = 0; i <= vec->last; i++)
            item_print(vec->items[i]);
    }
}
