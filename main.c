#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

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

    for (int i = 0; i < N_SYMS; i++) {
        if (syms[i][0] == '\0')
            break;
        printf("%d: (%zd)%s\n", i, strlen(syms[i]), syms[i]);
    }

    for (int i = 0; i < N_STRINGS; i++) {
        if (strings[i] == NULL)
            break;
        printf("%d: %s\n", i, strings[i]);
    }

    fclose(yyin);
    return 0;
}
