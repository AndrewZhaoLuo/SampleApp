#ifndef SCHEDULER_H_INCLUDED
#define SCHEDULER_H_INCLUDED

#include "taskqueue.h"

// length of the cycles in milliseconds
extern long long MAJOR_CYCLE;
extern long long MINOR_CYCLE;

// whether we are running as if after a major cycle, a minor cycle
// or neither (real time) only
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
