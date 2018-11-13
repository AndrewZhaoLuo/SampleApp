#include <stdio.h>
#include <time.h>

/*
This application blinks A B C D, where A and C blink at a one second rate
and B and D blink at a two second rate.

By Team AAA, copyright 2018.
*/

int DELAY_ONE_SECOND = 1;
int DELAY_TWO_SECOND = 2;

// Displays str for  aprox. num_secs seconds to console. Max char* length of 20 characters.
void tempPrint(char* str, int num_secs) {
    printf("\r%s                    ", str);
    fflush(stdout);
    int sec = 600000000;
    volatile int i = 0;
    for (i = sec * (num_secs); i > 0;) {
        i--;
    }
}

// Alternate displaying "A   C" for 1 second and "  B   D" for 2 seconds on the display.
int main(void)
{
	while (1) {
        tempPrint("A   C  ", DELAY_ONE_SECOND);
        tempPrint("  B   D", DELAY_TWO_SECOND);
	}

	return 0;
}
