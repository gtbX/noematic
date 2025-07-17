#ifndef STRING_TABLE_H
#define STRING_TABLE_H

#include <stdio.h>

/* add the string to the table, returning its index */
int add_string(FILE* file, int off, int len);

/* get the string referenced by the given id */
const char* get_string(int id);

/* clear string table and allocated memory */
void clear_strings();

#endif  /* STRING_TABLE_H */
