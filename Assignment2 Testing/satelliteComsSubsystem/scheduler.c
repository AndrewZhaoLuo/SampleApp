#include "scheduler.h"
#include "clock.h"
#include "taskqueue.h"
#include "TCB.h"

// fill scheduler.h's definition via extern
// length of the cycles in milliseconds
long long MAJOR_CYCLE = 1000;
long long MINOR_CYCLE = 100;

// waits until current cycle is over
void scheduleAndRun(Scheduler* scheduler, Taskqueue* queue) {
    long long currentTime = getTimeMillis();

    int isMajor = currentTime >= scheduler -> nextEndMajor; // are you after a major cycle
    int isMinor = currentTime >= scheduler -> nextEndMinor;

    cycleLevel level = CYCLE_REAL_TIME;
    if (isMinor) {
        scheduler -> nextEndMinor = currentTime + MINOR_CYCLE;
        level = CYCLE_MINOR;
    }
    if (isMajor) {
        scheduler -> nextEndMajor = currentTime + MAJOR_CYCLE;
        level = CYCLE_MAJOR;
    }
    int i;
    for (i = 0; i < queue -> length; i++) {
        TCB* curTCB = getNextTCB(queue);

        if (level == CYCLE_MAJOR) {
            // if a major cycle run everything
            invoke(curTCB);
        } else if (level == CYCLE_MINOR && curTCB -> priority != PRIORITY_LOW){
            invoke(curTCB);
        } else if (level == CYCLE_REAL_TIME && curTCB -> priority == PRIORITY_REAL_TIME) {
            invoke(curTCB);
        }
    }
}

void initScheduler(Scheduler* scheduler) {
    scheduler -> nextEndMajor = 0;
    scheduler -> nextEndMinor = 0;
}
