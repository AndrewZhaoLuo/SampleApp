#ifndef WARNINGALARMSUBSYSTEM_H
#define WARNINGALARMSUBSYSTEM_H

// rate in milliseconds to flash warning lights
#define FUEL_FLASH_PERIOD 2000
#define BATTERY_FLASH_PERIOD 1000

#include "bool.h"

typedef struct warningAlarmDataStruct{
    Bool* fuelLowPtr;
    Bool* batteryLowPtr;
    unsigned short* batteryLevelPtr;
    unsigned short* fuelLevelPtr;
} warningAlarmData;

void warningAlarmFunction(void* data);

#endif
