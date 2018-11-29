#ifndef CLOCK_H_INCLUDED
#define CLOCK_H_INCLUDED

// penalty for running getTimeMillis or incrementPenalty
// in millis, so meta! empirically estimated based on 100000 loop trial
#define CLOCK_CASTING_PENALTY 0.08L

// number of idle iterations in for loop to waste 0.01s
#define IDLE_LOOPS_CENTISECOND 6000

/*
Gets the current system time in milliseconds. It however
has accuracy only up to centiseconds!

The current system time should be based on a common
point in the past, e.g. January 1st 1970 or the
time the system started running, between calls
in the same continual operation of the system.
*/
unsigned long long getTimeMillis();
#endif // CLOCK_H_INCLUDED
