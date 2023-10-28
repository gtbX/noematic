%{
#include <stdio.h>
#include "action.h"
#include "option.h"
#include "setter.h"
#include "when.h"
#include "symtable.h"
int yylex(void);
void yyerror(char*);
%}

%union {
    int symbol;
    int value;
    int string;
    struct expression* expression;
    struct action* action;
    struct setter* setter;
    struct option* option;
};

%token <symbol> SYMBOL
%token <value> VALUE
%token <string> STRING

%token EXIT
%token WHEN
%token STRING_DEF
%token TEXT
%token SHORT
%token CLEAR
%token SET
%token GOTO
%token OPTIONS

%token AND
%token OR
%token NOT
%token EQUALS

%left EQUALS '>' '<'
%left OR
%left AND
%nonassoc NOT

%type <expression> expression
%type <action> action_block action_list action
%type <setter> assignment setter
%type <option> option_block option_list option

%%
game            : game gamespec
                |
                ;

gamespec        : when
                | string
                ;

string          : STRING_DEF SYMBOL STRING              { vars[$2] = $3; }
                ;

when            : WHEN '(' expression ')' action_block  { create_when($3, $5); }
                ;

expression      : SYMBOL                                { $$ = create_expression(SYMBOL); $$->symbol = $1; }
                | VALUE                                 { $$ = create_expression(VALUE); $$->value = $1; }
                | NOT expression                        { $$ = create_expression(NOT); $$->operands.rhs = $2; }
                | '(' expression ')'                    { $$ = $2; }
                | expression AND expression             { $$ = create_expression(AND); $$->operands.lhs = $1; $$->operands.rhs = $3; }
                | expression OR expression              { $$ = create_expression(OR); $$->operands.lhs = $1; $$->operands.rhs = $3; }
                | expression EQUALS expression          { $$ = create_expression(EQUALS); $$->operands.lhs = $1; $$->operands.rhs = $3; }
                | expression '>' expression             { $$ = create_expression('>'); $$->operands.lhs = $1; $$->operands.rhs = $3; }
                | expression '<' expression             { $$ = create_expression('<'); $$->operands.lhs = $1; $$->operands.rhs = $3; }
                ;

action_block    : '{' action_list '}'                   { $$ = $2; }
                ;

action_list     : action action_list                    { $1->next = $2; $$ = $1; }
                |                                       { $$ = NULL; }
                ;

action          : EXIT                                  { $$ = create_action(EXIT); }
                | TEXT ':' STRING                       { $$ = create_action(TEXT); $$->arg.text_str = $3; }
                | SHORT ':' STRING                      { $$ = create_action(SHORT); $$->arg.short_str = $3; }
                | CLEAR ':' SYMBOL                      { $$ = create_action(SET); $$->arg.setter = create_setter(create_expression(VALUE), 0); $$->arg.setter->exp->value = 0; $$->arg.setter->sym = $3; }
                | SET ':' setter                        { $$ = create_action(SET); $$->arg.setter = $3; }
                | GOTO ':' SYMBOL                       { $$ = create_action(GOTO); $$->arg.goto_sym = $3; }
                | OPTIONS ':' option_block              { $$ = create_action(OPTIONS); $$->arg.options = $3; }
                ;

setter          : SYMBOL ';' assignment                 { $$ = $3; $$->sym = $1; }
                | SYMBOL                                { $$ = create_setter(create_expression(VALUE), 0); $$->exp->value = 1; $$->sym = $1; }
                ;

assignment      : '=' expression ';'                    { $$ = create_setter($2, 0); }
                | '+' '=' expression ';'                { $$ = create_setter($3, 1); }
                | '-' '=' expression ';'                { $$ = create_setter($3, -1); }
                ;

option_block    : '{' option_list '}'                   { $$ = $2; }
                ;

option_list     : option option_list                    { $1->next = $2; $$ = $1; }
                |                                       { $$ = NULL; }
                ;

option          : STRING action_list                    { $$ = create_option($1, $2); }
                ;
%%

void yyerror(char *s) {
    fprintf(stderr, "%s\n", s);
}
