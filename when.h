#ifndef WHEN_H
#define WHEN_H

#include "action.h"
#include "expr.h"

#define N_WHENS 256

struct when {
    struct expression* condition;
    struct action* actions;
};

/* create a new when object, with the given expression and action list. returns id */
int create_when(struct expression*, struct action*);

/* free the list of when objects */
void clear_whens();

/* return the number of whens in the when table */
int when_count();

/* get the when with the given id */
struct when* get_when(int i);

/* execute the actions of the given when */
void exec_when(struct when* when);

/* if the condition of the given when evaluates to true, execute its actions */
void eval_when(struct when* when);

/* eval each when in the when list */
void eval_whens();

#endif  // WHEN_H
