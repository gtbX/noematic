#include "cp.h"

char decode_point(unsigned int cp) {
    if (cp < 128)
        return (char)cp;

    if (cp >= 0x2591 && cp <= 0x2593)
        return cp - (0x2591 - 0xB0);

    return '?';
}
