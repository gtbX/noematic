%{
#define YY_NO_UNISTD_H
#include <stdlib.h>
#include "y_tab.h"

#include "action.h"
#include "cp.h"
#include "expr.h"
#include "file.h"
#include "option.h"
#include "setter.h"
#include "strtable.h"
#include "symtable.h"
#include "utf8.h"
void yyerror(char*);

extern FILE *yyin;

#define STACK_SIZE 16
int pos_stack[STACK_SIZE] = { 0 }, *pos = pos_stack;

void advance(int len);

int extract_string(const char* str, int off, int len);
%}

%option never-interactive
%option yylineno

%x STRING_MODE
%x INCLUDE_MODE

%%

^\xef\xbb\xbf       advance(yyleng); /* skip BOM */
#.*$                advance(yyleng); /* skip comments */

[-+=()<>{};:]       advance(yyleng); return *yytext;

"exit"              advance(yyleng); return EXIT;
"terminal"          advance(yyleng); return TERMINAL;
"player"            advance(yyleng); return PLAYER;
"when"              advance(yyleng); return WHEN;
"string"            advance(yyleng); return STRING_DEF;
(show_)?"text"      advance(yyleng); return TEXT;
"prompt"            advance(yyleng); return TEXT;
"short"             advance(yyleng); return SHORT;
"clear"             advance(yyleng); return CLEAR;
"set"(local)?       advance(yyleng); return SET;
(goto|(auto)?next)  advance(yyleng); return GOTO;
"options"           advance(yyleng); return OPTIONS;
"notext"            advance(yyleng); /* nothing */

"and"               advance(yyleng); return AND;
"or"                advance(yyleng); return OR;
"not"               advance(yyleng); return NOT;
"=="                advance(yyleng); return EQUALS;

[a-zA-Z_][a-zA-Z0-9_]* {
                        yylval.symbol = get_sym(yytext);
                        advance(yyleng);
                        return SYMBOL;
                    }
[0-9]+              {
                        yylval.value = atoi(yytext);
                        advance(yyleng);
                        return VALUE;
                    }

\"[^"\n]*["\n]      {
                        yytext[yyleng - 1] = '\0';
                        yylval.string = extract_string(yytext + 1, *pos + 1, yyleng - 2);
                        advance(yyleng);
                        return STRING;
                    }

"[["                { BEGIN STRING_MODE; yymore(); }
<STRING_MODE>"]]"   {
                        BEGIN INITIAL;
                        yytext[yyleng - 2] = '\0';
                        yylval.string = extract_string(yytext + 2, *pos + 2, yyleng - 4);
                        advance(yyleng);
                        return STRING;
                    }
<STRING_MODE>.|\n   yymore();

include[ \t]*\"     advance(yyleng); BEGIN INCLUDE_MODE;
<INCLUDE_MODE>[^\"]* advance(yyleng); {
                        if (++pos >= pos_stack + STACK_SIZE) {
                            fprintf(stderr, "Include depth limit reached!\n");
                            exit(1);
                        }
                        *pos = 0;
                        yyin = fopen(get_filename(yytext), "rb");
                        if (!yyin) {
                            perror(yytext);
                            exit(1);
                        }
                        yy_switch_to_buffer(yy_create_buffer(yyin, YY_BUF_SIZE));
                        BEGIN INITIAL;
                    }
<INCLUDE_MODE>\"    advance(yyleng); BEGIN INITIAL;

[ \t\r\n]           advance(yyleng); /* skip whitespace */

<<EOF>>             {
                        yypop_buffer_state();
                        if (!YY_CURRENT_BUFFER)
                            yyterminate();
                        pos--;
                    }

%%

int yywrap(void) {
    return 1;
}

void advance(int len) {
    *pos += len;
}

int extract_string(const char* str, int off, int len) {
    const char* eq = strchr(str, '=');
    if (eq != NULL) {
        eq++;
        off += (eq - str);
        len -= (eq - str);
    }
    return add_string(yyin, off, len);
}
