#ifndef EXPR_H
#define EXPR_H

struct expression {
    int type;
    union {
        int symbol;
        int value;
        struct {
            struct expression* lhs;
            struct expression* rhs;
        } operands;
    };
};

/* create a new expression object of the given type */
struct expression* create_expression(int type);

/* free the given expression */
void free_expression(struct expression* expr);

/* evaluate the expression, returning the value */
int eval(struct expression* expr);

#endif // EXPR_H
