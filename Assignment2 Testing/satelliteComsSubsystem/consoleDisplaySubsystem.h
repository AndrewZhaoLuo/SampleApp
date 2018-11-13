#ifndef CONSOLEDISPLAYSUBSYSTEM_H
#define CONSOLEDISPLAYSUBSYSTEM_H

#include "bool.h"

typedef struct consoleDisplayDataStruct {
    unsigned int* thrustCommandPtr;
    unsigned short* batteryLevelPtr;
    unsigned short* fuelLevelPtr;
    unsigned short* powerConsumptionPtr;
    unsigned short* powerGenerationPtr;
    Bool* solarPanelStatePtr;
    Bool* fuelLowPtr;
    Bool* batteryLowPtr;
} consoleDisplayData;

void consoleDisplayFunction(void* data);

#endif
