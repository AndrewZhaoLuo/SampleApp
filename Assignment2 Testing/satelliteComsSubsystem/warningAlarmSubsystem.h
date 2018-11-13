#ifndef WARNINGALARMSUBSYSTEM_H
#define WARNINGALARMSUBSYSTEM_H

#include "bool.h"

typedef struct warningAlarmDataStruct{
    Bool* fuelLowPtr;
    Bool* batteryLowPtr;
    unsigned short* batteryLevelPtr;
    unsigned short* fuelLevelPtr;
} warningAlarmData;

void warningAlarmFunction(void* data);

#endif
