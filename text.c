#include "text.h"

#include <stdio.h>

#include "strtable.h"
#include "symtable.h"

int get_sym_var(const char** str) {
    char delim = *++*str;
    if (delim == '\'' || delim == '\"') {
        char sym[SYM_LEN], *s = sym;
        int* var;
        size_t n = 0;
        ++*str;
        while (**str && **str != delim && n < SYM_LEN - 1) {
            *s++ = *(*str)++;
            n++;
        }
        *s = '\0';
        if (**str == delim)
            ++*str;
        var = get_var(get_sym(sym));
        if (var)
            return *var;
    }
    return -1;
}

void print_text(const char* text) {
    while (*text) {
        if (*text == '%') {
            switch (*++text) {
            case 'O':
            case 'o':
                printf("%d", get_sym_var(&text));
                break;
            case 'T':
            case 't':
                print_text(get_string(get_sym_var(&text)));
                break;
            default:
                putchar('%');
                break;
            }
        } else {
            putchar(*text++);
        }
    }
}
