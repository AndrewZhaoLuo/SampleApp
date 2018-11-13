// a queue and scheduler implemented at once!
#ifndef TASKQUEUE_H_INCLUDED
#define TASKQUEUE_H_INCLUDED

#include "TCB.h"

typedef struct
{
    TCB* tcbArray;
    int length;
    int cur_index;
}
Taskqueue;

void initTaskQueue(Taskqueue* queue, TCB* tcbArray, int length);

// returns the next task in the queue
TCB* getNextTCB(Taskqueue* queue);

#endif // TASKQUEUE_H_INCLUDED
