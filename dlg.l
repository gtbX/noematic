%{
#define YY_NO_UNISTD_H
#include <stdlib.h>
#include "y_tab.h"
#include "cp.h"
#include "strtable.h"
#include "symtable.h"
#include "utf8.h"
void yyerror(char*);

int extract_string(char* str);
%}

%option never-interactive

%x STRING_MODE

%%

^\xef\xbb\xbf       ; /* skip BOM */
#.*$                ; /* skip comments */

[-+=()<>{};:]       return *yytext;

"exit"              return EXIT;
(terminal|player)" when" return WHEN;
"string"            return STRING_DEF;
(show_)?"text"      return TEXT;
"short"             return SHORT;
"clear"             return CLEAR;
"set"(local)?       return SET;
(goto|next)         return GOTO;
"options"           return OPTIONS;
"notext"            ; /* nothing */

"and"               return AND;
"or"                return OR;
"not"               return NOT;
"=="                return EQUALS;

[a-zA-Z_][a-zA-Z0-9_]* {
                        yylval.symbol = get_sym(yytext);
                        return SYMBOL;
                    }
[0-9]+              { yylval.value = atoi(yytext); return VALUE; }

\"[^"\n]*["\n]      {
                        yytext[yyleng - 1] = '\0';
                        yylval.string = extract_string(yytext + 1);
                        return STRING;
                    }

"[["                { BEGIN STRING_MODE; yymore(); }
<STRING_MODE>"]]"   {
                        BEGIN 0;
                        yytext[yyleng - 2] = '\0';
                        yylval.string = extract_string(yytext + 2);
                        return STRING;
                    }
<STRING_MODE>.|\n   yymore();

[ \t\n]             ; /* skip whitespace */

%%

int yywrap(void) {
    return 1;
}

int extract_string(char* str) {
    char* eq = strchr(str, '=');
    if (eq != NULL) {
        eq = filter_utf8(++eq);
        return add_string(eq);
    }
    str = filter_utf8(str);
    return add_string(str);
}
