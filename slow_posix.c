#include "slow.h"

#include <unistd.h>

void slow_char(int chars) {
    usleep(chars * 1000000 / CPS);
}

void wait(int n) {
    usleep(n * WAIT_MS * 1000);
}
