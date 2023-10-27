#ifndef ACTION_H
#define ACTION_H

struct option;

struct action {
    int type;
    struct action* next;
    union {
        int text_str;
        int short_str;
        int clear_sym;
        int goto_sym;
        struct option* options;
    } arg;
};

/* create a new action object of the given type */
struct action* create_action(int type);

/* free the given action object */
void free_action(struct action*);

#endif  // ACTION_H

