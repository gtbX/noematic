#include "text.h"

#include <stdio.h>

#include "strtable.h"
#include "symtable.h"

int read_sym_name(const char* str, char* buf) {
    size_t n = 0;
    while (*str && *str != '\'' && n < SYM_LEN - 1) {
        *buf++ = *str++;
        n++;
    }
    *buf = '\0';
    return n;
}

void print_text(const char* text) {
    while (*text) {
        if (*text == '%') {
            switch (*++text) {
            case 't':
                if (*++text == '\'') {
                    char sym[SYM_LEN];
                    int *var;
                    text++;
                    text += read_sym_name(text, sym);
                    if (*text == '\'')
                        text++;
                    var = get_var(get_sym(sym));
                    print_text(get_string(var ? *var : -1));
                }
                break;
            }
        } else {
            putchar(*text++);
        }
    }
}
