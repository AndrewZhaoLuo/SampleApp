// a queue and scheduler implemented at once!
#ifndef TASKQUEUE_H_INCLUDED
#define TASKQUEUE_H_INCLUDED

#include "TCB.h"
#include <Arduino.h>

// essentially an array where the
// next index to be used is processed
typedef struct
{
    TCB* head;
    TCB* tail;
    int length;
}
Taskqueue;

void initTaskQueue(Taskqueue* queue);

void addToTail(Taskqueue* queue, TCB* tcb);
void addToHead(Taskqueue* queue, TCB* tcb);

TCB* removeHead(Taskqueue* queue);
TCB* removeTail(Taskqueue* queue);

// returns the next task in the queue
TCB* getNextTCB(Taskqueue* queue);

#endif // TASKQUEUE_H_INCLUDED
