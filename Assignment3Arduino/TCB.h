#ifndef TCB_H_INCLUDED
#define TCB_H_INCLUDED

// priority levels are like so: REAL_TIME > HIGH > LOW
typedef enum {PRIORITY_REAL_TIME, PRIORITY_HIGH, PRIORITY_LOW} TaskPriority;

typedef struct
{
	void* taskDataPtr;
	void (*taskPtr)(void*);
    TaskPriority priority;

    // estimated time to execute task on average in millis
    double penaltyMillis;
}
TCB;

// invokes TCB's function, passing in the given task info
// schedules the TCB to run at least the given number of
// milliseconds next from the current time.
//
// returns 1 if the task was invoked
// returns 0 if the task was not invoked
void invoke(TCB* tcb);

// initialize TCB with the given info
void initTCB(TCB* tcb, void* taskDataPtr, void (*taskPtr)(void*), TaskPriority priority, double penaltyMillis);

#endif // TCB_H_INCLUDED
