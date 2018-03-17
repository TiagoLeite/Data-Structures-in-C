#include "rbtree.h"
#include <stdio.h>
#include <stdlib.h>
#define RED 1
#define BLACK 0
#define ESQ 0
#define DIR 1

typedef struct no
{
	ITEM *item;
	struct no *fesq;
	struct no *fdir;
	struct no *pai;
	int cor;
}NO;

struct rbtree
{
	NO *raiz;
	NO *sentinela; //nó sentinela para facilitar, para os filhos das folhas apontarem
};

RBTree *rbtree_new()
{
	RBTree *ptree = (RBTree*)malloc(sizeof(RBTree));
	if(ptree == NULL)
		return NULL;
	ptree->sentinela = (NO*)malloc(sizeof(NO));
	ptree->sentinela->cor = BLACK; //sentinela preto
	ptree->raiz = NULL;
	return ptree;
}

int roda_esq(RBTree *tree, NO *x) //rotação à esquerda - será utilizada na inserção e remoção
{
	if(x == NULL)
		return 0;
	NO *y = x->fdir; //seta y como filho direito de x
	x->fdir = y->fesq; 
	y->fesq->pai = x; //subárvore esqueda de y agora é a subárvore direita de x
	y->pai = x->pai;
	if(x->pai == tree->sentinela) //se x era raiz, agora y será
		tree->raiz = y;
	else if(x == x->pai->fesq)
		x->pai->fesq = y;
	else
		x->pai->fdir = y; //liga y a seu pai
	y->fesq = x; //liga y como pai de x
	x->pai = y; //liga x como filho de y
	return 1;
}

int roda_dir(RBTree *tree, NO *x) //rotação à direita, também usada na remoção e inserção, análoga à rotação à esquerda
{
	if(x == NULL)
		return 0;
	NO *y = x->fesq;
	x->fesq = y->fdir;
	y->fdir->pai = x;
	y->pai = x->pai;
	if(x->pai == tree->sentinela)
		tree->raiz = y;
	else if(x == x->pai->fesq)
		x->pai->fesq = y;
	else
		x->pai->fdir = y;
	y->fdir = x;
	x->pai = y;
	return 1;
}

int vazia(RBTree *tree)
{
	return (tree->raiz == NULL || tree->raiz == tree->sentinela);
}

int criaRaiz(RBTree *tree, ITEM *item)//insere um nó raiz na árvore
{	
	if(tree == NULL)
		return 0;
	tree->raiz = (NO*)malloc(sizeof(NO));
	if(tree->raiz == NULL)
		return 0;
	tree->raiz->item = item;
	tree->raiz->fesq = tree->sentinela;
	tree->raiz->fdir = tree->sentinela;
	tree->raiz->cor = BLACK;
	tree->raiz->pai = tree->sentinela;
	return 1;
}

int adicionaFilho(int filho, NO *pno, ITEM *pitem, RBTree *tree)//adiciona filho à direita ou esquerda num nó
{
	if(pno == NULL || pitem == NULL)
		return 0;
	NO *pnovoNo = (NO*)malloc(sizeof(NO));
	if(pnovoNo == NULL)
		return 0;
	pnovoNo->fesq = tree->sentinela;
	pnovoNo->fdir = tree->sentinela;
	pnovoNo->item = pitem;
	pnovoNo->cor = RED; //cor do nó a inserir é vermelho, pelas regras da árvore vermelho-preto
	if(filho == DIR)
		pno->fdir = pnovoNo;
	else
		pno->fesq = pnovoNo;
	pnovoNo->pai = pno;
	return 1;
}

void arruma_arvore(RBTree *tree, NO *pai, NO *x)//arruma a árvore após a inserção, para manter as propriedades, fazendo rotações ou recolorações
{
	if(pai->cor == BLACK)//caso 0: pai preto - não faz mais nada
		return;
	NO *tio, *avo;
	avo = pai->pai;
	if(pai==avo->fdir)
		tio = avo->fesq;
	else
		tio = avo->fdir;
	if(pai->cor == RED && tio->cor == BLACK)//caso 1: pai vermelho e tio preto - fazer rotações
	{
		if(x==pai->fesq && pai==avo->fesq) 
		{
			roda_dir(tree, avo);
			avo->cor = RED;
			pai->cor = BLACK;
			return;
		}
		
		if(x==pai->fdir && pai==avo->fdir) 
		{
			roda_esq(tree, avo);
			avo->cor = RED;
			pai->cor = BLACK;
			return;
		}
		
		if(x==pai->fesq && pai==avo->fdir)
		{
			roda_dir(tree, pai);
			roda_esq(tree, avo);
			avo->cor = RED;
			x->cor = BLACK;
			return;
		}

		if(x==pai->fdir && pai==avo->fesq)
		{
			roda_esq(tree, pai);
			roda_dir(tree, avo);
			avo->cor = RED;
			x->cor = BLACK;
			return;
		}

	}
	if(pai->cor == RED && tio->cor == RED)//caso 2: pai vermelho e tio vermelho - fazer recolorações e arrumar de novo, se necessário
	{
		pai->cor = BLACK;
		tio->cor = BLACK;
		avo->cor = RED;
		if(avo->pai == tree->sentinela)
			avo->cor = BLACK;
		else if(avo->pai->cor == RED)
			arruma_arvore(tree, avo->pai, avo);
		return;
	}
}	

int rbtree_add(RBTree *tree, ITEM *item)//adicionar um nó
{
	if(tree == NULL)
		return 0;
	if(vazia(tree))
		return (criaRaiz(tree, item));
	NO *paux = tree->raiz;
	NO *filho;
	while(1)//percorre a árvore para achar a posição de inserção
	{
		if(paux->item->key > item->key)
		{
			if(paux->fesq == tree->sentinela)
			{
				adicionaFilho(ESQ, paux, item, tree);
				filho = paux->fesq;
				break;
			}
			else
				paux = paux->fesq;
		}
		else if(paux->item->key < item->key)
		{
			if(paux->fdir==tree->sentinela)
			{
				adicionaFilho(DIR, paux, item, tree);
				filho = paux->fdir;
				break;
			}
			else
				paux = paux->fdir;
		}
		else //chave já existente
			return 0;
	}
	arruma_arvore(tree, paux, filho);//arruma a árvore para restaurar suas propriedades
	return 1;
}

NO *sucessor(NO *raiz, RBTree *tree)//retorna o sucessor de um nó, considerando a ordem crescente das chaves
{
	NO *paux;
	if(raiz->fdir != tree->sentinela)// se o filho da direita existe, então basta ir descendo à esquerda...
	{
		while(raiz->fesq != tree->sentinela)
			raiz = raiz->fesq;
		return raiz;
	}
	paux = raiz->pai;
	while(paux != tree->sentinela && raiz == paux->fdir)//...senão, tem que ir subindo na árvore até achar o primeiro nó à esquerda
	{
		raiz = paux;
		paux = paux->pai;
	}
	return paux;
}

void arruma_arvore_2(RBTree *tree, NO *x)  //arruma a árvore após a remoção, para manter suas propriedades vermelho-preto
{
	NO *paux; //ponteiro auxiliar: será irmão de x
	while(x != tree->raiz && x->cor == BLACK && x != tree->sentinela) //percorre a árvore subindo, a fim de restaurá-la
	{
		if(x == x->pai->fesq)
		{
			paux = x->pai->fdir;
			if(paux->cor == RED) 
			{
				paux->cor = BLACK;
				x->pai->cor = RED;
				roda_esq(tree, x->pai);
				paux = x->pai->fdir;
			}
			if(paux->fdir->cor == BLACK) 
			{
				paux->fesq->cor = BLACK;
				paux->cor = RED;
				roda_dir(tree, paux);
				paux = x->pai->fdir;
				paux->cor = x->pai->cor;
				x->pai->cor = BLACK;
				paux->fdir->cor = BLACK;
				roda_esq(tree, x->pai);
				x = tree->raiz;
			}
			else if(paux->fesq->cor == BLACK && paux->fdir->cor == BLACK) 
			{
				paux->cor = RED;
				x = x->pai;
			}
		}
		else
		{
			paux = x->pai->fesq;
			if(paux->cor == RED)
			{
				paux->cor = BLACK;
				x->pai->cor = RED;
				roda_esq(tree, x->pai);
				paux = x->pai->fesq;
			}
			if(paux->fesq->cor == BLACK)
			{
				paux->fdir->cor = BLACK;
				paux->cor = RED;
				roda_dir(tree, paux);
				paux = x->pai->fesq;
				paux->cor = x->pai->cor;
				x->pai->cor = BLACK;
				paux->fesq->cor = BLACK;
				roda_esq(tree, x->pai);
				x = tree->raiz;
			}
			else if(paux->fdir->cor == BLACK && paux->fesq->cor == BLACK)
			{
				paux->cor = RED;
				x = x->pai;
			}
		}
	}
	x->cor = BLACK;
}

ITEM *rbtree_remove(RBTree *tree, int key)//remove um nó dada uma chave
{
	if(tree == NULL || vazia(tree))
		return NULL;
	NO *prem = tree->raiz;  //ponteiro nó de remoção
	NO *paux, *x;
	ITEM *item;
	
	while(1)   //procura pelo nó a ser removido
	{
		if(prem->item->key > key)
		{
			if(prem->fesq==tree->sentinela)
				return NULL;
			prem = prem->fesq;
		}
		else if(prem->item->key < key)
		{
			if(prem->fdir==tree->sentinela)
				return NULL;
			prem = prem->fdir;
		}
		else   //chave encontrada
			break;
	}

	if(prem->fesq == tree->sentinela || prem->fdir == tree->sentinela)
		paux = prem;
	else
		paux = sucessor(prem, tree);
	if(paux->fesq != tree->sentinela)
		x = paux->fesq;
	else
		x = paux->fdir;

	x->pai = paux->pai;

	if(paux->pai == tree->sentinela)
		tree->raiz = x;
	else if(paux == paux->pai->fesq)
		paux->pai->fesq = x;
	else
		paux->pai->fdir = x;

	item = prem->item;

	if(paux != prem)
		prem->item = paux->item;
	if(paux->cor == BLACK) //só é necessário arrumar a árvore se um nó preto for removido
		arruma_arvore_2(tree, x);

	free(paux);
	return item;
}

int rbtree_height_Aux(NO *raiz, RBTree *tree) //função auxiliar para calcular recursivamente a altura da árvore
{
	int esq, dir;
	if(raiz == tree->sentinela) //árvore vazia
		return -1;
	esq = rbtree_height_Aux(raiz->fesq, tree);  //altura da subárvore esquerda
	dir = rbtree_height_Aux(raiz->fdir, tree);  //altura da subárvore direita
	return (esq > dir ? (esq + 1) : (dir + 1) ); 
}
int rbtree_height(RBTree *tree) //calcula a altura da árvore
{	
	if(tree == NULL)
		return -1;
	return rbtree_height_Aux(tree->raiz, tree);
}

void rbtree_free_Aux(NO *raiz, RBTree *tree)   //função apaga árvore auxiliar
{
	if(raiz == tree->sentinela || raiz==NULL)
		return;
	rbtree_free_Aux(raiz->fesq, tree);  //apaga subárvore esquerda
	rbtree_free_Aux(raiz->fdir, tree);  //apaga subárvore direita
	free(raiz->item);  					//apaga raiz
	free(raiz);
}

void rbtree_free(RBTree **tree)   //apaga a árvore, liberando memória
{
	if(tree == NULL || *tree == NULL)
		return;
	rbtree_free_Aux((*tree)->raiz, (*tree));
	free(*tree);
	(*tree) = NULL;
}

/*
Funções rbtree_remove , arruma_arvore_2 e roda_esq criadas com base nos pseudocódigos presentes em: 
--Cormen, Thomas H. Algoritmos: teoria e prática. Rio de Janeiro: Elsevier, 2002. 
*/