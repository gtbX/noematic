#include "option.h"

#include <stdlib.h>
#include <string.h>

#include "strtable.h"
#include "y.tab.h"

#define N_OPTS 16

struct option* active[N_OPTS];
int n_opts = 0;

struct option* create_option(int text, struct action* actions) {
    struct option* option = malloc(sizeof(struct option));
    option->text = text;
    option->actions = actions;
    // find and cache the SHORT action text
    for (; actions != NULL; actions = actions->next) {
        if (actions->type == SHORT) {
            option->short_txt = actions->arg.short_str;
            break;
        }
    }
    return option;
}

void free_option(struct option* option) {
    if (!option)
        return;
    free_option(option->next);
    free_action(option->actions);
    free(option);
}

void add_options(struct option* options) {
    if (!options || n_opts >= N_OPTS)
        return;
    active[n_opts++] = options;
    add_options(options->next);
}

void clear_options() {
    n_opts = 0;
}

int option_count() {
    return n_opts;
}

int eval_option(struct option* opt, const char* input) {
    if (strstr(get_string(opt->text), input) ||
        strstr(get_string(opt->short_txt), input)) {
        exec_actions(opt->actions);
        return 1;
    }
    return 0;
}

int eval_options(const char* input) {
    int i;
    for(i = 0; i < n_opts; i++) {
        if (eval_option(active[i], input)) {
            return 1;
        }
    }
    return 0;
}
