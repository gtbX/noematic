#include "setter.h"
#include <stdlib.h>

struct setter* create_setter(struct expression* exp, char mod) {
    struct setter* setter = malloc(sizeof(struct setter));
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
