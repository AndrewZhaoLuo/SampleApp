#ifndef TCB_H_INCLUDED
#define TCB_H_INCLUDED
// priority levels are like so: REAL_TIME > HIGH > LOW
typedef enum {PRIORITY_REAL_TIME = 1,
              PRIORITY_CRITICAL = 2,
              PRIORITY_HIGH = 3,
              PRIORITY_MEDIUM = 4,
              PRIORITY_LOW = 5, } TaskPriority;

typedef struct Task
{
	void* taskDataPtr;
	void (*taskPtr)(void*);
    TaskPriority priority;

    struct Task* next;
    struct Task* prev;
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
