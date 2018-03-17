#include <stdio.h>
#include <string.h>
#include "vector.h"

#define CMD_LENGTH 20

#define CMD_NEW      "new"
#define CMD_FREE     "free"
#define CMD_SIZE     "size"
#define CMD_CAPACITY "capacity"
#define CMD_EMPTY    "empty"
#define CMD_ADD      "add"
#define CMD_REMOVE   "remove"
#define CMD_GET      "get"
#define CMD_AT       "at"
#define CMD_COPY     "copy"
#define CMD_REV      "rev"
#define CMD_CAT      "cat"
#define CMD_PRINT    "print"

static void cmd_new(Vector *vecs[]) {
    int vec_i, capacity;
    
    scanf("%d %d", &vec_i, &capacity);
    vecs[vec_i] = vector_new(capacity);
}

static void cmd_free(Vector *vecs[]) {
    int vec_i;

    scanf("%d", &vec_i);
    vector_free(&vecs[vec_i]);
}

static void cmd_size(Vector *vecs[]) {
    int vec_i;

    scanf("%d", &vec_i);
    printf("%d\n", vector_size(vecs[vec_i]));
}

static void cmd_capacity(Vector *vecs[]) {
    int vec_i;

    scanf("%d", &vec_i);
    printf("%d\n", vector_capacity(vecs[vec_i]));
}

static void cmd_empty(Vector *vecs[]) {
    int vec_i;

    scanf("%d", &vec_i);
    printf("%s\n", vector_empty(vecs[vec_i]) ? "true" : "false");
}

static void cmd_add(Vector *vecs[]) {
    int vec_i, key, value;
    ITEM *item;

    scanf("%d %d %d", &vec_i, &key, &value);
    item = item_new(key, value);
    if (item != NULL) {
        if (vector_add(vecs[vec_i], item))
            printf("true\n");
        else {
            printf("false\n");
            item_free(&item);
        }
    }
}

static void cmd_remove(Vector *vecs[]) {
    int vec_i, key;
    ITEM *item;

    scanf("%d %d", &vec_i, &key);
    item = vector_remove(vecs[vec_i], key);
    printf("remove(%d): ", key);
    if (item != NULL) {
        item_print(item);
        item_free(&item);
    } else
        printf("NULL\n");
}

static void cmd_get(Vector *vecs[]) {
    int vec_i, key;
    ITEM *item;

    scanf("%d %d", &vec_i, &key);
    item = vector_get(vecs[vec_i], key);
    printf("get(%d): ", key);
    if (item != NULL)
        item_print(item);
    else
        printf("NULL\n");
}

static void cmd_at(Vector *vecs[]) {
    int vec_i, pos;
    ITEM *item;

    scanf("%d %d", &vec_i, &pos);
    item = vector_at(vecs[vec_i], pos);
    printf("at(%d): ", pos);
    if (item != NULL)
        item_print(item);
    else
        printf("NULL\n");
}

static void cmd_copy(Vector *vecs[]) {
    int vec_i, vec_j;

    scanf("%d %d", &vec_i, &vec_j);
    printf("%s\n", (vector_copy(vecs[vec_i], vecs[vec_j]) == vecs[vec_i]) ? "true" : "false");
}

static void cmd_rev(Vector *vecs[]) {
    int vec_i, vec_j;

    scanf("%d %d", &vec_i, &vec_j);
    printf("%s\n", (vector_rev(vecs[vec_i], vecs[vec_j]) == vecs[vec_i]) ? "true" : "false");
}

static void cmd_cat(Vector *vecs[]) {
    int vec_i, vec_j, vec_k;

    scanf("%d %d %d", &vec_i, &vec_j, &vec_k);
    printf("%s\n", (vector_cat(vecs[vec_i], vecs[vec_j], vecs[vec_k]) == vecs[vec_k]) ? "true" : "false");
}

static void cmd_print(Vector *vecs[]) {
    int vec_i;

    scanf("%d", &vec_i);
    vector_print(vecs[vec_i]);
}

int main() {
    Vector *vecs[] = { NULL, NULL, NULL };
    char cmd[CMD_LENGTH], buf[CMD_LENGTH * 10];

    while (scanf("%s", cmd) != EOF) {
        if (strcmp(CMD_NEW, cmd) == 0)
            cmd_new(vecs); /* new vec_i */
        else if (strcmp(CMD_FREE, cmd) == 0)
            cmd_free(vecs); /* free vec_i */
        else if (strcmp(CMD_SIZE, cmd) == 0)
            cmd_size(vecs); /* size vec_i */
        else if (strcmp(CMD_CAPACITY, cmd) == 0)
            cmd_capacity(vecs); /* capacity vec_i */
        else if (strcmp(CMD_EMPTY, cmd) == 0)
            cmd_empty(vecs); /* empty vec_i */
        else if (strcmp(CMD_ADD, cmd) == 0)
            cmd_add(vecs); /* add vec_i key value */
        else if (strcmp(CMD_REMOVE, cmd) == 0)
            cmd_remove(vecs); /* remove vec_i key */
        else if (strcmp(CMD_GET, cmd) == 0)
            cmd_get(vecs); /* get vec_i key */
        else if (strcmp(CMD_AT, cmd) == 0)
            cmd_at(vecs); /* at vec_i pos */
        else if (strcmp(CMD_COPY, cmd) == 0)
            cmd_copy(vecs); /* copy vec_i vec_j */
        else if (strcmp(CMD_REV, cmd) == 0)
            cmd_rev(vecs); /* rev vec_i */
        else if (strcmp(CMD_CAT, cmd) == 0)
            cmd_cat(vecs); /* cat vec_i vec_j vec_k */
        else if (strcmp(CMD_PRINT, cmd) == 0)
            cmd_print(vecs); /* print vec_i */
        else
            printf("invalid command: %s%s", cmd, fgets(buf, sizeof buf, stdin));
    }

    return 0;
}
