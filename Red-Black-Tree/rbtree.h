#ifndef RBTREE_H
#define RBTREE_H

#include "item.h"

typedef struct rbtree RBTree;

RBTree *rbtree_new();
void rbtree_free(RBTree **tree);
int rbtree_add(RBTree *tree, ITEM *item);
ITEM *rbtree_remove(RBTree *tree, int key);
int rbtree_height(RBTree *tree);

#endif /* RBTREE_H */
