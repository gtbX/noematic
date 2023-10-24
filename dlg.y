%{
#include <stdio.h>
#include "parts.h"
int yylex(void);
void yyerror(char*);
%}

%union {
    int symbol;
    int value;
    int string;
    struct expression* expression;
    struct action* action;
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

%%
game            : game gamespec
                |
                ;

gamespec        : when
                | string
                ;

string          : STRING_DEF SYMBOL STRING
                ;

when            : WHEN '(' expression ')' action_block  { create_when($3, $5); }
                ;

expression      : SYMBOL
                | VALUE
                | NOT expression
                | '(' expression ')'
                | expression AND expression
                | expression OR expression
                | expression EQUALS expression
                | expression '>' expression
                | expression '<' expression
                ;

action_block    : '{' action_list '}'                   { $$ = $2; }
                ;

action_list     : action action_list                    { $1->next = $2; $$ = $1; }
                |                                       { $$ = NULL; }
                ;

action          : EXIT                                  { $$ = create_action(EXIT); }
                | TEXT ':' STRING                       { $$ = create_action(TEXT); }
                | SHORT ':' STRING                      { $$ = create_action(SHORT); }
                | CLEAR ':' SYMBOL                      { $$ = create_action(CLEAR); }
                | SET ':' setter                        { $$ = create_action(SET); }
                | GOTO ':' SYMBOL                       { $$ = create_action(GOTO); }
                | OPTIONS ':' option_block              { $$ = create_action(OPTIONS); }
                ;

setter          : SYMBOL ';' assignment
                | SYMBOL
                ;

assignment      : '=' expression ';'
                | '+' '=' expression ';'
                | '-' '=' expression ';'
                ;

option_block    : '{' option_list '}'
                ;

option_list     : option_list option
                |
                ;

option          : STRING action_list
                ;
%%

void yyerror(char *s) {
    fprintf(stderr, "%s\n", s);
}
