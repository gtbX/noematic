#include "strtable.h"

#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define N_STRINGS 512

char* strings[N_STRINGS] = { 0 };
int id = 0;

int add_string(const char* string) {
    if (string[0] == '\0')
        return -1;
    strings[id] = strdup(string);
    if (!strings[id]) {
        perror("add_string: strdup");
        exit(errno);
    }
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

void dump_strings() {
    int i;
    for (i = 0; i < N_STRINGS; i++) {
        if (!strings[i])
            break;
        printf("%d %s\n", i, strings[i]);
    }
}
