#include "parts.h"
#include <stdlib.h>

struct when* whens[N_WHENS] = { 0 };
int n_whens = 0;

int create_when(struct expression* expression, struct action* actions) {
    whens[n_whens] = malloc(sizeof(struct when));
    whens[n_whens]->condition = expression;
    whens[n_whens]->actions = actions;
    return n_whens++;
}

void free_when(struct when* w) {
    if (w->actions)
        free_action(w->actions);
    free(w);
}

void clear_whens() {
    while (n_whens > 0) {
        free_when(whens[--n_whens]);
    }
}

struct action* create_action(int type) {
    struct action* action = malloc(sizeof(struct action));
    action->type = type;
    return action;
}

void free_action(struct action* action) {
    if (action->next != NULL)
        free_action(action->next);
    free(action);
}

struct option* create_option(int text, struct action* actions) {
    struct option* option = malloc(sizeof(struct option));
    option->text = text;
    option->actions = actions;
    return option;
}

void free_option(struct option* option) {
    if(option->next != NULL)
        free_option(option->next);
    free(option);
}
