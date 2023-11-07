#include "slow.h"

#include <unistd.h>

void slow_char(int chars) {
    /* 5000us = 1/200s */
    usleep(chars * 10000);
}
