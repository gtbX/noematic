#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "when.h"
#include "option.h"
#include "setter.h"
#include "strtable.h"
#include "symtable.h"
#include "y_tab.h"

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

    exec_when(get_when(0)); /* bootstrap */
    eval_whens();

    while (run_flag && option_count() > 0) {
        char buf[64];

        do {
            int len;
            fgets(buf, sizeof(buf), stdin);
            len = strlen(buf);
            if (len > 0 && buf[len - 1] == '\n')
                buf[len - 1] = '\0';
        } while(eval_options(buf) == 0);

        clear_options();
        eval_whens();
        clear_temp();
    }

    clear_whens();
    clear_strings();

    fclose(yyin);
    return 0;
}
