#define CPS 100
#define WAIT_MS 100

/* delay for the requisite amount of time to hit the target CPS rate */
void slow_char(int chars);

/* wait for the given number of wait periods */
void wait(int n);
