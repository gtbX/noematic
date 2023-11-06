#include "setter.h"

#include <errno.h>
#include <stdlib.h>
#include <stdio.h>

#include "expr.h"
#include "symtable.h"

struct setter* create_setter(struct expression* exp, char mod) {
    struct setter* setter = malloc(sizeof(struct setter));
    if (!setter) {
        perror("create_setter: malloc");
        exit(errno);
    }
    setter->exp = exp;
    setter->mod = mod;
    return setter;
}

void free_setter(struct setter* setter) {
    if (!setter)
        return;
    free_expression(setter->exp);
    free(setter);
}

void set(struct setter* setter) {
    int val = eval(setter->exp);
    if (setter->mod == 0)
        *get_var(setter->sym) = val;
    else
        *get_var(setter->sym) = *get_var(setter->sym) + (val * setter->mod);
}
