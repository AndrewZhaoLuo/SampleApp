#include "globals.h"
#include "satelliteComsSubsystem.h"
#include "rand1.h"
#include "print_format.h"

void satelliteComsFunction(void* data) {
    // Cast to correct pointer
    satelliteComsData* comsData = (satelliteComsData*) data;

    *(comsData->thrustCommandPtr) = randomInteger(RANDOM_MIN_CMD, RANDOM_MAX_CMD);

    // Set battery low
    if(*(comsData->batteryLevelPtr) <= LOW_LEVEL_BATTERY_WARNING){
        *(comsData->batteryLowPtr) = TRUE;
    } else {
        *(comsData->batteryLowPtr) = FALSE;
    }

    // Set fuel low
    if(*(comsData->fuelLevelPtr) <= LOW_LEVEL_FUEL_WARNING) {
        *(comsData->fuelLowPtr) = TRUE;
    } else {
        *(comsData->fuelLowPtr) = FALSE;
    }

    // for debugging
    //print_format("SUBSYSTEM SATELLITE:\n");
    //print_format("\tFuel Low Warning %d\n\tBattery Low Warning %d\n", *(comsData->fuelLowPtr), *(comsData->batteryLowPtr));
}
