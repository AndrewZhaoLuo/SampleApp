#include <stdio.h>
#include <time.h>

/*
This application blinks A B C D, where A and C blink at a one second rate
and B and D blink at a two second rate.

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
        printf ("\rA   C  ");
        fflush(stdout);
        delay();

        printf ("\r  B   D");
        fflush(stdout);
        int i = 0;
        for (i = 0; i <2; i++) {
            delay();
        }
	}

	return 0;
}
