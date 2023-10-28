#include "when.h"
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

int when_count() {
    return n_whens;
}

struct when* get_when(int i) {
    if (i < 0 || i >= n_whens)
        return NULL;
    return whens[i];
}

void exec_when(struct when* when) {
    if (!when)
        return;
    exec_action(when->actions);
}

void eval_when(struct when* when) {
    if (!when)
        return;
    if (eval(when->condition))
        exec_when(when);
}
