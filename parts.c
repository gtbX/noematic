#include "parts.h"
#include "y.tab.h"
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
    free_expression(w->condition);
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
    if (!action)
        return;
    free_action(action->next);
    switch (action->type) {
    case SET:
        free_setter(action->arg.setter);
        break;
    case OPTIONS:
        free_option(action->arg.options);
        break;
    }
    free(action);
}

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

struct option* create_option(int text, struct action* actions) {
    struct option* option = malloc(sizeof(struct option));
    option->text = text;
    option->actions = actions;
    return option;
}

void free_option(struct option* option) {
    if (!option)
        return;
    free_option(option->next);
    free_action(option->actions);
    free(option);
}
