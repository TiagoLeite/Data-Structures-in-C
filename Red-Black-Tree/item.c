#include <stdio.h>
#include <stdlib.h>
#include "item.h"

ITEM *item_new(int key, int value) {
    ITEM *item = (ITEM *) malloc(sizeof(ITEM));
    if (item != NULL) {
        item->key = key;
        item->value = value;
    }
    return item;
}

void item_free(ITEM **item) {
    if (item != NULL) {
        free(*item);
        *item = NULL;
    }
}

ITEM *item_copy(const ITEM *item) {
    if (item == NULL)
        return NULL;

    return item_new(item->key, item->value);
}

void item_print(const ITEM *item) {
    printf("{key: %d, value: %d}\n", item->key, item->value);
}
