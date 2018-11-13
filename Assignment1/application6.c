#include <stdio.h>
#include <time.h>

/*
This application blinks A B C D, where A and C blink at a one second rate
and B and D blink at a two second rate.

By Team AAA, copyright 2018.
*/

int DELAY_ONE_SECOND = 1;
int DELAY_TWO_SECOND = 2;

void delay(int* num_secs) {
    int sec = 600000000;
    volatile int i = 0;
    for (i = sec * (*num_secs); i > 0;) {
        i--;
    }
}

int main(void)
{
	while (1) {
        printf ("\rA   C  ");
        fflush(stdout);
        delay(&DELAY_ONE_SECOND);

        printf ("\r  B   D");
        fflush(stdout);
        delay(&DELAY_TWO_SECOND);
	}

	return 0;
}
