#define CPS 100 /* text output speed in chars per second */
#define WAIT_MS 100 /* base wait time of %w1 command, in ms */

/* delay for the requisite amount of time to hit the target CPS rate */
void slow_char(int chars);

/* wait for the given number of wait times */
void wait(int n);
