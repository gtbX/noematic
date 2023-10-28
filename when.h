#ifndef WHEN_H
#define WHEN_H

#include "action.h"
#include "expr.h"

#define N_WHENS 256

struct when {
    struct expression* condition;
    struct action* actions;
};

extern struct when* whens[N_WHENS];

/* create a new when object, with the given expression and action list. returns id */
int create_when(struct expression*, struct action*);

/* free the list of when objects */
void clear_whens();

#endif  // WHEN_H
