#include "strtable.h"
#include "utf8.h"

#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define N_STRINGS 512

struct strent {
    FILE* file;
    int off;
    int len;
};

struct strent strings[N_STRINGS] = { 0 };
int id = 0;
char *buf = NULL;
int buflen = 0;

int add_string(FILE* file, int off, int len) {
    if (len == 0 || file == NULL)
        return -1;
    strings[id].file = file;
    strings[id].off = off;
    strings[id].len = len;
    return id++;
}

const char* get_string(int n) {
    if (n >= 0 && n < id) {
        int l = strings[n].len + 1;
        if (l > buflen) {
            if (buf != NULL)
                free(buf);
            buf = malloc(l);
            buflen = l;
            if (buf == NULL) {
                perror("malloc");
                exit(1);
            }
        }
        fseek(strings[n].file, strings[n].off, SEEK_SET);
        fread(buf, 1, strings[n].len, strings[n].file);
        buf[strings[n].len] = '\0';
        filter_utf8(buf);
        return buf;
    }
    return "";
}

void clear_strings() {
    if (buf)
        free(buf);
}
