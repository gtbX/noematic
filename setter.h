#ifndef SETTER_H
#define SETTER_H

#include "expr.h"

struct setter {
    int sym;
    struct expression* exp;
    char mod;
};

/* create a new setter with the given expression and modifier */
struct setter* create_setter(struct expression* exp, char mod);

/* free the given setter object */
void free_setter(struct setter*);

/* execute the given setter */
void set(struct setter*);

#endif /* SETTER_H */
