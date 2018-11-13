#include "globals.h"

void initPowerData() {
    powerData.solarPanelStatePtr = &solarPanelState;
    powerData.batteryLevelPtr = &batteryLevel;
    powerData.powerConsumptionPtr = &powerConsumption;
    powerData.powerGenerationPtr = &powerGeneration;
    powerData.callCounter = 0;
    powerData.increaseConsumption = TRUE;
}

void initThrusterData() {
    thrusterData.thrustCommandPtr = &thrustCommand;
    thrusterData.fuelLevelPtr = &fuelLevel;
}

void initComsData() {
    comsData.thrustCommandPtr = &thrustCommand;
    comsData.batteryLevelPtr = &batteryLevel;
    comsData.fuelLevelPtr = &fuelLevel;
    comsData.powerConsumptionPtr = &powerConsumption;
    comsData.powerGenerationPtr = &powerGeneration;
    comsData.solarPanelStatePtr = &solarPanelState;
    comsData.fuelLowPtr = &fuelLow;
    comsData.batteryLowPtr = &batteryLow;
}

void initDisplayData() {
    displayData.thrustCommandPtr = &thrustCommand;
    displayData.batteryLevelPtr = &batteryLevel;
    displayData.fuelLevelPtr = &fuelLevel;
    displayData.powerConsumptionPtr = &fuelLevel;
    displayData.powerGenerationPtr = &powerGeneration;
    displayData.solarPanelStatePtr = &solarPanelState;
    displayData.fuelLowPtr = &fuelLow;
    //displayData.batteryLevelPtr = &batteryLow;
}

void initWarningData() {
    warningData.batteryLevelPtr = &batteryLevel;
    warningData.batteryLowPtr = &batteryLow;
    warningData.fuelLevelPtr = &fuelLevel;
    warningData.fuelLowPtr = &fuelLow;
}

void initialize(){
    // Initialize globals
    thrustCommand = 0;
    batteryLevel = 100;
    fuelLevel = 100;
    powerConsumption = 0;
    powerGeneration = 0;
    solarPanelState = FALSE;
    fuelLow = FALSE;
    batteryLow = FALSE;

    // Initialize data structs
    initPowerData();
}

