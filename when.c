#include "when.h"

#include <errno.h>
#include <stdlib.h>
#include <stdio.h>

#include "option.h"
#include "setter.h"

#define N_WHENS 256

struct when* whens[N_WHENS] = { 0 };
int n_whens = 0;

int create_when(struct expression* expression, struct action* actions) {
    whens[n_whens] = malloc(sizeof(struct when));
    if (!whens[n_whens]) {
        perror("create_when: malloc");
        exit(errno);
    }
    whens[n_whens]->condition = expression;
    whens[n_whens]->actions = actions;
#ifdef DEBUG
    printf("Creating when[%d](", n_whens);
    print_expr(expression);
    printf(")\n");
#endif
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
    exec_actions(when->actions);
}

void eval_when(struct when* when) {
    if (!when)
        return;
#ifdef DEBUG
    printf("evaluating when ( ");
    print_expr(when->condition);
    printf(" ) = %d\n", eval(when->condition));
#endif
    if (eval(when->condition)) {
#ifdef DEBUG
        printf("executing\n");
#endif
        exec_when(when);
    }
}

void eval_whens() {
    int i;
    for (i = 0; i < n_whens; i++) {
        eval_when(whens[i]);
    }
}
