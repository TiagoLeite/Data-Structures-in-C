#ifndef VECTOR_H
#define VECTOR_H

#include "item.h"

typedef struct vector Vector;

Vector *vector_new(int capacity);
void vector_free(Vector **vec);
int vector_size(const Vector *vec);
int vector_capacity(const Vector *vec);
int vector_empty(const Vector *vec);
int vector_add(Vector *vec, ITEM *item);
ITEM *vector_remove(Vector *vec, int key);
ITEM *vector_get(const Vector *vec, int key);
ITEM *vector_at(const Vector *vec, int pos);
Vector *vector_copy(Vector *dst, const Vector *src);
Vector *vector_rev(Vector *rev, const Vector *vec);
Vector *vector_cat(const Vector *vec1, const Vector *vec2, Vector *cat);
void vector_print(const Vector *vec);

#endif /* VECTOR_H */
