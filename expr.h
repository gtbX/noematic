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
    } e;
};

/* create a new symbol expression for the given symbol */
struct expression* create_sym_expression(int sym);

/* create a new value expression of the given value */
struct expression* create_val_expression(int val);

/* create a new unary expression wrapping the given expression */
struct expression* create_unary_expression(int type, struct expression* exp);

/* create a new binary expression of the given expressions */
struct expression* create_binary_expression(int type, struct expression* lhs, struct expression* rhs);

/* free the given expression */
void free_expression(struct expression* expr);

/* evaluate the expression, returning the value */
int eval(struct expression* expr);

#endif // EXPR_H
