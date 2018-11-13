#include "globals.h"
#include "powerSubsystem.h"

void powerSubsystemFunction(void* data){
    // Cast to correct pointer
    powerSubsystemData* powerData = (powerSubsystemData*) data;

    // Power Consumption
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

    // Power Generation
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

    // Battery Level
    if(!(*(powerData->solarPanelStatePtr))) {  // Solar panel is not deployed
        *(powerData->batteryLevelPtr) = *(powerData->batteryLevelPtr) - (3 * (*(powerData->powerConsumptionPtr)));
    } else {  // Solar panel is deployed
        *(powerData->batteryLevelPtr) = *(powerData->batteryLevelPtr) + *(powerData->powerGenerationPtr) - *(powerData->powerConsumptionPtr);
    }

    // cannot overcharge batteries
    if (*(powerData->batteryLevelPtr) > 100) {
        *(powerData->batteryLevelPtr) = 100;
    }
    printf("SUBSYSTEM POWER\n");
    printf("\tCurrent power consumption: %d \n\tCurrent power generation: %d \n\tBattery level: %d \n\tSolar panels: %d\n",
           *(powerData ->powerConsumptionPtr), *(powerData->powerGenerationPtr), *(powerData->batteryLevelPtr), *(powerData->solarPanelStatePtr));
    powerData->callCounter++;
}
