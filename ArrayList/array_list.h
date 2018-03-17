#ifndef ARRAY_LIST_H
#define ARRAY_LIST_H

#include "item.h"

typedef struct array_list ArrayList;

ArrayList *list_new();
void list_free(ArrayList **list);
int list_size(const ArrayList *list);
int list_empty(const ArrayList *list);
int list_add(ArrayList *list, ITEM *item);
ITEM *list_remove(ArrayList *list, int key);
ITEM *list_get(const ArrayList *list, int key);
ITEM *list_at(const ArrayList *list, int pos);
void list_print(const ArrayList *list);

#endif /* ARRAY_LIST_H */
