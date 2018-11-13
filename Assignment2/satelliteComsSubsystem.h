#ifndef SATELLITECOMSSUBSYSTEM_H
#define SATELLITECOMSSUBSYSTEM_H
#define LOW_LEVEL_BATTERY_WARNING 10
#define LOW_LEVEL_FUEL_WARNING 10

#include "bool.h"

typedef struct satelliteComsDataStruct {
    unsigned int* thrustCommandPtr;
    unsigned short* batteryLevelPtr;
    unsigned short* fuelLevelPtr;
    unsigned short* powerConsumptionPtr;
    unsigned short* powerGenerationPtr;
    Bool* solarPanelStatePtr;
    Bool* fuelLowPtr;
    Bool* batteryLowPtr;
} satelliteComsData;

void satelliteComsFunction(void* data);

#endif
