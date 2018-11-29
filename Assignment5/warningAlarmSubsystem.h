#ifndef WARNINGALARMSUBSYSTEM_H
#define WARNINGALARMSUBSYSTEM_H

// rate in milliseconds to flash warning lights
#define FUEL_FLASH_PERIOD 2000
#define BATTERY_FLASH_PERIOD 1000
#define FIVE_SECONDS 5000
#define TEN_SECONDS 10000
#define FIFTEEN_SECONDS 15000
#define ALARM_FLASH_PERIOD 5000

#define ALARM_OFF 0
#define FLUSH_X_COORD 0
#define FLUSH_Y_TEMP 120
#define FLUSH_Y_FUEL 80
#define FLUSH_Y_BATTERY 40

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
