#ifndef SCHEDULER_H_INCLUDED
#define SCHEDULER_H_INCLUDED

// length of the cycles in milliseconds
#define MAJOR_CYCLE 1000
#define MINOR_CYCLE 20

#include "taskqueue.h"

// whether we are running as if after a major cycle, a minor cycle
// or neither (real time execution -- as fast as the clock can go!) only
typedef enum {CYCLE_MAJOR, CYCLE_MINOR, CYCLE_REAL_TIME} cycleLevel;

typedef struct {
    // the time where to end the next major cycle
    long long nextEndMajor;

    // the time where to end the next minor cycle
    long long nextEndMinor;
} Scheduler;

// waits until current cycle is over
void scheduleAndRun(Scheduler* scheduler, Taskqueue* queue);

void initScheduler(Scheduler* scheduler);

#endif // SCHEDULER_H_INCLUDED
