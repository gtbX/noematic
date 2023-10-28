#ifndef SYM_TABLE_H
#define SYM_TABLE_H

/* get or add the symbol name to the table. returns the id. */
int get_sym(const char* id);

/* get a pointer to the variable associated with the given id. */
int* get_var(int id);

#endif  //SYM_TABLE_H
