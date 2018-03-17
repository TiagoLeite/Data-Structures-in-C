#ifndef ITEM_H
#define ITEM_H

typedef struct item ITEM;
struct item {
    int key, value;
};

ITEM *item_new(int key, int value);
void item_free(ITEM **item);
ITEM *item_copy(const ITEM *item);
void item_print(const ITEM *item);

#endif /* ITEM_H */
