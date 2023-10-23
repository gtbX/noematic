#include <stdlib.h>
#include <string.h>
#include "strtable.h"

char* strings[N_STRINGS] = { 0 };
int id = 0;

int add_string(const char* string) {
    strings[id] = strdup(string);
    return id++;
}

void clear_strings() {
    while(id > 0) {
        free(strings[--id]);
    }
}
