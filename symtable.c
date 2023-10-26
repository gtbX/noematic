#include <stdlib.h>
#include <string.h>
#include "symtable.h"

char syms[N_SYMS][SYM_LEN] = { 0 };
int vars[N_SYMS] = { 0 };

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
