#include "clock.h"
#include "TCB.h"

// similar example as what is done in the EE474 lecture notes
// and examples kernels on the website for the class
void invoke(TCB* tcb) {
    (tcb -> taskPtr)(tcb -> taskDataPtr);
}

void initTCB(TCB* tcb, void* taskDataPtr, void (*taskPtr)(void*), TaskPriority priority) {
    tcb -> taskDataPtr = taskDataPtr;
    tcb -> taskPtr = taskPtr;
    tcb -> priority = priority;
}
