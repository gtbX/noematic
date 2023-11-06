#include "expr.h"

#include <stdlib.h>
#include <stdio.h>

#include "symtable.h"
#include "y_tab.h"

struct expression* create_expression(int type) {
    struct expression* expr = malloc(sizeof(struct expression));
    expr->type = type;
    return expr;
}

struct expression* create_sym_expression(int sym) {
    struct expression* expr = create_expression(SYMBOL);
    expr->e.symbol = sym;
    return expr;
}

struct expression* create_val_expression(int val) {
    struct expression* expr = create_expression(VALUE);
    expr->e.value = val;
    return expr;
}

struct expression* create_unary_expression(int type, struct expression* exp) {
    struct expression* expr = create_expression(type);
    expr->e.operands.rhs = exp;
    return expr;
}

struct expression* create_binary_expression(int type, struct expression* lhs, struct expression* rhs) {
    struct expression* expr = create_expression(type);
    expr->e.operands.lhs = lhs;
    expr->e.operands.rhs = rhs;
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
        free_expression(expr->e.operands.lhs);
    case NOT:
        free_expression(expr->e.operands.rhs);
    }
    free(expr);
}

int eval(struct expression* expr) {
    switch (expr->type) {
    case VALUE:
        return expr->e.value;
    case SYMBOL:
        return *get_var(expr->e.symbol);
    case NOT:
        return !eval(expr->e.operands.rhs);
    case AND:
        return eval(expr->e.operands.lhs) && eval(expr->e.operands.rhs);
    case OR:
        return eval(expr->e.operands.lhs) || eval(expr->e.operands.rhs);
    case EQUALS:
        return eval(expr->e.operands.lhs) == eval(expr->e.operands.rhs);
    case '<':
        return eval(expr->e.operands.lhs) < eval(expr->e.operands.rhs);
    case '>':
        return eval(expr->e.operands.lhs) > eval(expr->e.operands.rhs);
    }
    return 0;
}

void print_expr(struct expression* expr) {
    switch (expr->type) {
    case VALUE:
        printf("%d", expr->e.value);
        break;
    case SYMBOL:
        printf("%s(%d)", get_sym_name(expr->e.symbol), *get_var(expr->e.symbol));
        break;
    case NOT:
        printf("(not ");
        print_expr(expr->e.operands.rhs);
        printf(" )");
        break;
    default:
        printf("( ");
        print_expr(expr->e.operands.lhs);
        switch (expr->type) {
        case AND: printf(" and "); break;
        case OR: printf(" or "); break;
        case EQUALS: printf(" == "); break;
        case '<': printf(" < "); break;
        case '>': printf(" > "); break;
        }
        print_expr(expr->e.operands.rhs);
        printf(" )");
        break;
    }
}
