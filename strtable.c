#include "strtable.h"

#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define N_STRINGS 512

struct strent {
    char* str;
    int off;
    int len;
};

struct strent strings[N_STRINGS] = { 0 };
int id = 0;

int add_string(const char* string, int off, int len) {
    if (string[0] == '\0')
        return -1;
    strings[id].str = strdup(string);
    if (!strings[id].str) {
        perror("add_string: strdup");
        exit(errno);
    }
    strings[id].off = off;
    strings[id].len = len;
    return id++;
}

const char* get_string(int n) {
    if (n >= 0 && n < id)
        return strings[n].str;
    return "";
}

void clear_strings() {
    while(id > 0) {
        free(strings[--id].str);
    }
}

void dump_strings() {
    int i;
    for (i = 0; i < N_STRINGS; i++) {
        if (!strings[i].str)
            break;
        printf("%d %s\n", i, strings[i].str);
    }
}
