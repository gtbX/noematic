%{
#include <stdio.h>
#include "storage.h"
int yylex(void);
void yyerror(char*);
%}

%union {
    int symbol;
    int value;
    struct {
        int offset;
        int length;
    } string;
//    node* n_ptr;
};

%token <symbol> SYMBOL
%token <value> VALUE
%token <string> STRING

%token WHEN
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

//%type <n_ptr> when expression 

%%
game            : game when
                |
                ;

when            : WHEN '(' expression ')' action_block
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

action_block    : '{' action_list '}'
                ;

action_list     : action_list action
                |
                ;

action          : TEXT ':' STRING
                | SHORT ':' STRING
                | CLEAR ':' SYMBOL
                | SET ':' setter
                | GOTO ':' SYMBOL
                | OPTIONS ':' option_block
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
