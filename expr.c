#include "expr.h"
#include <stdlib.h>
#include "y.tab.h"

struct expression* create_expression(int type) {
    struct expression* expr = malloc(sizeof(struct expression));
    expr->type = type;
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
