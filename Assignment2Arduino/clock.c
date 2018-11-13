#include "clock.h"

// milliseconds since program had started
static unsigned long long curMillis = 0;

// how long non-clock tasks have run, estimated
// based on empirics on how long tasks take to run
static double curPenaltyMillis = 0;

// for idle loop
static volatile int i = 0;

/*
This file contains the system specific implementation of the clock function.
This one is made for the Arduino environment to be used for the demo.

It uses a software delay and takes into account penalties from running tasks

TODO: what to do on overflow.
*/
unsigned long long getTimeMillis() {
    if (curPenaltyMillis > 1) {
        unsigned long long wholePenaltyMillis = (int) curPenaltyMillis;
        curPenaltyMillis -= wholePenaltyMillis;
        curMillis += curPenaltyMillis;
    } else {
        curPenaltyMillis += CLOCK_CASTING_PENALTY; // empirically found :O
        // loop over some number of seconds
        for (i = IDLE_LOOPS_CENTISECOND; i > 0;) {
          i--;
        } 
        curMillis += 10;
    }

    return curMillis;
}

void incrementPenalty(double penaltyMillis) {
  curPenaltyMillis += penaltyMillis + CLOCK_CASTING_PENALTY;
}
