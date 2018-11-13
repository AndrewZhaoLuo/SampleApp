#include "taskqueue.h"

void initTaskQueue(Taskqueue* queue) {
    queue -> head = NULL;
    queue -> tail = NULL;
    queue -> length = 0;
}

void addToTail(Taskqueue* queue, TCB* tcb) {
    if (queue -> length == 0) {
        addToHead(queue, tcb);
        return;
    }

    TCB* tmp = queue -> tail;
    queue -> tail -> next = tcb;
    queue -> tail = tcb;
    queue -> tail -> next = NULL;
    queue -> tail -> prev = tmp;

    queue -> length++;
}

void addToHead(Taskqueue* queue, TCB* tcb) {
    if (queue -> head == NULL) {
        queue -> head = queue -> tail = tcb;
        queue -> length++;
        return;
    }

    TCB* tmp = queue -> head;
    queue -> head -> prev = tcb;
    queue -> head = tcb;
    queue -> head -> prev = NULL;
    queue -> head -> next = tmp;
    
    queue -> length++;
}

TCB* removeHead(Taskqueue* queue) {
    if (queue -> head == NULL) {
        return NULL;
    }

    if (queue -> length == 1) {
        queue -> length--;
        TCB* tmp = queue -> head;
        queue -> head = queue -> tail = NULL;
        return tmp;
    }

    TCB* tmp = queue -> head;
    queue -> head = queue -> head -> next;
    queue -> head -> prev = NULL;
    queue -> length--;
    return tmp;
}

TCB* removeTail(Taskqueue* queue) {
    if (queue -> tail == NULL || queue -> length == 1) {
        return removeHead(queue);
    }

    TCB* tmp = queue -> tail;
    queue -> tail = queue -> tail -> prev;
    queue -> tail -> next = NULL;
    queue -> length--;
    return tmp;
}

// returns the next task in the queue
TCB* getNextTCB(Taskqueue* queue) {
    if (queue -> length == 0) return NULL;

    TCB* head = removeHead(queue);
    //addToTail(queue, head);
    return head;
}
