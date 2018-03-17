#include <stdio.h>
#include <string.h>

#include "rbtree.h"

#define CMD_LENGTH 25

#define CMD_NEW    "new"
#define CMD_FREE   "free"
#define CMD_ADD    "add"
#define CMD_REMOVE "remove"
#define CMD_HEIGHT "height"

static void cmd_add(RBTree *tree) {
    int key, value;
    ITEM *item;

    scanf("%d %d", &key, &value);
    item = item_new(key, value);
    if (item != NULL) {
        printf("add(%d, %d): ", key, value);
        if (rbtree_add(tree, item))
            printf("true\n");
        else {
            printf("false\n");
            item_free(&item);
        }
    }
}

static void cmd_remove(RBTree *tree) {
    int key;
    ITEM *item;

    scanf("%d", &key);
    item = rbtree_remove(tree, key);
    printf("remove(%d): ", key);
    if (item != NULL) {
        item_print(item);
        item_free(&item);
    } else
        printf("NULL\n");
}

int main() {
    
    RBTree *tree = NULL;
    char cmd[CMD_LENGTH], buf[CMD_LENGTH * 10];

    while (scanf("%s", cmd) != EOF) {
        if (strcmp(CMD_NEW, cmd) == 0)
            tree = rbtree_new();
        else if (strcmp(CMD_FREE, cmd) == 0)
            rbtree_free(&tree);
        else if (strcmp(CMD_ADD, cmd) == 0)
            cmd_add(tree); //add key value 
        else if (strcmp(CMD_REMOVE, cmd) == 0)
            cmd_remove(tree); //remove key 
        else if (strcmp(CMD_HEIGHT, cmd) == 0)
            printf("%d\n", rbtree_height(tree));
        else
            printf("invalid command: %s%s", cmd, fgets(buf, sizeof buf, stdin));
    }

    return 0;
}