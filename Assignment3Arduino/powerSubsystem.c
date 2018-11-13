#include "globals.h"
#include "powerSubsystem.h"
#include "print_format.h"

void powerSubsystemFunction(void* data){
    // Cast to correct pointer
    powerSubsystemData* powerData = (powerSubsystemData*) data;

    // Power Consumption, increase consumption/decrease consumption
    // based on whether system is currently increasing or decreasing
    // power use
    if(powerData->increaseConsumption) {
        if (powerData->callCounter % 2 == 0) {
            *(powerData->powerConsumptionPtr) += 2;
        } else {
            *(powerData->powerConsumptionPtr) -= 1;
        }
        if (*(powerData->powerConsumptionPtr) > CONSUMPTION_LIMIT) {
            powerData->increaseConsumption = FALSE;
        }
    } else {
        if (powerData->callCounter % 2 == 0) {
            *(powerData->powerConsumptionPtr) -= 2;
        } else {
            *(powerData->powerConsumptionPtr) += 1;
        }
        if (*(powerData->powerConsumptionPtr) < CONSUMPTION_FLOOR) {
            powerData->increaseConsumption = TRUE;
        }
    }

    // Power Generation, based on battery level (which effects charging efficiency)
    // and whether solar panels are active
    if(*(powerData->solarPanelStatePtr)) {  // Solar panel is deployed
        if (*(powerData->batteryLevelPtr) > BATTERY_LEVEL_RETRACT) {
            *(powerData->solarPanelStatePtr) = FALSE;
            // Engineering decision: When we retract solar panel, power generation is 0
            *(powerData->powerGenerationPtr) = 0;
        } else if (*(powerData->batteryLevelPtr) < LOW_BATTERY_LEVEL){
            if (powerData->callCounter % 2 == 0) {
                *(powerData->powerGenerationPtr) += 2;
            } else {
                *(powerData->powerGenerationPtr) += 1;
            }
        } else if (*(powerData->batteryLevelPtr) <= HIGH_BATTERY_LEVEL
                   && *(powerData->batteryLevelPtr) >= LOW_BATTERY_LEVEL) {
            if (powerData->callCounter % 2 == 0) {
                *(powerData->powerGenerationPtr) += 2;
            }
        }
    } else {  // Solar panel is not deployed
        if (*(powerData->batteryLevelPtr) <= BATTERY_LEVEL_DEPLOY) {
            *(powerData->solarPanelStatePtr) = TRUE;
        }
    }

    // Battery Level use based on given formula
    if(!(*(powerData->solarPanelStatePtr))) {  // Solar panel is not deployed
        *(powerData->batteryLevelPtr) = *(powerData->batteryLevelPtr) - (3 * (*(powerData->powerConsumptionPtr)));
    } else {  // Solar panel is deployed
        *(powerData->batteryLevelPtr) = *(powerData->batteryLevelPtr) + *(powerData->powerGenerationPtr) - *(powerData->powerConsumptionPtr);
    }

    // cannot overcharge batteries (though you can try!)
    if (*(powerData->batteryLevelPtr) > 100) {
        *(powerData->batteryLevelPtr) = 100;
    }

    // for debugging
    print_format("SUBSYSTEM POWER\n");
    print_format("\tCurrent power consumption: %d \n\tCurrent power generation: %d \n\tBattery level: %d \n\tSolar panels: %d\n",
           *(powerData ->powerConsumptionPtr), *(powerData->powerGenerationPtr), *(powerData->batteryLevelPtr), *(powerData->solarPanelStatePtr));

    // call counting to control incremental behavior
    powerData->callCounter++;
}
