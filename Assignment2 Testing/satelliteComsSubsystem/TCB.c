#include <stdio.h>
#include "clock.h"
#include "TCB.h"

void invoke(TCB* tcb) {
    (tcb -> taskPtr)(tcb -> taskDataPtr);
}

void initTCB(TCB* tcb, void* taskDataPtr, void (*taskPtr)(void*), TaskPriority priority) {
    tcb -> taskDataPtr = taskDataPtr;
    tcb -> taskPtr = taskPtr;
    tcb -> priority = priority;
}
