#include <sys/time.h>

/*
This file contains the system specific implementation of clock function.
This one is made for the testing environment on the area.
Based on:

https://stackoverflow.com/questions/3756323/how-to-get-the-current-time-in-milliseconds-from-c-in-linux

// TODO: make a software delay
*/
unsigned long long getTimeMillis() {
    struct timeval te;
    gettimeofday(&te, NULL); // get current time
    long long milliseconds = te.tv_sec*1000LL + te.tv_usec/1000; // calculate milliseconds
    return milliseconds;
}
