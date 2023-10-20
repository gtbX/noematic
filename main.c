#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

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

    yydebug = 1;
    yy_flex_debug = 1;

    yyparse();

    fclose(yyin);
	return 0;
}
