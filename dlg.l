%{
#include <stdlib.h>
#include "y.tab.h"
#include "symtable.h"
void yyerror(char*);
%}

%x STRING_MODE

%%

^\xef\xbb\xbf       ; /* skip BOM */
#.*$                ; /* skip comments */

[-+=()<>{};:]       return *yytext;

"exit"              return EXIT;
(terminal|player)" when" return WHEN;
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
[0-9]+              return VALUE;

\"[^"\n]*["\n]      return STRING;

"[["                { BEGIN STRING_MODE; yylval.string.offset = ftell(yyin); yymore(); }
<STRING_MODE>"]]"   { BEGIN 0; yylval.string.length = ftell(yyin) - yylval.string.offset; return STRING; }
<STRING_MODE>.|\n   yymore();

[ \t\n]             ; /* skip whitespace */

%%

int yywrap(void) {
    return 1;
}
