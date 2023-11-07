#include "slow.h"

#include <dos.h>

void slow_char(int chars) {
	delay(1000 / CPS);
}