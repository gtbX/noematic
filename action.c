#include "action.h"
#include <stdlib.h>

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
