#include "scheduler.h"
#include "clock.h"
#include "taskqueue.h"
#include "TCB.h"
#include "globals.h"
#include "print_format.h"

// Dynamically reschedules tasks highest -> lowest priority.
// POWER_DATA requires global flag
// KEYPAD_DATA && PANEL_DATA require global flag
void reschedule() {
  for (int insertPriorityThreshold = 0; insertPriorityThreshold < LENGTH; insertPriorityThreshold++) { // Look at every task
    for (int TCB_NUM = 0; TCB_NUM < LENGTH; TCB_NUM++) {
      TCB* curTCB = &tcbs[TCB_NUM];
      int curPriority = curTCB -> priority;
      if (curPriority == insertPriorityThreshold) {
        // Only connect power_data if battery connected
        if (TCB_NUM == POWER_DATA_TCB && !batteryConnectedFlag) continue;
        // Only connect Keypad_data and panal_data if
        if ((TCB_NUM == KEYPAD_DATA_TCB || TCB_NUM == PANEL_DATA_TCB)
            && !(solarPanelConnectedFlag && (solarPanelDeploy | solarPanelRetract))) {
           continue;
        }
        addToTail(&queue, &tcbs[TCB_NUM]);
      }
    }
  }
}

// waits until current cycle is over
void scheduleAndRun(Scheduler* scheduler, Taskqueue* queue) {
    static int curPriority = 0;
    curPriority++;
    if (curPriority > PRIORITY_LOW) curPriority = 1;

    long long currentTime = getTimeMillis();

    // are we after the completion of a major/minor cycle
    int isMajor = currentTime >= scheduler -> nextEndMajor;
    int isMinor = currentTime >= scheduler -> nextEndMinor;

    // set the priority level we should be running tasks on based on
    // whether we have completed a cycle or not
    cycleLevel level = CYCLE_REAL_TIME;
    if (isMinor) {
        scheduler -> nextEndMinor = currentTime + MINOR_CYCLE;
        level = CYCLE_MINOR;
    }

    if (isMajor) {
        scheduler -> nextEndMajor = currentTime + MAJOR_CYCLE;
        level = CYCLE_MAJOR;
    }

    // go through TCB queue, executing things if they are high enough priority
    while (queue -> length > 0) {
        TCB* curTCB = getNextTCB(queue);

        if (level == CYCLE_MAJOR) {
            // if a major cycle run everything
            invoke(curTCB);
        } else if (level == CYCLE_MINOR && curTCB -> priority <= curPriority && curTCB -> priority != PRIORITY_LOW) {
            invoke(curTCB);
        } else if (curTCB -> priority == PRIORITY_REAL_TIME) {
            invoke(curTCB);
        }
    }
    reschedule();
}

void initScheduler(Scheduler* scheduler) {
    scheduler -> nextEndMajor = 0;
    scheduler -> nextEndMinor = 0;
}
