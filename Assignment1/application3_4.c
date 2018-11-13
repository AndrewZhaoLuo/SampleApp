#include <stdio.h>
#include <time.h>

/*
This application blinks A B C D, where A and C blink at a one second rate
and B and D blink at a two second rate.

By Team AAA, copyright 2018.
*/

/*
Delay is a function which waits at least the given
number of milliseconds. It may wait more based on
how scheduling of threads is done on your system.

Note that this method makes use of clock() from time.h
so performance will be based on how you implement that.

On most systems it will wait basically your given millis
plus a few clock cycles.
*/
void delay(volatile long millis) {
    clock_t start_time = clock();

    // the interval in milliseconds converted to clock intervals
    clock_t interval = ((double)(millis) / 1000.0) * CLOCKS_PER_SEC;

    while(clock() < start_time + interval);
}

int main(void)
{
    // note spec is unclear what offset B D should flash in relation to A and C
	while (1) {
        // Print each of these strings, overwriting the previous
        // line and persist for 1000 millis
        printf ("\rA   C  ");
        fflush(stdout);
        delay(1000);

        printf ("\r       ");
        fflush(stdout);
        delay(1000);

        printf ("\rA B C D");
        fflush(stdout);
        delay(1000);

        printf ("\r  B   D");
        fflush(stdout);
        delay(1000);
	}

	return 0;
}
