#include <stdio.h>
#include <time.h>

/*
This application blinks A B C D, where A and C blink at a one second rate
and B and D blink at a two second rate.

By Team AAA, copyright 2018.
*/

#include "tempPrint.c"

int DELAY_ONE_SECOND = 1;
int DELAY_TWO_SECOND = 2;
int TICS_PER_SEC = 600000000;

// Alternate displaying "A   C" for 1 second and "  B   D" for 2 seconds on the display.
int main(void)
{
	while (1) {
        tempPrint("A   C  ", DELAY_ONE_SECOND, TICS_PER_SEC);
        tempPrint("  B   D", DELAY_TWO_SECOND, TICS_PER_SEC);
	}

	return 0;
}
