#ifndef POWERSUBSYSTEM_H
#define POWERSUBSYSTEM_H

/*
Why deploy at 60? In the worst case we are at 61 and 12 consumption

Battery:     61 25 17  9  5   1 --- phew barely lived!
Consumption: 12 10 11  9  10  8
Generation:   0  2  3  5  6   8
              ^
              |____where we start solar panels
              56 - 12
              20
*/
#define BATTERY_LEVEL_DEPLOY 61
#define BATTERY_LEVEL_RETRACT 95
#define CONSUMPTION_LIMIT 10
#define CONSUMPTION_FLOOR 5
#define HIGH_BATTERY_LEVEL 95
#define LOW_BATTERY_LEVEL 50

#include "bool.h"

typedef struct powerSubsystemDataStruct {
    Bool* solarPanelStatePtr;
    unsigned short* batteryLevelPtr;
    unsigned short* powerConsumptionPtr;
    unsigned short* powerGenerationPtr;
    int callCounter;
    Bool increaseConsumption;
} powerSubsystemData;

void powerSubsystemFunction(void* data);

#endif
