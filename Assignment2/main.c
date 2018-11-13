#include <stdio.h>
#include "TCB.h"
#include "scheduler.h"
#include "globals.h"

#define LENGTH 5

//  Declare the prototypes for the tasks
void get (void* aNumber);
void increment (void* aNumber);
void display (void* aNumber);

TCB tcbs[LENGTH];

int main(void)
{
    printf("Starting...\n");
    Scheduler scheduler;
    initScheduler(&scheduler);
    initialize();

    initTCB(&tcbs[0], (void*)&powerData, powerSubsystemFunction, PRIORITY_LOW);
    initTCB(&tcbs[1], (void*)&comsData, satelliteComsFunction, PRIORITY_LOW);
    initTCB(&tcbs[2], (void*)&thrusterData, thrusterSubsystemFunction, PRIORITY_LOW);
    initTCB(&tcbs[3], (void*)&displayData, consoleDisplayFunction, PRIORITY_LOW);
    initTCB(&tcbs[4], (void*)&warningData, warningAlarmFunction, PRIORITY_HIGH);

    Taskqueue queue;
    initTaskQueue(&queue, tcbs, LENGTH);

    while (1) scheduleAndRun(&scheduler, &queue);

	return 0;
}

void get (void* aNumber)
{
    int* number = (int*) aNumber;

	printf ("GET() %d\n", *number);
	return;
}

void increment (void* aNumber)
{
    int* number = (int*) aNumber;

	printf ("INCREMENT() %d\n", *number);
	return;
}

void display (void* aNumber)
{
    int* number = (int*) aNumber;

	printf ("DISPLAY() %d\n", *number);
	return;
}
