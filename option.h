#ifndef OPTION_H
#define OPTION_H

#include "action.h"

struct option {
    int text;
    int short_txt;
    struct action* actions;
    struct option* next;
};

/* create a new option object with the given text and actions */
struct option* create_option(int text, struct action* actions);

/* free the given option object */
void free_option(struct option*);

/* add a set of options to the list of active options */
void add_options(struct option* options);

/* clear the list of active options */
void clear_options();

/* get the size of the active option list */
int option_count();

/* evaluate the option list against the given string. return true if an option is executed */
int eval_options(const char* input);

#endif /* OPTION_H */
