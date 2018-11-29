#include "clock.h"
#include <Arduino.h>

// for idle loop
static volatile int i = 0;

/*
This file contains the system specific implementation of the clock function.
This one is made for the Arduino environment to be used for the demo.

It uses a software delay and takes into account penalties from running tasks

TODO: what to do on overflow.
*/
unsigned long long getTimeMillis() {
    return millis();
}
