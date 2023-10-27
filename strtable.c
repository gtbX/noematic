#include <stdlib.h>
#include <string.h>
#include "strtable.h"

#define N_STRINGS 512

char* strings[N_STRINGS] = { 0 };
int id = 0;

int add_string(const char* string) {
    if (string[0] == '\0')
        return -1;
    strings[id] = strdup(string);
    return id++;
}

const char* get_string(int n) {
    if (n >= 0 && n < id)
        return strings[n];
    return "";
}

void clear_strings() {
    while(id > 0) {
        free(strings[--id]);
    }
}
