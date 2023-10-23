#ifndef STRING_TABLE_H
#define STRING_TABLE_H

#define N_STRINGS 512

extern char* strings[N_STRINGS];

/* add the string to the table, returning its index */
int add_string(const char* string);

void clear_strings();

#endif  // STRING_TABLE_H
