#include <stdio.h>
#include <stdlib.h>
#include "array_list.h"
#define CAPACITY 10

typedef struct node Node;
struct node 
{
    int last;
    ITEM *items[CAPACITY];
    Node *next;
};

struct array_list 
{
    Node *firstNode, *lastNode;
    int size;
};

ArrayList *list_new() 
{
    int i;
    ArrayList *pArray = (ArrayList*)malloc(sizeof(ArrayList));
    if(pArray == NULL)
        return NULL;
    Node *pNode = (Node*)malloc(sizeof(Node));
    if(pNode == NULL)
    {
        free(pArray);
        return NULL;
    }
    for (i=0; i < CAPACITY; ++i)
        pNode->items[i] = NULL; 
    pNode->next = NULL;
    pNode->last = -1;
    pArray->firstNode = pNode;
    pArray->lastNode = pNode;
    pArray->size = 0;
    return pArray;
}

void list_free(ArrayList **list)
{
    Node *paux, *prem; //ponteiro auxiliar e de remoção
    int i;
    if(list == NULL || *list == NULL)
        return;
    paux  = (*list)->firstNode;
    prem = paux;
    while(paux!=NULL)//apaga do inicio ao fim da lista
    {
        for(i=0; i<= paux->last; i++)
            item_free(&(paux->items[i]));
        paux = paux->next;
        free(prem);
        prem = paux;
    }
    (*list)->firstNode = NULL;
    (*list)->lastNode = NULL;
    free(*list);
    (*list) = NULL;
}

int list_size(const ArrayList *list)
{
    if(list == NULL)
        return 0;    
    return (list->size);
}

int list_empty(const ArrayList *list)
{
    if(list == NULL || list_size(list) == 0)
        return 1;
    return 0;
}

int list_add(ArrayList *list, ITEM *item)
{
    int i;
    Node *pNode;//para criar um possível novo nó
    Node *paux; //usado para achar a posicao de inserção
    ITEM *psalva; //salva o endereço do item que será deslocado
    ITEM *pinsert;//para salvar o endereço do item a ser inserido
    if(item == NULL)
        return 0;
    if(list == NULL)
    {
        item_free(&item);
        return 0;
    }

    if(list_empty(list)) //se a lista estivet vazia...
    {
        list->firstNode->items[++(list->firstNode->last)] = item; //...insere no início
        (list->size)++;
        return 1;
    }

    paux = list->firstNode;
    while(paux != list->lastNode) //vai descobrir o nó onde o item será inserido, ou chegar ao último se não achar
    {
        if( paux->items[paux->last]->key >= item->key )//se achar, na ultima posicao do array de um nó, uma chave maior ou igual a que vai inserir, para
            break;
        paux = paux->next;
    }
    for(i=0; i<= paux->last; i++)
    {
        if( paux->items[i]->key == item->key )//se a chave for igual, substitui o item anterior
        {
            item_free(&paux->items[i]);
            paux->items[i] = item;
            return 1; //termina
        }
        if( paux->items[i]->key > item->key )//procura a chave ao longo do array, dentro do nó
            break;
    }

    if(i==CAPACITY) //se isso ocorrer, significa que o item será inserido na última posicao da lista, em um novo nó
    {
        pNode = (Node*)malloc(sizeof(Node));
        if(pNode == NULL)
                return 0;
        for (i=0; i < CAPACITY; ++i)
             pNode->items[i] = NULL; 
        pNode->next = NULL;
        pNode->last = -1;
        list->lastNode->next = pNode;
        list->lastNode = pNode;
        paux = pNode;
        i = 0;//atualiza o indice, já que agora está no começo de um novo vetor  
    }
    pinsert = item;
    while(paux->items[i] != NULL)
    {
        psalva = paux->items[i];//salva o item, para o anterior ocupar seu lugar (deslocamento de itens para frente)
        paux->items[i] = pinsert;
        pinsert = psalva;
        i++;
        if(i==CAPACITY) //se chegou ao fim da array
        {
            if(paux == list->lastNode)//se estiver no ultimo nó, cria mais um
            {
                pNode = (Node*)malloc(sizeof(Node));
                if(pNode == NULL)
                        return 0;
                for (i=0; i < CAPACITY; ++i)
                    pNode->items[i] = NULL; 
                pNode->next = NULL;
                pNode->last = -1;
                list->lastNode->next = pNode;
                list->lastNode = pNode;
                paux = pNode;
                i = 0;
            }
            else //se não for o último nó, vai para o próximo nó
            {
                paux = paux->next;
                i = 0;
            }
        }
    }
    paux->items[i] = pinsert; //insere o ultimo item
    (list->lastNode->last)++; //incrementa a posicao do último ítem no último nó
    (list->size)++;
    return 1;
}

ITEM *list_remove(ArrayList *list, int key)
{
    Node *paux;//para percorrer a lista
    ITEM *removed; //para retornar o item removido
    int i;
    if(list == NULL)
        return NULL;
    paux = list->firstNode;
    while(paux != list->lastNode)//descobrir o nó de onde o item sera removido, fazendo busca sequencial nos nós
    {
        if( paux->items[paux->last]->key >= key )//compara a chave com a última chave de cada nó
            break;
        paux = paux->next;
    }

    for (i=0; i<=paux->last ; ++i) //busca sequencial no vetor, à procura da chave
    {
        if(paux->items[i]->key == key)
        {
            removed = paux->items[i];
            break;
        }
    }

    if(i==paux->last +1) //se nao achou a key
        return NULL; //termina

    while(paux->items[i]!= NULL)
    {
        if(i==CAPACITY-1)//se for o último item do vetor, copia o primeiro item do vetor do nó seguinte
        {
            if(paux != list->lastNode)
            {
                paux->items[i] = paux->next->items[0];
                paux = paux->next;
                i = 0;
            }
            else //mas se nao houver nó seguinte, joga NULL nesse item e acaba
            {
                paux->items[i] = NULL;
                (paux->last)--;
                (list->size)--;
                return removed;
            }
            
        }
        else //se naõ for o item último do vetor, copia o pŕoximo nele
        {
            paux->items[i] = paux->items[i+1];
            i++;
        }
    }
    (list->lastNode->last)--;
    if(list->lastNode->items[0] == NULL && list->lastNode != list->firstNode)//caso o último nó fique vazio, apaga-o
    {
        paux = list->firstNode;
        while(paux->next != list->lastNode)//isto servirá para reposicionar o ponteiro que aponta para o último nó da lista
            paux = paux->next;
        free(list->lastNode);
        list->lastNode = paux;
        list->lastNode->next = NULL;
    }
    (list->size)--;
    return removed;   
}

ITEM *list_get(const ArrayList *list, int key)
{
    Node *paux;
    int i, j, meio;
    if(list == NULL)
        return NULL;
    paux = list->firstNode;
    while(paux != NULL && paux->items[paux->last]->key < key)//busca sequencial nos nós
        paux = paux->next;
    if(paux == NULL)//não achou
        return NULL;
    i = 0;
    j = paux->last;
    meio = (i+j)/2;
    while(i<=j) //busca binária no vetor
    {
        if(paux->items[meio]->key == key)
            return paux->items[meio];
        else if(paux->items[meio]->key < key)
        {
            i = meio+1;
            meio = (i+j)/2;
        }
        else
        {
            j = meio-1;
            meio = (i+j)/2; 
        }
    }
    return NULL;
}

ITEM *list_at(const ArrayList *list, int pos)
{
    Node *paux;
    int i, n;
    if(list == NULL || pos >= list->size || pos < 0)
        return NULL;
    paux = list->firstNode;
    n = pos/CAPACITY; // n significa o número de nós que podemos "pular"
    for (i=0; i<n; ++i)
        paux = paux->next;
    pos = pos-n*CAPACITY; //posicao do item no vetor
    return paux->items[pos];
}

void list_print(const ArrayList *list) {
    if (list != NULL) {
        Node *node;
        int i;

        for (node = list->firstNode; node != NULL; node = node->next) {
            printf("-- node:\n");
            for (i = 0; i <= node->last; i++)
                item_print(node->items[i]);
        }
    }
}
