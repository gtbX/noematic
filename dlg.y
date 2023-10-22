%{
#include <stdio.h>
int yylex(void);
void yyerror(char*);
%}

%union {
    int symbol;
    int value;
    int string;
//    node* n_ptr;
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

//%type <n_ptr> when expression 

%%
game            : game gamespec
                |
                ;

gamespec        : when
                | string
                ;

string          : STRING_DEF SYMBOL STRING
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

action          : EXIT
                | TEXT ':' STRING
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
