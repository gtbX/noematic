#include "action.h"
#include <stdlib.h>

struct action* create_action(int type) {
    struct action* action = malloc(sizeof(struct action));
    action->type = type;
    return action;
}

void free_action(struct action* action) {
    if (action->next != NULL)
        free_action(action->next);
    free(action);
}
