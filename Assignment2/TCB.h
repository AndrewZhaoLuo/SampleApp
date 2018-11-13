#ifndef TCB_H_INCLUDED
#define TCB_H_INCLUDED
typedef enum {PRIORITY_REAL_TIME, PRIORITY_HIGH, PRIORITY_LOW} TaskPriority;

typedef struct
{
	void* taskDataPtr;
	void (*taskPtr)(void*);
    TaskPriority priority;
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
void initTCB(TCB* tcb, void* taskDataPtr, void (*taskPtr)(void*), TaskPriority priority);

#endif // TCB_H_INCLUDED
