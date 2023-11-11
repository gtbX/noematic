#include "option.h"

#include <ctype.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "expr.h"
#include "setter.h"
#include "slow.h"
#include "strtable.h"
#include "symtable.h"
#include "text.h"
#include "y_tab.h"

#define N_OPTS 16

struct option* active[N_OPTS];
int n_opts = 0;

struct option* create_option(int text, struct action* actions) {
    struct option* option = malloc(sizeof(struct option));
    if (!option) {
        perror("create_option: malloc");
        exit(errno);
    }
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

/* returns 1 if haystack contains needle, 2 if strings are the same; else 0 */
int str_match(const char* haystack, const char* needle) {
    const char* hptr = haystack, *nptr = needle, *ptr = NULL;
    while (*hptr && *nptr) {
        if (toupper(*hptr) == toupper(*nptr)) {
            if (!ptr)
                ptr = hptr;
            nptr++;
        } else {
            nptr = needle;
            ptr = NULL;
        }
        hptr++;
    }
    if (*nptr) {
        return 0; /* no match */
    }
    if (ptr == haystack && !*hptr) { /* exact match */
        return 2;
    }
    return 1;
}

void exec_option(struct option* opt) {
    print_text("> ");
    print_text(get_string(opt->text));
    print_text("\n");
    wait(3);
    exec_actions(opt->actions);
}

/* 2 on exact match of short or long texts,
 * 1 on partial match of either,
 * 0 on no match */
int eval_option(struct option* opt, const char* input) {
    int t_match = str_match(get_string(opt->text), input);
    if (t_match < 2) {
        int s_match = str_match(get_string(opt->short_txt), input);
        return t_match > s_match ? t_match : s_match;
    }
    return t_match;
}

void print_option(struct option* opt) {
    int text = opt->short_txt >= 0 ? opt->short_txt : opt->text;
    printf("%s\n", get_string(text));
}

int eval_options(const char* input) {
    struct option* matched[N_OPTS];
    int n_matched = 0, i;
    if (input[0] != '\0') {
        for(i = 0; i < n_opts; i++) {
            int match = eval_option(active[i], input);
            if (match > 1) {
                exec_option(active[i]);
                return 1;
            } else if (match > 0) {
                matched[n_matched++] = active[i];
            }
        }
    } else if (n_opts == 1) {
        exec_option(active[0]);
        return 1;
    }

    if (n_matched == 1) {
        exec_option(matched[0]);
#ifdef DEBUG
        dump_syms();
#endif
        return 1;
    } else {
        struct option** list;
        int n;
        if (n_matched > 1) {
            printf("Which?\n");
            list = matched;
            n = n_matched;
        } else {
            printf("Options:\n");
            list = active;
            n = n_opts;
        }

        for (i = 0; i < n; i++) {
            print_option(list[i]);
        }
    }
    return 0;
}
