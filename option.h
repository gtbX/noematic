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

/* add an option to the list of active options */
void add_option(struct option* option);

/* clear the list of active options */
void clear_options();

/* get the size of the active option list */
int option_count();

/* get the option at the given position of the active option list */
struct option* get_option(int i);

#endif  // OPTION_H
