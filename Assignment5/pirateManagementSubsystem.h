#ifndef PIRATEMANAGEMENTSUBSYSTEM_H_INCLUDED
#define PIRATEMANAGEMENTSUBSYSTEM_H_INCLUDED

#include "bool.h"

// map of frequency -> distance is simple
#define THRESHOLD_PHASORS 30
#define THRESHOLD_TORPEDO 5

typedef struct pirateManagementStruct {
    int* pirateDistance;
    Bool* firePhasor;
    Bool* fireTorpedo;
} pirateManagementData;

void pirateManagementFunction(void* data);

#endif // PIRATEMANAGEMENTSUBSYSTEM_H_INCLUDED
