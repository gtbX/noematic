#ifndef SYM_TABLE_H
#define SYM_TABLE_H

#define SYM_LEN 64
#define N_SYMS 256

extern char syms[N_SYMS][SYM_LEN];
extern int vars[N_SYMS];

/* get or add the symbol name to the table. returns the id. */
int get_sym(const char* id);

#endif  //SYM_TABLE_H
