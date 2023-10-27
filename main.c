#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "parts.h"
#include "strtable.h"
#include "symtable.h"
#include "y.tab.h"

extern FILE* yyin;
extern int yy_flex_debug;

void print_expression(struct expression* expr) {
    if (expr->type == SYMBOL) {
        printf(" %s ", syms[expr->symbol]);
    } else if (expr->type == VALUE) {
        printf(" %d ", expr->value);
    } else if (expr->type == NOT) {
        printf("NOT");
        print_expression(expr->operands.rhs);
    } else {
        print_expression(expr->operands.lhs);
        switch (expr->type) {
        case AND:
            printf("AND");
            break;
        case OR:
            printf("OR");
            break;
        case EQUALS:
            printf("==");
            break;
        case '<':
            printf("<");
            break;
        case '>':
            printf(">");
            break;
        }
        print_expression(expr->operands.rhs);
    }
}

void print_options(struct option* options);

void print_actions(struct action* actions) {
    for (struct action* act = actions; act; act = act->next) {
        printf("action %d, %p\n", act->type, act);
        if (act->type == TEXT)
            printf("%s\n", get_string(act->arg.text_str));
        if (act->type == SHORT)
            printf("%s\n", get_string(act->arg.short_str));
        if (act->type == OPTIONS)
            print_options(act->arg.options);
    }
}

void print_options(struct option* options) {
    for (struct option* opt = options; opt; opt = opt->next) {
        printf("option %p %s\n", opt, get_string(opt->text));
        print_actions(opt->actions);
    }
}

int main(int argc, char** argv) {
	if (argc < 2) {
		printf("Usage: %s [game.dlg]\n", argv[0]);
		return 1;
	}

	yyin = fopen(argv[1], "rb");
	if (!yyin) {
		perror("Game file");
		return errno;
	}

#if YYDEBUG
    yydebug = YYDEBUG;
    yy_flex_debug = YYDEBUG;
#endif

    yyparse();

    for (int i = 0; i < N_SYMS; i++) {
        if (syms[i][0] == '\0')
            break;
        printf("%d: (%zd)%s\n", i, strlen(syms[i]), syms[i]);
    }

    for (int i = 0; i < N_WHENS; i++) {
        if (whens[i] == NULL)
            break;
        printf("when %d: %p ", i, whens[i]);
        print_expression(whens[i]->condition);
        printf("\n");
        print_actions(whens[i]->actions);
    }

    clear_whens();
    clear_strings();

    fclose(yyin);
    return 0;
}
