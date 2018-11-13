#include <stdio.h>
#include <assert.h>
#include "globals.h"

int main(void)
{
    initialize();

    // do not crash hopefully
	return testSatelliteComsSubsystem();
}

int testSatelliteComsSubsystem() {
    // ensure it works at putting off a new random number
    satelliteComsFunction(&comsData);
    satelliteComsFunction(&comsData);
    satelliteComsFunction(&comsData);
    satelliteComsFunction(&comsData);
    satelliteComsFunction(&comsData);

    assert(*(comsData.thrustCommandPtr) == 40439);
    assert(!*(comsData.batteryLowPtr));
    assert(!*(comsData.fuelLowPtr));

    // now both things should be alarmed
    *(comsData.batteryLevelPtr) = 9;
    *(comsData.fuelLevelPtr) = 9;
    satelliteComsFunction(&comsData);

    assert(*(comsData.batteryLowPtr));
    assert(*(comsData.fuelLowPtr));

    // now alarms should be gone
    *(comsData.batteryLevelPtr) = 90;
    *(comsData.fuelLevelPtr) = 90;
    satelliteComsFunction(&comsData);

    assert(!*(comsData.batteryLowPtr));
    assert(!*(comsData.fuelLowPtr));

    return 0;
}
