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

%left OR
%left AND
%left EQUALS
%left '>' '<'
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

string          : STRING_DEF SYMBOL STRING              { *get_var($2) = $3; }
                ;

when            : WHEN '(' expression ')' action_block  { create_when($3, $5); }
                ;

expression      : SYMBOL                                { $$ = create_sym_expression($1); }
                | VALUE                                 { $$ = create_val_expression($1); }
                | NOT expression                        { $$ = create_unary_expression(NOT, $2); }
                | '(' expression ')'                    { $$ = $2; }
                | expression AND expression             { $$ = create_binary_expression(AND, $1, $3); }
                | expression OR expression              { $$ = create_binary_expression(OR, $1, $3); }
                | expression EQUALS expression          { $$ = create_binary_expression(EQUALS, $1, $3); }
                | expression '>' expression             { $$ = create_binary_expression('>', $1, $3); }
                | expression '<' expression             { $$ = create_binary_expression('<', $1, $3); }
                ;

action_block    : '{' action_list '}'                   { $$ = $2; }
                ;

action_list     : action action_list                    { $1->next = $2; $$ = $1; }
                |                                       { $$ = NULL; }
                ;

action          : EXIT                                  { $$ = create_action(EXIT); }
                | TEXT ':' STRING                       { $$ = create_action(TEXT); $$->arg.text_str = $3; }
                | SHORT ':' STRING                      { $$ = create_action(SHORT); $$->arg.short_str = $3; }
                | CLEAR ':' SYMBOL                      { $$ = create_action(SET); $$->arg.setter = create_setter(create_val_expression(0), 0); $$->arg.setter->sym = $3; }
                | SET ':' setter                        { $$ = create_action(SET); $$->arg.setter = $3; }
                | GOTO ':' SYMBOL                       { $$ = create_action(GOTO); $$->arg.goto_sym = $3; }
                | OPTIONS ':' option_block              { $$ = create_action(OPTIONS); $$->arg.options = $3; }
                ;

setter          : SYMBOL ';' assignment                 { $$ = $3; $$->sym = $1; }
                | SYMBOL                                { $$ = create_setter(create_val_expression(1), 0); $$->sym = $1; }
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
