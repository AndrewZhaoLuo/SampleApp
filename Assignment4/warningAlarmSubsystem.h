#ifndef WARNINGALARMSUBSYSTEM_H
#define WARNINGALARMSUBSYSTEM_H

// rate in milliseconds to flash warning lights
#define FUEL_FLASH_PERIOD 2000
#define BATTERY_FLASH_PERIOD 1000
#define TEN_SECONDS 10000
#define FIFTEEN_SECONDS 15000
#define ALARM_FLASH_PERIOD 5000

#include "bool.h"

typedef struct warningAlarmDataStruct{
    Bool* fuelLowPtr;
    Bool* batteryLowPtr;
    unsigned short* batteryLevelPtr;
    unsigned short* fuelLevelPtr;
    int* tempAlarmStatePtr; // For alarm system
    unsigned long long* tempAlarmTriggeredTimePtr;
} warningAlarmData;

void warningAlarmFunction(void* data);

#endif
