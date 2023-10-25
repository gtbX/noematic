#ifndef DLG_H 
#define DLG_H

#define N_WHENS 256

struct expression {
    int type;
};

struct action {
    int type;
    struct action* next;
    union {
        int text_str;
        int short_str;
        int clear_sym;
        int goto_sym;
    } arg;
};

struct option {
    short text;
    struct action* actions;
};

struct when {
    struct expression* condition;
    struct action* actions;
};

extern struct when* whens[N_WHENS];

/* create a new when object, with the given expression and action list. returns id */
int create_when(struct expression*, struct action*);

/* free the list of when objects */
void clear_whens();

/* create a new action object of the given type */
struct action* create_action(int type);

/* free the given action object */
void free_action(struct action*);

#endif  // DLG_H

