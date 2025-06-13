%{
#define YY_NO_UNISTD_H
#include <stdlib.h>
#include "y_tab.h"

#include "action.h"
#include "cp.h"
#include "expr.h"
#include "option.h"
#include "setter.h"
#include "strtable.h"
#include "symtable.h"
#include "utf8.h"
void yyerror(char*);

int pos = 0;

void advance(int len);

int extract_string(char* str, int off, int len);
%}

%option never-interactive

%x STRING_MODE

%%

^\xef\xbb\xbf       advance(yyleng); /* skip BOM */
#.*$                advance(yyleng); /* skip comments */

[-+=()<>{};:]       advance(yyleng); return *yytext;

"exit"              advance(yyleng); return EXIT;
(terminal|player)" when" advance(yyleng); return WHEN;
"string"            advance(yyleng); return STRING_DEF;
(show_)?"text"      advance(yyleng); return TEXT;
"short"             advance(yyleng); return SHORT;
"clear"             advance(yyleng); return CLEAR;
"set"(local)?       advance(yyleng); return SET;
(goto|next)         advance(yyleng); return GOTO;
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
                        yylval.string = extract_string(yytext + 1, pos + 1, yyleng - 2);
                        advance(yyleng);
                        return STRING;
                    }

"[["                { BEGIN STRING_MODE; yymore(); }
<STRING_MODE>"]]"   {
                        BEGIN 0;
                        yytext[yyleng - 2] = '\0';
                        yylval.string = extract_string(yytext + 2, pos + 2, yyleng - 4);
                        advance(yyleng);
                        return STRING;
                    }
<STRING_MODE>.|\n   yymore();

[ \t\r\n]           advance(yyleng); /* skip whitespace */

%%

int yywrap(void) {
    return 1;
}

void advance(int len) {
    pos += len;
}

int extract_string(char* str, int off, int len) {
    char* eq = strchr(str, '=');
    if (eq != NULL) {
        eq++;
        off += (eq - str);
        len -= (eq - str);
        str = eq;
    }
    str = filter_utf8(str);
    return add_string(str, off, len);
}
