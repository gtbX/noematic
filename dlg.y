%{
#include <stdio.h>
int yylex(void);
void yyerror(char*);
%}

%token IDENTIFIER
%token VALUE
%token STRING

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

%%
game            : game when
                |
                ;

when            : WHEN '(' expression ')' action_block
                ;

expression      : IDENTIFIER
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
                | CLEAR ':' IDENTIFIER
                | SET ':' setter
                | GOTO ':' IDENTIFIER
                | OPTIONS ':' option_block
                ;

setter          : IDENTIFIER ';' assignment
                | IDENTIFIER
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
