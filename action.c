#include "action.h"

#include <stdlib.h>
#include <stdio.h>

#include "option.h"
#include "setter.h"
#include "when.h"
#include "strtable.h"
#include "symtable.h"
#include "y_tab.h"

int run_flag = 1;

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

void exec_actions(struct action* action) {
    if (!action)
        return;

    switch (action->type) {
    case EXIT:
        run_flag = 0;
        break;
    case TEXT:
        printf("%s", get_string(action->arg.text_str));
        break;
    case SET:
        set(action->arg.setter);
        break;
    case GOTO:
        set_temp(action->arg.goto_sym);
        break;
    case OPTIONS:
        add_options(action->arg.options);
        break;
    }

    exec_actions(action->next);
}
