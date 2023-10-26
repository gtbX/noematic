#ifndef PARTS_h
#define PARTS_H

#include "expr.h"

#define N_WHENS 256

struct setter {
    int sym;
    struct expression* exp;
    char mod;
};

struct action {
    int type;
    struct action* next;
    union {
        int text_str;
        int short_str;
        int goto_sym;
        struct setter* setter;
        struct option* options;
    } arg;
};

struct option {
    short text;
    struct action* actions;
    struct option* next;
};

struct when {
    struct expression* condition;
    struct action* actions;
};

extern struct when* whens[N_WHENS];

/* create a new when object, with the given expression and action list. returns id */
int create_when(struct expression*, struct action*);

/* free the list of when objects */
void clear_whens();

/* create a new action object of the given type */
struct action* create_action(int type);

/* free the given action object */
void free_action(struct action*);

/* create a new setter with the given expression and modifier */
struct setter* create_setter(struct expression* exp, char mod);

/* free the given setter object */
void free_setter(struct setter*);

/* create a new option object with the given text and actions */
struct option* create_option(int text, struct action* actions);

/* free the given option object */
void free_option(struct option*);

#endif  // PARTS_H

