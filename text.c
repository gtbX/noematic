#include "text.h"

#include <stdlib.h>
#include <stdio.h>

#include "slow.h"
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

int get_num_arg(const char** str) {
    char buf[8] = "0", *num = buf;
    size_t n = 0;
    while (**str >= '0' && **str <= '9' && n < sizeof(buf) - 1) {
        *num++ = *(*str)++;
        n++;
    }
    *num = '\0';
    return atoi(buf);
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
            case 'W':
            case 'w':
                text++;
                wait(get_num_arg(&text));
                break;
            default:
                putchar('%');
                break;
            }
        } else {
            putchar(*text++);
            fflush(stdout);
            slow_char(1);
        }
    }
}
