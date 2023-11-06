#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "symtable.h"

#define SYM_LEN 64
#define N_SYMS 256

char syms[N_SYMS][SYM_LEN] = { 0 };
int vars[N_SYMS] = { 0 };
int temp = -1;
int scratch;

/* get or add the symbol name to the table. returns the id. */
int get_sym(const char* id) {
    int i;
    for (i = 0; i < N_SYMS; i++) {
        if (syms[i][0] == '\0') {
            strncpy(syms[i], id, SYM_LEN);
            syms[i][SYM_LEN - 1] = '\0';
            return i;
        }
        if (strcmp(syms[i], id) == 0) {
            return i;
        }
    }
    return -1;
}

int* get_var(int i) {
    if (i < 0 || i >= N_SYMS)
        return NULL;
    if (i == temp) {
        scratch = 1;
        return &scratch;
    }
    return vars + i;
}

void set_temp(int id) {
    printf("set temp %s (%d)\n", syms[id], id);
    temp = id;
}

void clear_temp() {
    printf("clear temp %s (%d)\n", syms[temp], temp);
    temp = -1;
}

void dump_syms() {
    int i;
    for (i = 0; i < N_SYMS; i++) {
        if (syms[i][0] == '\0')
            break;
        if (vars[i] == 0)
            continue;
        printf("%d %s\t\t", i, syms[i]);
        if (i == temp)
            printf("(1)\n");
        else
            printf("%d\n", vars[i]);
    }
}
