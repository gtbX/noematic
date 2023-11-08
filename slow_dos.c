#include "slow.h"

#include <dos.h>

void slow_char(int chars) {
	delay(chars * 1000 / CPS);
}

void wait(int n) {
	delay(n * WAIT_MS);
}
