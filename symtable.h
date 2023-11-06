#ifndef SYM_TABLE_H
#define SYM_TABLE_H

/* get or add the symbol name to the table. returns the id. */
int get_sym(const char* name);

/* get the symbol name for the given id */
const char* get_sym_name(int id);

/* get a pointer to the variable associated with the given id. */
int* get_var(int id);

/* temporarily set the given variable to 1 */
void set_temp(int id);

/* clear the temp variable, setting it back to what it was */
void clear_temp();

/* print the contents of the symbol table */
void dump_syms();

#endif /* SYM_TABLE_H */
