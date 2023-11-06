#include "option.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "strtable.h"
#include "symtable.h"
#include "y_tab.h"

#define N_OPTS 16

struct option* active[N_OPTS];
int n_opts = 0;

struct option* create_option(int text, struct action* actions) {
    struct option* option = malloc(sizeof(struct option));
    option->text = text;
    option->short_txt = -1;
    option->actions = actions;
    /* find and cache the SHORT action text */
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

void print_option(struct option* opt) {
    int text = opt->short_txt >= 0 ? opt->short_txt : opt->text;
    printf("%s\n", get_string(text));
}

int eval_options(const char* input) {
    int i;
    if (input[0] != '\0') {
        for(i = 0; i < n_opts; i++) {
            if (eval_option(active[i], input)) {
#ifdef DEBUG
                dump_syms();
#endif
                return 1;
            }
        }
    }

    printf("Options:\n");
    for (i = 0; i < n_opts; i++) {
        print_option(active[i]);
    }
    return 0;
}
