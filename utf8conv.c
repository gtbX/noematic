#include "utf8.h"
char* filter_utf8(char* str) {
    unsigned char* a = str, *b = str;
    while (*b != '\0') {
        if (!(*b & 0x80)) {
            *a++ = *b++; /* pass through ASCII unmodified */
        } else {
	    unsigned long cp;
	    if ((*b & 0xE0) == 0xC0) {
		cp = (*b++ & ~0xE0) << 6;
		cp |= (*b++ & ~0xC0);
	    } else if ((*b & 0xF0) == 0xE0) {
		cp = (*b++ & ~0xF0) << 12;
		cp |= (*b++ & ~0xC0) << 6;
		cp |= (*b++ & ~0xC0);
	    } else if ((*b & 0xF8) == 0xF0) {
		cp = (*b++ & ~0xF8) << 18;
		cp |= (*b++ & ~0xC0) << 12;
		cp |= (*b++ & ~0xC0) << 6;
		cp |= (*b++ & ~0xC0);
	    }
	    *a++ = decode_point(cp);
	}
    }
    *a = '\0';
    return str;
}
