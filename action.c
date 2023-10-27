#include "action.h"

#include <stdlib.h>
#include <stdio.h>

#include "parts.h"
#include "strtable.h"
#include "y.tab.h"

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

void exec_action(struct action* action) {
    if (!action)
        return;

    switch (action->type) {
    case TEXT:
        printf("%s", get_string(action->arg.text_str));
    }

    exec_action(action->next);
}
