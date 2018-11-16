#include "globals.h"
#include "powerSubsystem.h"
#include "print_format.h"
#include "clock.h"
#include <Arduino.h>

int readBatteryLevel();

void updateBatteryLevelDisplay(double batteryLevel, powerSubsystemData* powerData);

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
            // set motorspeed
            *powerData -> solarPanelDeploy = FALSE;
            *powerData -> solarPanelRetract = TRUE;
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
            *powerData -> solarPanelDeploy = TRUE;
            *powerData -> solarPanelRetract = FALSE;
        }
    }

    // Battery Management System
	int batteryLevel = readBatteryLevel();
	long long currentTime = getTimeMillis();
	Bool isStable = batteryConnectedFlag && (currentTime - batteryConnectionTimestamp > DISPLAY_THRESHOLD);

	if (isStable) {
		updateBatteryLevelDisplay(batteryLevel, powerData);
	} else if (batteryConnectedFlag) {
		if (batteryConnectionTimestamp == 0) {
			batteryConnectionTimestamp = getTimeMillis();
		}
	} else {
		batteryConnectionTimestamp = 0; // SET TO DISCONNECTED
    updateBatteryLevelDisplay(0, powerData);
	}

  // cannot overcharge batteries (though you can try!)
  if (*(powerData->batteryLevelPtr) > 100) {
      *(powerData->batteryLevelPtr) = 100;
  }

  // for debugging
  /*print_format("SUBSYSTEM POWER\n");
  print_format("\tCurrent power consumption: %d \n\tCurrent power generation: %d \n\tBattery level: %d \n\tSolar panels: %d\n",
         *(powerData ->powerConsumptionPtr), *(powerData->powerGenerationPtr), *(powerData->batteryLevelPtr), *(powerData->solarPanelStatePtr));*/

  // call counting to control incremental behavior
  powerData->callCounter++;
}

// Reads battery level in bits from 0-1023 then converts to range of 0 - 36V then converts to 0-100 to represent % of max charge
int readBatteryLevel() {
	int batteryADC = analogRead(BATTERY_IN_PIN);
	int batteryLevel = ((batteryADC / 1023.0) * VOLTAGE_SCALAR);
	// Insert Value into buffer
  //pushBack(&powerBuf, batteryLevel);
	return batteryLevel;
}

void updateBatteryLevelDisplay(double batteryLevel, powerSubsystemData* powerData) {
	// Set global to value
  int newBatteryLevel = ((batteryLevel/VOLTAGE_SCALAR) * 100) + (*(powerData->powerGenerationPtr)) - (*(powerData->powerConsumptionPtr));
  if (newBatteryLevel <= 0 || !batteryConnectedFlag){
    newBatteryLevel = 0;
  }
  *(powerData -> batteryLevelPtr) = (unsigned short) newBatteryLevel;
}
