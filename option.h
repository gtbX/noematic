#ifndef OPTION_H
#define OPTION_H

#include "action.h"

struct option {
    short text;
    struct action* actions;
    struct option* next;
};

/* create a new option object with the given text and actions */
struct option* create_option(int text, struct action* actions);

/* free the given option object */
void free_option(struct option*);

#endif  // OPTION_H
