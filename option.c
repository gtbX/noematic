#include "option.h"
#include <stdlib.h>

#define N_OPTS 16

struct option* active[N_OPTS];
int n_opts = 0;

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

void add_option(struct option* option) {
    active[n_opts++] = option;
}

void clear_options() {
    n_opts = 0;
}

int option_count() {
    return n_opts;
}

struct option* get_option(int i) {
    if (i < 0 || i >= n_opts)
        return NULL;
    return active[i];
}
