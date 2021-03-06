#ifndef SATELLITECOMSSUBSYSTEM_H
#define SATELLITECOMSSUBSYSTEM_H

// tell houston we have a problem when our resources become too low...
#define MEDIUM_LEVEL_BATTERY_WARNING 61
#define MEDIUM_LEVEL_FUEL_WARNING 50
#define LOW_LEVEL_BATTERY_WARNING 35
#define LOW_LEVEL_FUEL_WARNING 25
#define FIVE_SECONDS 5000
#define TEN_SECONDS 10000

// range of values that can be received as a "command"
#define RANDOM_MIN_CMD 0
#define RANDOM_MAX_CMD 65535
#define NO_NEW_FREQUENCY_INFO -1

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
    int* last_freq;
    char* commandPtr;
    char* PS4commandPtr;
    char* responsePtr;
    Bool* isEarthTerminalPtr;
    Bool* schedCommandTaskPtr;
    Bool* schedVehicleCommsPtr;
    char** responseMessagePtr;
    Bool* isNewResponsePtr;
    Bool* userThrustValuePtr;
    unsigned short* batteryTempPtr;
    unsigned short* transportDistPtr;
    char** initials;
    char** date;
    int* pirateDistance;
    Bool* pirateDetected;
} satelliteComsData;

void satelliteComsFunction(void* data);

#endif
