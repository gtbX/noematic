#include "dlg.h"
#include <stdlib.h>

struct when* whens[N_WHENS] = { 0 };
int n_whens = 0;

int create_when(struct expression* expression, struct action* actions) {
    whens[n_whens] = malloc(sizeof(struct when));
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

void free_action(struct action* action) {
    if (action->next != NULL)
        free_action(action->next);
    free(action);
}
