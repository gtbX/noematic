#include "option.h"
#include <stdlib.h>

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
