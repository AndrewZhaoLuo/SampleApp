#include "clock.h"

/*
This file contains the system specific implementation of the clock function.
This one is made for the Arduino environment to be used for the demo

// TODO: make a software delay
*/
unsigned long long getTimeMillis() {
    return millis();
}
