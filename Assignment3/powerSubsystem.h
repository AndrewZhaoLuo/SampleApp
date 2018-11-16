#ifndef POWERSUBSYSTEM_H
#define POWERSUBSYSTEM_H

/*
Why deploy at 60? In the worst case we are at 61 and 12 consumption

Battery:     61 25 17  9  5   1 --- phew barely lived!
Consumption: 12 10 11  9  10  8
Generation:   0  2  3  5  6   8
              ^
              |____where we start solar panels
              56 - 12
              20
*/

// the battery level thresholds to deploy and retract the solar panels
#define BATTERY_LEVEL_DEPLOY 61
#define BATTERY_LEVEL_RETRACT 95
#define DISPLAY_THRESHOLD 0.0006 // 600 microseconds
#define ADC_BIT_RESOLUTION 0.0049 // 4.9mV per bit
#define VOLTAGE_SCALAR 36.0 // Converts 0-5V to 0-36V as per spec
#define ADC_PIN 58 // Hardware pin of ADC

// the power consumption thresholds to begin decreasing/increasing use
#define CONSUMPTION_LIMIT 10
#define CONSUMPTION_FLOOR 5

// HIGH and LOW battery levels which effect efficiency of solar panel
// power generation
#define HIGH_BATTERY_LEVEL 95
#define LOW_BATTERY_LEVEL 50

#include "bool.h"

typedef struct powerSubsystemDataStruct {
    Bool* solarPanelStatePtr;
    unsigned short* batteryLevelPtr;
    unsigned short* powerConsumptionPtr;
    unsigned short* powerGenerationPtr;
    int callCounter;
    Bool increaseConsumption;

    Bool* solarPanelDeploy;
    Bool* solarPanelRetract;
    int* motorDriveSpeed;
    int* batteryBuff; // 16-Sample buffer
    int* batteryTempBuff;

} powerSubsystemData;

void powerSubsystemFunction(void* data);

#endif
