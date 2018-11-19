#include "globals.h"
#include "powerSubsystem.h"
#include "print_format.h"
#include "clock.h"
#include <Arduino.h>

int readBatteryLevel();

void updateBatteryLevelDisplay(double batteryLevel, powerSubsystemData* powerData);
int measureAnalogPin(int pin);
double measureBatteryTemp(int pin);
double convertReadingToTemp(int reading);
int convertReadingToMV(int reading);
int isTempSensorReadingSafe(int reading, int buffer[]);

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

    // Battery Management System ********************************************************
	int batteryLevel = readBatteryLevel();
  pushSample(powerData->batteryBuff, batteryLevel);

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

  // Battery Temperature System **************************************************************
  //print_format("A___________________________________________________________");
  int sensorReading1 = convertReadingToMV(measureAnalogPin(BATTERY_TEMPERATURE_SENSOR1_PIN)); //mV
  int sensorReading2 = convertReadingToMV(measureAnalogPin(BATTERY_TEMPERATURE_SENSOR2_PIN)); //mV
  //print_format("sensorReading1: %d, sensorReading2: %d", sensorReading1, sensorReading2);
  int isTempSafe = isTempSensorReadingSafe(sensorReading1, powerData ->batteryTempBuff) && isTempSensorReadingSafe(sensorReading2, powerData ->batteryTempBuff);

  // Trigger alarm until acknowledged
  if (!isTempSafe){
    //print_format("ALARM TRIGGERED ****************************************************");
    // Trigger Alarm
    if (*(powerData->tempAlarmStatePtr) == TEMPERATURE_ALARM_NOT_TRIGGERED) {
      *(powerData->tempAlarmStatePtr) = TEMPERATURE_ALARM_TRIGGERED_UNACKNOWLEDGED;
      *(powerData->tempAlarmTriggeredTimePtr) = getTimeMillis();
    }
  } else if (*(powerData -> tempAlarmStatePtr) == TEMPERATURE_ALARM_TRIGGERED_ACKNOWLEDGED) {
    // Disable alarm if temperature safe and alarm was acknowledged
    *(powerData -> tempAlarmStatePtr) = TEMPERATURE_ALARM_NOT_TRIGGERED;
  }
  pushSample(powerData->batteryTempBuff, sensorReading1);
  pushSample(powerData->batteryTempBuff, sensorReading2);
  printBuffer(powerData->batteryTempBuff, 18);

  unsigned short avgTemp = ((unsigned short)sensorReading1 + (unsigned short)sensorReading2) / 2;
  avgTemp = (unsigned short) convertReadingToTemp(avgTemp);
  // Set global battery temp
  *(powerData->batteryTempPtr) = avgTemp;
  //print_format("isTempSafe?: %d, tempAlarmState: %d, tempAlarmTriggeredTime: %d", isTempSafe,*(powerData->tempAlarmStatePtr), *(powerData->tempAlarmTriggeredTimePtr)); 
  //print_format("B___________________________________________________________");

  // for debugging
  /*print_format("SUBSYSTEM POWER\n");
  print_format("\tCurrent power consumption: %d \n\tCurrent power generation: %d \n\tBattery level: %d \n\tSolar panels: %d\n ",
         *(powerData ->powerConsumptionPtr), *(powerData->powerGenerationPtr), *(powerData->batteryLevelPtr), *(powerData->solarPanelStatePtr));*/

  // call counting to control incremental behavior
  powerData->callCounter++;
}

// Reads battery level in bits from 0-1023 then converts to range of 0 - 36V then converts to 0-100 to represent % of max charge
int readBatteryLevel() {
	int batteryADC = analogRead(BATTERY_IN_PIN);
	int batteryLevel = ((batteryADC / 1023.0) * VOLTAGE_SCALAR);
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

// Measures analog pin value in mV
int measureAnalogPin(int pin) {
  int reading = analogRead(pin);
  return reading;
}

// Measures analog pin for temp sensor data. Scales mV reading to V.
double measureBatteryTemp(int pin) {
  return convertReadingToTemp(measureAnalogPin(pin));
}

double convertReadingToTemp(int reading) {
  return (32.0 * (reading / 100.0)) + 33.0;
}

int convertReadingToMV(int reading) {
  return (int)(reading * 4.9);
}

// Compares temp to last two samples to determine if safe.
// If either of last to samples are 0 (default buffer values), assumes safe.
int isTempSensorReadingSafe(int reading, int buffer[]) {
  double readingTemperature = convertReadingToTemp(reading);
  
  double lastSampleTemp = convertReadingToTemp(getNthPreviousSample(buffer, 0));
  double lastLastSampleTemp = convertReadingToTemp(getNthPreviousSample(buffer, 1));
  //print_format("***Cur sample: %d, last sample: %d, lastlast sample: %d", reading, getNthPreviousSample(buffer, 0), getNthPreviousSample(buffer, 1));
  //print_format("***Cur temp: %d, last temp: %d, lastlast temp: %d", (int)readingTemperature, (int)lastLastSampleTemp, (int)lastSampleTemp);

  /*
  // Haven't taken more than 2 samples, assume safe.
  double bufferDefault = convertReadingToTemp(0.0);
  if (lastSampleTemp == bufferDefault || lastLastSampleTemp == bufferDefault) {
    return 1;
    print_format("Buffer does not have enough values yet\n");
  }
  */

  double largestSampleTemp = lastSampleTemp;
  if (lastLastSampleTemp > largestSampleTemp) {
    largestSampleTemp = lastLastSampleTemp;
  }
 
  int isSafe = (readingTemperature < (largestSampleTemp * 1.20));
  return isSafe;
}
