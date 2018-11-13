#include "clock.h"
#include "TCB.h"

// similar example as what is done in the EE474 lecture notes
// and examples kernels on the website for the class
void invoke(TCB* tcb) {
    // run task and increment clock's penalty counter
    (tcb -> taskPtr)(tcb -> taskDataPtr);
    incrementPenalty(tcb -> penaltyMillis);
}

void initTCB(TCB* tcb, void* taskDataPtr, void (*taskPtr)(void*), TaskPriority priority, double penaltyMillis) {
    tcb -> taskDataPtr = taskDataPtr;
    tcb -> taskPtr = taskPtr;
    tcb -> priority = priority;
    tcb -> penaltyMillis = penaltyMillis;
}
