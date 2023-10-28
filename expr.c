#include "expr.h"
#include <stdlib.h>
#include "symtable.h"
#include "y.tab.h"

struct expression* create_expression(int type) {
    struct expression* expr = malloc(sizeof(struct expression));
    expr->type = type;
    return expr;
}

struct expression* create_sym_expression(int sym) {
    struct expression* expr = create_expression(SYMBOL);
    expr->symbol = sym;
    return expr;
}

struct expression* create_val_expression(int val) {
    struct expression* expr = create_expression(VALUE);
    expr->value = val;
    return expr;
}

struct expression* create_unary_expression(int type, struct expression* exp) {
    struct expression* expr = create_expression(type);
    expr->operands.rhs = exp;
    return expr;
}

struct expression* create_binary_expression(int type, struct expression* lhs, struct expression* rhs) {
    struct expression* expr = create_expression(type);
    expr->operands.lhs = lhs;
    expr->operands.rhs = rhs;
    return expr;
}

void free_expression(struct expression* expr) {
    if (!expr)
        return;
    switch(expr->type) {
    case AND:
    case OR:
    case EQUALS:
    case '>':
    case '<':
        free_expression(expr->operands.lhs);
    case NOT:
        free_expression(expr->operands.rhs);
    }
    free(expr);
}

int eval(struct expression* expr) {
    switch(expr->type) {
    case VALUE:
        return expr->value;
    case SYMBOL:
        return *get_var(expr->symbol);
    case NOT:
        return !eval(expr->operands.rhs);
    case AND:
        return eval(expr->operands.lhs) && eval(expr->operands.rhs);
    case OR:
        return eval(expr->operands.lhs) || eval(expr->operands.rhs);
    case EQUALS:
        return eval(expr->operands.lhs) == eval(expr->operands.rhs);
    case '<':
        return eval(expr->operands.lhs) < eval(expr->operands.rhs);
    case '>':
        return eval(expr->operands.lhs) > eval(expr->operands.rhs);
    }
    return 0;
}
