#include <stdio.h>
#include <time.h>

/*
This application blinks A, then B then C then D with one
second delay between them. Afterwards, repeats process.

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
    while(1){
        printf ("\rA      ");
        fflush(stdout);
        delay();

        printf ("\r  B    ");
        fflush(stdout);
        delay();

        printf ("\r    C  ");
        fflush(stdout);
        delay();

        printf ("\r      D");
        fflush(stdout);
        delay();
    }

	return 0;
}
