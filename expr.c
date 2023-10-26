#include "expr.h"
#include <stdlib.h>
#include "symtable.h"
#include "y.tab.h"

struct expression* create_expression(int type) {
    struct expression* expr = malloc(sizeof(struct expression));
    expr->type = type;
    return expr;
}

void free_expression(struct expression* expr) {
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
        return vars[expr->symbol];
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
