#include "globals.h"
#include "thrusterSubsystem.h"
#include "rand1.h"
#include "print_format.h"

void thrusterSubsystemFunction(void* data) {
    // for fuel usage < 1, keep track of when we have used an integer number of fuel
    static double store = 0.0;

    // Cast to correct pointer
    thrusterSubsystemData* thrusterData = (thrusterSubsystemData*) data;
    int cmd = *(thrusterData->thrustCommandPtr);

    // see specification for how bits are associated
    int left = cmd & 1;
    int right = (cmd>>1) & 1;
    int up = (cmd>>2) & 1;
    int down = (cmd>>3) & 1;

    int magnitude = (cmd>>4) & 0b1111;
    int duration = (cmd>>8) & 0b11111111;

    int numberOfEnginesOn = left + right + up + down;

    // see report/specs for calculation on this level
    double fuelPerSec = (100.0L/11664000.0L) * magnitude * numberOfEnginesOn / 4;
    double fuelUsed = duration * fuelPerSec;
    store += fuelUsed;

    // see if we have used an integer amount of fuel so far
    int roundedFuelUsed = (int) store;
    store -= roundedFuelUsed;
    *(thrusterData->fuelLevelPtr) = *(thrusterData->fuelLevelPtr) - roundedFuelUsed;


    long storePrint = store * 1000000;
    long fuelUsedPrint = fuelUsed * 1000000;
    print_format("SUBSYSTEM THRUSTER\n");
    print_format("\tLeft %d, Right %d, Up %d, Down %d \n\tMagnitude %d, Duration %d\n\tFuel Used Actual (millionths) %ld, Store (millionths) %ld, Rounded Used %d\n\tCommand 0x%X\n",
           left, right, up, down, magnitude, duration, fuelUsedPrint, storePrint, roundedFuelUsed, cmd);
}
