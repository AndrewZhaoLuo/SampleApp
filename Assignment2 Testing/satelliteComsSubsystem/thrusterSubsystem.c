#include "globals.h"
#include "thrusterSubsystem.h"

#include "rand1.h"

void thrusterSubsystemFunction(void* data) {
    static double store = 0.0; // for fuel usage < 1

    // Cast to correct pointer
    thrusterSubsystemData* thrusterData = (thrusterSubsystemData*) data;
    int cmd = *(thrusterData->thrustCommandPtr);

    int left = cmd & 1;
    int right = (cmd>>1) & 1;
    int up = (cmd>>2) & 1;
    int down = (cmd>>3) & 1;

    int magnitude = (cmd>>4) & 0b1111;
    int duration = (cmd>>8) & 0b11111111;

    double fuelPerSec = (100.0L/11664000.0L) * magnitude;
    double fuelUsed = duration * fuelPerSec;
    store += fuelUsed;

    int roundedFuelUsed = (int) store;
    store -= roundedFuelUsed;
    *(thrusterData->fuelLevelPtr) = *(thrusterData->fuelLevelPtr) - roundedFuelUsed;

    printf("SUBSYSTEM THRUSTER\n");
    printf("\tLeft %d, Right %d, Up %d, Down %d \n\tMagnitude %d, Duration %d\n\tFuel Used Actual %f, Store %f, Rounded Used %d\n\tCommand 0x%X\n",
           left, right, up, down, magnitude, duration, fuelUsed, store, roundedFuelUsed, cmd);
}
