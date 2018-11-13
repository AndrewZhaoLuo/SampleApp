#include <stdio.h>
#include "globals.h"
#include "warningAlarmSubsystem.h"

void warningAlarmFunction(void* data) {
    // Cast to correct pointer
    warningAlarmData* warningData = (warningAlarmData*) data;

    unsigned short fuelLevel = *(warningData->fuelLevelPtr);
    unsigned short batteryLevel = *(warningData->batteryLevelPtr);
    Bool fuelLow = *(warningData->fuelLowPtr);  // Fuel is less than or equal to 10
    Bool batteryLow = *(warningData->batteryLowPtr);  // Battery is less than or equal to 10

    printf("SUBSYSTEM WARNING:\n");
    if(fuelLevel > 50 && batteryLevel > 50){
        // Display on annunciation panel in SOLID GREEN
        printf("\tGREEN: FUEL\n");
        printf("\tGREEN: BATTERY\n");
    }
    else if (fuelLevel > 50 && batteryLevel <= 50 && batteryLevel > 10) {
        printf("\tGREEN: FUEL\n");
        printf("\tORANGE: BATTERY\n"); // Flash at 1 second rate
    }
    else if (fuelLevel > 50 && batteryLow) {
        printf("\tGREEN: FUEL\n");
        printf("\tRED: BATTERY\n"); // Flash at 1 second rate
    }
    else if (fuelLevel <= 50 && fuelLevel > 10 && batteryLevel > 50) {
        printf("\tORANGE: FUEL\n");  // Flash at 2 second rate
        printf("\tGREEN: BATTERY\n");
    }
    else if (fuelLevel <= 50 && fuelLevel > 10 && batteryLevel <= 50 && batteryLevel > 10) {
        printf("\tORANGE: FUEL\n");  // Flash at 2 second rate
        printf("\tORANGE: BATTERY\n"); // Flash at 1 second rate
    }
    else if (fuelLevel <= 50 && fuelLevel > 10 && batteryLow) {
        printf("\tORANGE: FUEL\n");  // Flash at 2 second rate
        printf("\tRED: BATTERY\n"); // Flash at 1 second rate
    }
    else if(fuelLow && batteryLevel > 50){
        // Display on annunciation panel in SOLID GREEN
        printf("\tRED: FUEL\n"); // Flash at 2 second rate
        printf("\tGREEN: BATTERY\n");
    }
    else if(fuelLow && batteryLevel <= 50 && batteryLevel > 10){
        // Display on annunciation panel in SOLID GREEN
        printf("\tRED: FUEL\n"); // Flash at 2 second rate
        printf("\tORANGE: BATTERY\n"); // Flash at 1 second rate
    }
    else if(fuelLow && batteryLow){
        // Display on annunciation panel in SOLID GREEN
        printf("\tRED: FUEL\n"); // Flash at 2 second rate
        printf("\tRED: BATTERY\n"); // Flash at 1 second rate
    }
    printf("\n");
}
