#include <stdio.h>
#include <string.h>

#include "array_list.h"

#define CMD_LENGTH 25

#define CMD_NEW     "new"
#define CMD_FREE    "free"
#define CMD_SIZE    "size"
#define CMD_EMPTY   "empty"
#define CMD_ADD     "add"
#define CMD_REMOVE  "remove"
#define CMD_GET     "get"
#define CMD_AT      "at"
#define CMD_PRINT   "print"

static void cmd_new(ArrayList *lists[]) {
    int list_i;
    
    scanf("%d", &list_i);
    lists[list_i] = list_new();
}

static void cmd_free(ArrayList *lists[]) {
    int list_i;

    scanf("%d", &list_i);
    list_free(&lists[list_i]);
}

static void cmd_size(ArrayList *lists[]) {
    int list_i;

    scanf("%d", &list_i);
    printf("%d\n", list_size(lists[list_i]));
}

static void cmd_empty(ArrayList *lists[]) {
    int list_i;

    scanf("%d", &list_i);
    printf("%s\n", list_empty(lists[list_i]) ? "true" : "false");
}

static void cmd_add(ArrayList *lists[]) {
    int list_i, key, value;
    ITEM *item;

    scanf("%d %d %d", &list_i, &key, &value);
    item = item_new(key, value);
    if (item != NULL) {
        if (list_add(lists[list_i], item))
            printf("true\n");
        else {
            printf("false\n");
            item_free(&item);
        }
    }
}

static void cmd_remove(ArrayList *lists[]) {
    int list_i, key;
    ITEM *item;

    scanf("%d %d", &list_i, &key);
    item = list_remove(lists[list_i], key);
    printf("remove(%d): ", key);
    if (item != NULL) {
        item_print(item);
        item_free(&item);
    } else
        printf("NULL\n");
}

static void cmd_get(ArrayList *lists[]) {
    int list_i, key;
    ITEM *item;

    scanf("%d %d", &list_i, &key);
    item = list_get(lists[list_i], key);
    printf("get(%d): ", key);
    if (item != NULL)
        item_print(item);
    else
        printf("NULL\n");
}

static void cmd_at(ArrayList *lists[]) {
    int list_i, pos;
    ITEM *item;

    scanf("%d %d", &list_i, &pos);
    item = list_at(lists[list_i], pos);
    printf("at(%d): ", pos);
    if (item != NULL)
        item_print(item);
    else
        printf("NULL\n");
}

static void cmd_print(ArrayList *lists[]) {
    int list_i;

    scanf("%d", &list_i);
    list_print(lists[list_i]);
}

int main() {
    ArrayList *lists[] = { NULL, NULL, NULL };
    char cmd[CMD_LENGTH], buf[CMD_LENGTH * 10];

    while (scanf("%s", cmd) != EOF) {
        if (strcmp(CMD_NEW, cmd) == 0)
            cmd_new(lists); /* new list_i */
        else if (strcmp(CMD_FREE, cmd) == 0)
            cmd_free(lists); /* free list_i */
        else if (strcmp(CMD_SIZE, cmd) == 0)
            cmd_size(lists); /* size list_i */
        else if (strcmp(CMD_EMPTY, cmd) == 0)
            cmd_empty(lists); /* empty list_i */
        else if (strcmp(CMD_ADD, cmd) == 0)
            cmd_add(lists); /* add list_i key value */
        else if (strcmp(CMD_REMOVE, cmd) == 0)
            cmd_remove(lists); /* remove list_i key */
        else if (strcmp(CMD_GET, cmd) == 0)
            cmd_get(lists); /* get list_i key */
        else if (strcmp(CMD_AT, cmd) == 0)
            cmd_at(lists); /* at list_i pos */
        else if (strcmp(CMD_PRINT, cmd) == 0)
            cmd_print(lists); /* print list_i */
        else
            printf("invalid command: %s%s", cmd, fgets(buf, sizeof buf, stdin));
    }

    return 0;
}
