#include <stdio.h>
#include <string.h>

#include "matrizEsparsa.h"

#define CMD_LENGTH 25

static void cmd_new(MATESPARSA *mats[])
{
    int i, lin, col;
    scanf("%d %d %d", &i, &lin, &col);
    mats[i] = cria(lin,col);
}

static void cmd_free(MATESPARSA *mats[]) {
    int i;
    scanf("%d", &i);
    apagar(&mats[i]);
}

static void cmd_add(MATESPARSA *mats[]) {
    int i, j, k;
    scanf("%d %d %d", &i, &j, &k);
    mats[i] = add(mats[j], mats[k]);   
}

static void cmd_get(MATESPARSA *mats[]) {
    double valor;
    int i, lin, col;
    scanf("%d %d %d", &i, &lin, &col);
    valor =  get(mats[i], lin, col);
    printf("%.2lf\n", valor);
}

static void cmd_set(MATESPARSA *mats[]) {
    double valor;
    int i, lin, col;
    scanf("%d %d %d %lf", &i, &lin, &col, &valor);
    set(mats[i], lin, col, valor);
}

static void cmd_mult(MATESPARSA *mats[]) {
    int i, j, k;
    scanf("%d %d %d", &i, &j, &k);
    mats[i] = mult(mats[j], mats[k]);
}

static void cmd_print(MATESPARSA *mats[]) {
    int i;
    scanf("%d", &i);
    print(mats[i]);
}

int main(void) 
{
    MATESPARSA *mats[] = { NULL, NULL, NULL };
    char cmd[CMD_LENGTH], buf[CMD_LENGTH * 10];
    
    while (scanf("%s", cmd) != EOF) 
    {
        if (strcmp("new", cmd) == 0)
            cmd_new(mats); 
        else if (strcmp("free", cmd) == 0)
            cmd_free(mats);
        else if (strcmp("add", cmd) == 0)
            cmd_add(mats);
        else if (strcmp("get", cmd) == 0)
            cmd_get(mats);
        else if (strcmp("print", cmd) == 0)
            cmd_print(mats);
        else if(strcmp("set", cmd) == 0)
            cmd_set(mats);
        else if(strcmp("mult", cmd) == 0)
            cmd_mult(mats);
        else
            printf("invalid command: %s%s", cmd, fgets(buf, sizeof buf, stdin));
    }

    return 0;
}
