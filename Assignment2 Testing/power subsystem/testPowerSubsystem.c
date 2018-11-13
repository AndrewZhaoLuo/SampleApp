#include "globals.h"
#include "powerSubsystem.h"
#include <assert.h>

void testPowerSubsystem();

int main(int argc, char** argv) {
    testPowerSubsystem();
    return 1;
}

void testPowerSubsystem(){
    initialize();

    powerSubsystemFunction(&powerData);
    assert(*(powerData.powerConsumptionPtr) == 2);
    assert(*(powerData.powerGenerationPtr) == 0);
    assert(*(powerData.batteryLevelPtr) == 94);
    assert(*(powerData.solarPanelStatePtr) == 0);

    powerSubsystemFunction(&powerData);
    assert(*(powerData.powerConsumptionPtr) == 1);
    assert(*(powerData.powerGenerationPtr) == 0);
    assert(*(powerData.batteryLevelPtr) == 91);
    assert(*(powerData.solarPanelStatePtr) == 0);

    powerSubsystemFunction(&powerData);
    assert(*(powerData.powerConsumptionPtr) == 3);
    assert(*(powerData.powerGenerationPtr) == 0);
    assert(*(powerData.batteryLevelPtr) == 82);
    assert(*(powerData.solarPanelStatePtr) == 0);

    powerSubsystemFunction(&powerData);
    assert(*(powerData.powerConsumptionPtr) == 2);
    assert(*(powerData.powerGenerationPtr) == 0);
    assert(*(powerData.batteryLevelPtr) == 76);
    assert(*(powerData.solarPanelStatePtr) == 0);

    powerSubsystemFunction(&powerData);
    assert(*(powerData.powerConsumptionPtr) == 4);
    assert(*(powerData.powerGenerationPtr) == 0);
    assert(*(powerData.batteryLevelPtr) == 64);
    assert(*(powerData.solarPanelStatePtr) == 0);

    powerSubsystemFunction(&powerData);
    assert(*(powerData.powerConsumptionPtr) == 3);
    assert(*(powerData.powerGenerationPtr) == 0);
    assert(*(powerData.batteryLevelPtr) == 55);
    assert(*(powerData.solarPanelStatePtr) == 0);

    powerSubsystemFunction(&powerData);
    assert(*(powerData.powerConsumptionPtr) == 5);
    assert(*(powerData.powerGenerationPtr) == 0);
    assert(*(powerData.batteryLevelPtr) == 50);
    assert(*(powerData.solarPanelStatePtr) == 1);

    powerSubsystemFunction(&powerData);
    assert(*(powerData.powerConsumptionPtr) == 4);
    assert(*(powerData.powerGenerationPtr) == 0);
    assert(*(powerData.batteryLevelPtr) == 46);
    assert(*(powerData.solarPanelStatePtr) == 1);

    powerSubsystemFunction(&powerData);
    assert(*(powerData.powerConsumptionPtr) == 6);
    assert(*(powerData.powerGenerationPtr) == 2);
    assert(*(powerData.batteryLevelPtr) == 42);
    assert(*(powerData.solarPanelStatePtr) == 1);

    ////////////////////////////////////////
    powerSubsystemFunction(&powerData);
    assert(*(powerData.powerConsumptionPtr) == 5);
    assert(*(powerData.powerGenerationPtr) == 3);
    assert(*(powerData.batteryLevelPtr) == 40);
    assert(*(powerData.solarPanelStatePtr) == 1);

    powerSubsystemFunction(&powerData);
    assert(*(powerData.powerConsumptionPtr) == 7);
    assert(*(powerData.powerGenerationPtr) == 5);
    assert(*(powerData.batteryLevelPtr) == 38);
    assert(*(powerData.solarPanelStatePtr) == 1);

    powerSubsystemFunction(&powerData);
    assert(*(powerData.powerConsumptionPtr) == 6);
    assert(*(powerData.powerGenerationPtr) == 6);
    assert(*(powerData.batteryLevelPtr) == 38);
    assert(*(powerData.solarPanelStatePtr) == 1);

    powerSubsystemFunction(&powerData);
    assert(*(powerData.powerConsumptionPtr) == 8);
    assert(*(powerData.powerGenerationPtr) == 8);
    assert(*(powerData.batteryLevelPtr) == 38);
    assert(*(powerData.solarPanelStatePtr) == 1);

    powerSubsystemFunction(&powerData);
    assert(*(powerData.powerConsumptionPtr) == 7);
    assert(*(powerData.powerGenerationPtr) == 9);
    assert(*(powerData.batteryLevelPtr) == 40);
    assert(*(powerData.solarPanelStatePtr) == 1);

    powerSubsystemFunction(&powerData);
    assert(*(powerData.powerConsumptionPtr) == 9);
    assert(*(powerData.powerGenerationPtr) == 11);
    assert(*(powerData.batteryLevelPtr) == 42);
    assert(*(powerData.solarPanelStatePtr) == 1);

    powerSubsystemFunction(&powerData);
    assert(*(powerData.powerConsumptionPtr) == 8);
    assert(*(powerData.powerGenerationPtr) == 12);
    assert(*(powerData.batteryLevelPtr) == 46);
    assert(*(powerData.solarPanelStatePtr) == 1);

    powerSubsystemFunction(&powerData);
    assert(*(powerData.powerConsumptionPtr) == 10);
    assert(*(powerData.powerGenerationPtr) == 14);
    assert(*(powerData.batteryLevelPtr) == 50);
    assert(*(powerData.solarPanelStatePtr) == 1);

    powerSubsystemFunction(&powerData);
    assert(*(powerData.powerConsumptionPtr) == 9);
    assert(*(powerData.powerGenerationPtr) == 14);
    assert(*(powerData.batteryLevelPtr) == 55);
    assert(*(powerData.solarPanelStatePtr) == 1);

    powerSubsystemFunction(&powerData);
    assert(*(powerData.powerConsumptionPtr) == 11);
    assert(*(powerData.powerGenerationPtr) == 16);
    assert(*(powerData.batteryLevelPtr) == 60);
    assert(*(powerData.solarPanelStatePtr) == 1);

    powerSubsystemFunction(&powerData);
    assert(*(powerData.powerConsumptionPtr) == 12);
    assert(*(powerData.powerGenerationPtr) == 16);
    assert(*(powerData.batteryLevelPtr) == 64);
    assert(*(powerData.solarPanelStatePtr) == 1);

    powerSubsystemFunction(&powerData);
    assert(*(powerData.powerConsumptionPtr) == 10);
    assert(*(powerData.powerGenerationPtr) == 18);
    assert(*(powerData.batteryLevelPtr) == 72);
    assert(*(powerData.solarPanelStatePtr) == 1);

    powerSubsystemFunction(&powerData);
    assert(*(powerData.powerConsumptionPtr) == 11);
    assert(*(powerData.powerGenerationPtr) == 18);
    assert(*(powerData.batteryLevelPtr) == 79);
    assert(*(powerData.solarPanelStatePtr) == 1);

    powerSubsystemFunction(&powerData);
    assert(*(powerData.powerConsumptionPtr) == 9);
    assert(*(powerData.powerGenerationPtr) == 20);
    assert(*(powerData.batteryLevelPtr) == 90);
    assert(*(powerData.solarPanelStatePtr) == 1);

    powerSubsystemFunction(&powerData);
    assert(*(powerData.powerConsumptionPtr) == 10);
    assert(*(powerData.powerGenerationPtr) == 20);
    assert(*(powerData.batteryLevelPtr) == 100);
    assert(*(powerData.solarPanelStatePtr) == 1);

    powerSubsystemFunction(&powerData);
    assert(*(powerData.powerConsumptionPtr) == 8);
    assert(*(powerData.powerGenerationPtr) == 0);
    assert(*(powerData.batteryLevelPtr) == 76);
    assert(*(powerData.solarPanelStatePtr) == 0);
}


