#ifndef SYM_TABLE_H
#define SYM_TABLE_H

/* get or add the symbol name to the table. returns the id. */
int get_sym(const char* id);

/* get a pointer to the variable associated with the given id. */
int* get_var(int id);

/* temporarily set the given variable to 1 */
void set_temp(int id);

/* clear the temp variable, setting it back to what it was */
void clear_temp();

#endif  //SYM_TABLE_H
