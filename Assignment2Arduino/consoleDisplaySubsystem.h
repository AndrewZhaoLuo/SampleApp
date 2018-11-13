#ifndef CONSOLEDISPLAYSUBSYSTEM_H
#define CONSOLEDISPLAYSUBSYSTEM_H

// all values should be flush 140 pixels from left side of screen
#define TEXT_ALIGN_X 140

// all field names should be aligned at 0 for x coord.
#define FIELD_ALIGN_X 0

// all headers should be at the very top of the screen
#define HEADER_ALIGN_Y 0

// y-coordinates to start printing assoc. values for
#define Y_STATE 30
#define Y_BATTERY 50
#define Y_FUEL 70
#define Y_POWER 90

#define FONTSIZE 1

// max width of the string to print
#define MAX_VALUE_WIDTH 20

// for TRUE/FALSE
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

/*
See specification/report for full functionality
*/
void consoleDisplayFunction(void* data);

#endif
