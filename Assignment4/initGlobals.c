#include <stdarg.h>
#include <Arduino.h>
#include "globals.h"
#include "clock.h"

void batteryConnectionInterrupt() {
  int val = digitalRead(53);
  if (val == HIGH) {
    batteryConnectedFlag = TRUE;
    batteryConnectionTimestamp = getTimeMillis();
  } else {
    batteryConnectedFlag = FALSE;
  }
}

void solarPanelConnectionInterrupt() {
  int val = digitalRead(51);
  if (val == HIGH) {
    solarPanelConnectedFlag = TRUE;
  } else {
    solarPanelConnectedFlag = FALSE;
  }
}

void solarPanelSafetyInterrupt() {
  int val = digitalRead(49);
  if (val == HIGH) {
    solarPanelMoveFlag = FALSE;
  } else {
    solarPanelMoveFlag = TRUE;
  }
}

void transportDistFreqInterrupt(){
  int val = digitalRead(47);
  if (val == HIGH) {
    transportDistanceFreqConnectedFlag = TRUE;
  } else {
    transportDistanceFreqConnectedFlag = FALSE;
  }
}

void initPowerData() {
    powerData.solarPanelStatePtr = &solarPanelState;
    powerData.batteryLevelPtr = &batteryLevel;
    powerData.powerConsumptionPtr = &powerConsumption;
    powerData.powerGenerationPtr = &powerGeneration;
    powerData.callCounter = 0;
    powerData.increaseConsumption = TRUE;

    powerData.motorDriveSpeed = &motorSpeed;
    powerData.solarPanelRetract = &solarPanelRetract;
    powerData.solarPanelDeploy = &solarPanelDeploy;
    // Buffers
    powerData.batteryBuff= &batteryBuf;
    powerData.batteryTempBuff = &batteryTempBuf;
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
    displayData.powerConsumptionPtr = &powerConsumption;
    displayData.powerGenerationPtr = &powerGeneration;
    displayData.solarPanelStatePtr = &solarPanelState;
    displayData.fuelLowPtr = &fuelLow;
    displayData.batteryLowPtr = &batteryLow;
    displayData.batteryTempPtr = &batteryTemp;
    displayData.transportDistPtr = &transportDist;
}

void initWarningData() {
    warningData.batteryLevelPtr = &batteryLevel;
    warningData.batteryLowPtr = &batteryLow;
    warningData.fuelLevelPtr = &fuelLevel;
    warningData.fuelLowPtr = &fuelLow;
}


void initVehicleData() {
  vehicleData.vehicleCommandPtr = &vehicleCommand;
  vehicleData.vehicleResponsePtr = &vehicleResponse;
  vehicleData.transportDistPtr = &transportDist;
}

void initPanelData() {
    panelData.solarPanelState = &solarPanelState;
    panelData.solarPanelRetract = &solarPanelRetract;
    panelData.solarPanelDeploy = &solarPanelDeploy;
    panelData.solarPanelDriveDec = &solarPanelDriveDec;
    panelData.solarPanelDriveInc = &solarPanelDriveInc;
    panelData.motorDriveSpeed = &motorSpeed;
}

void initKeyData() {
    keyData.solarPanelDriveDec = &solarPanelDriveDec;
    keyData.solarPanelDriveInc = &solarPanelDriveInc;
}

void initTransportData(){
  transportData.timeIntervalBuffer = &timeIntervalBuf;
  transportData.meterDistanceBuffer = &meterDistanceBuf;
  transportData.transportDistPtr = &transportDist;
}

void initialize(){
    // Initialize globals
    thrustCommand = 0;
    motorSpeed = 25;
    batteryLevel = 100;
    fuelLevel = 100;
    powerConsumption = 0;
    powerGeneration = 0;
    solarPanelState = FALSE;
    fuelLow = FALSE;
    batteryLow = FALSE;
    solarPanelDeploy = FALSE;
    solarPanelRetract = FALSE;
    vehicleCommand = '\0';
    vehicleResponse = '\0';
    solarPanelDriveInc = FALSE;
    solarPanelDriveDec = FALSE;
    //batteryLevelPtr = powerBuf;
    batteryTemp = 33;
    transportDist = 1000;

    // Initalize data buffers
    initBuffer(batteryBuf, 16 + BUFFER_METADATA_SIZE); //16-sample battery buffer
    initBuffer(batteryTempBuf, 16 + BUFFER_METADATA_SIZE);
    initBuffer(powerBuf, 16 + BUFFER_METADATA_SIZE);
    initBuffer(timeIntervalBuf, 16 + BUFFER_METADATA_SIZE);
    initBuffer(meterDistanceBuf, 8 + BUFFER_METADATA_SIZE);

    // interrupt flags
    batteryConnectedFlag = FALSE;
    batteryConnectionTimestamp = 0;
    solarPanelConnectedFlag = FALSE;
    solarPanelMoveFlag = TRUE;
    transportDistanceFreqConnectedFlag = FALSE;

    // Initialize data structs
    initPowerData();
    initThrusterData();
    initComsData();
    initDisplayData();
    initWarningData();
    initVehicleData();
    initPanelData();
    initKeyData();
    initTransportData();

    // initialize the various data structures for the kernel
    initScheduler(&scheduler);

    initTCB(&tcbs[COMS_DATA_TCB], (void*)&comsData, satelliteComsFunction, PRIORITY_LOW);
    initTCB(&tcbs[THRUSTER_DATA_TCB], (void*)&thrusterData, thrusterSubsystemFunction, PRIORITY_LOW);
    initTCB(&tcbs[POWER_DATA_TCB], (void*)&powerData, powerSubsystemFunction, PRIORITY_LOW);
    initTCB(&tcbs[WARNING_DATA_TCB], (void*)&warningData, warningAlarmFunction, PRIORITY_HIGH);
    initTCB(&tcbs[DISPLAY_DATA_TCB], (void*)&displayData, consoleDisplayFunction, PRIORITY_LOW);
    initTCB(&tcbs[VEHICLE_DATA_TCB], (void*)&vehicleData, vehicleCommsFunction, PRIORITY_HIGH);
    initTCB(&tcbs[PANEL_DATA_TCB], (void*)&panelData, solarPanelControlFunction, PRIORITY_HIGH);
    initTCB(&tcbs[KEYPAD_DATA_TCB], (void*)&keyData, keypadFunction, PRIORITY_HIGH);
    initTCB(&tcbs[DISTANCE_TRANSPORT_DATA_TCB], (void*)&transportData, transportDistanceFunction, PRIORITY_LOW);

    initTaskQueue(&queue);
}
