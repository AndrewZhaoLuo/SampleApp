#include <stdio.h>
#include <time.h>

/*
This application blinks A B C D to stdout at a one second rate.

By Team AAA, copyright 2018.
*/

void delay() {
    int sec = 600000000;
    volatile int i = 0;
    for (i = sec; i > 0;) {
        i--;
    }
}

int main(void)
{
    while (1) {
        // print A B C D to console, overwriting previous line
        // and persist for at least one second
        printf ("\rA B C D");
        fflush(stdout);
        delay();

        // then clear line and persist for at least one second
        printf ("\r       ");
        fflush(stdout);
        delay();
	}

	return 0;
}
