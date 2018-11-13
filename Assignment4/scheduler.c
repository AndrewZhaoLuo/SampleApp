#include "scheduler.h"
#include "clock.h"
#include "taskqueue.h"
#include "TCB.h"
#include "globals.h"
#include "print_format.h"

// reschedule taskqueue after we are done
void reschedule() {
  addToHead(&queue, &tcbs[COMS_DATA_TCB]);

  if (batteryConnectedFlag) {
    addToHead(&queue, &tcbs[POWER_DATA_TCB]);
  }

  addToHead(&queue, &tcbs[THRUSTER_DATA_TCB]);
  addToHead(&queue, &tcbs[WARNING_DATA_TCB]);
  addToHead(&queue, &tcbs[DISPLAY_DATA_TCB]);
  addToHead(&queue, &tcbs[VEHICLE_DATA_TCB]);

  if (solarPanelConnectedFlag && (solarPanelDeploy | solarPanelRetract)) {
    addToHead(&queue, &tcbs[PANEL_DATA_TCB]);
    addToHead(&queue, &tcbs[KEYPAD_DATA_TCB]);
    // add solar panel control task
  }
}

// waits until current cycle is over
void scheduleAndRun(Scheduler* scheduler, Taskqueue* queue) {
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
        } else if (level == CYCLE_MINOR && curTCB -> priority != PRIORITY_LOW){
            invoke(curTCB);
        } else if (level == CYCLE_REAL_TIME && curTCB -> priority == PRIORITY_REAL_TIME) {
            invoke(curTCB);
        }
    }

    reschedule();
}

void initScheduler(Scheduler* scheduler) {
    scheduler -> nextEndMajor = 0;
    scheduler -> nextEndMinor = 0;
}
