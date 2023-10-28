#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "when.h"
#include "option.h"
#include "strtable.h"
#include "symtable.h"
#include "y.tab.h"

extern FILE* yyin;
extern int yy_flex_debug;

int main(int argc, char** argv) {
	if (argc < 2) {
		printf("Usage: %s [game.dlg]\n", argv[0]);
		return 1;
	}

	yyin = fopen(argv[1], "rb");
	if (!yyin) {
		perror("Game file");
		return errno;
	}

#if YYDEBUG
    yydebug = YYDEBUG;
    yy_flex_debug = YYDEBUG;
#endif

    yyparse();

    do {
    } while (option_count() > 0);

    clear_whens();
    clear_strings();

    fclose(yyin);
    return 0;
}
