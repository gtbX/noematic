void filter_utf8(char* str) {
    char* a = str, *b = str;
    do {
        if (!(*b & 0x80)) {
            *a++ = *b++; /* pass through ASCII unmodified */
        } else {
            int cp;
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
    } while (*b != '\0');
}
