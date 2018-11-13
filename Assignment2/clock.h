#ifndef CLOCK_H_INCLUDED
#define CLOCK_H_INCLUDED

/*
Gets the current system time in milliseconds.

The current system time should be based on a common
point in the past, e.g. January 1st 1970 or the
time the system started running, between calls
in the same continual operation of the system.
*/
unsigned long long getTimeMillis();

#endif // CLOCK_H_INCLUDED
