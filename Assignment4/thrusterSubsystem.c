#include "globals.h"
#include "thrusterSubsystem.h"
#include "rand1.h"
#include "print_format.h"

#define ONE_BIT 1
#define FOUR_BITS 0b1111
#define EIGHT_BITS 0b11111111
#define SHIFT_ONE 1
#define SHIFT_TWO 2
#define SHIFT_THREE 3
#define SHIFT_FOUR 4
#define SHIFT_EIGHT 8
#define FUEL_SCALAR (100.0L/11664000.0L)
#define SCALE_FOR_PRINT 1000000
#define NUM_THRUSTERS 4

void thrusterSubsystemFunction(void* data) {
    // for fuel usage < 1, keep track of when we have used an integer number of fuel
    static double store = 0.0;

    // Cast to correct pointer
    thrusterSubsystemData* thrusterData = (thrusterSubsystemData*) data;
    int cmd = *(thrusterData->thrustCommandPtr);

    // see specification for how bits are associated
    int left = cmd & ONE_BIT;
    int right = (cmd>>SHIFT_ONE) & ONE_BIT;
    int up = (cmd>>SHIFT_TWO) & ONE_BIT;
    int down = (cmd>>SHIFT_THREE) & ONE_BIT;

    int magnitude = (cmd>>SHIFT_FOUR) & FOUR_BITS;
    int duration = (cmd>>SHIFT_EIGHT) & EIGHT_BITS;

    int numberOfEnginesOn = left + right + up + down;

    // see report/specs for calculation on this level
    double fuelPerSec = FUEL_SCALAR * magnitude * numberOfEnginesOn / NUM_THRUSTERS;
    double fuelUsed = duration * fuelPerSec;
    store += fuelUsed;

    // see if we have used an integer amount of fuel so far
    int roundedFuelUsed = (int) store;
    store -= roundedFuelUsed;
    *(thrusterData->fuelLevelPtr) = *(thrusterData->fuelLevelPtr) - roundedFuelUsed;


    long storePrint = store * SCALE_FOR_PRINT;
    long fuelUsedPrint = fuelUsed * SCALE_FOR_PRINT;
    /*print_format("SUBSYSTEM THRUSTER\n");
    print_format("\tLeft %d, Right %d, Up %d, Down %d \n\tMagnitude %d, Duration %d\n\tFuel Used Actual (millionths) %ld, Store (millionths) %ld, Rounded Used %d\n\tCommand 0x%X\n",
           left, right, up, down, magnitude, duration, fuelUsedPrint, storePrint, roundedFuelUsed, cmd);*/
}
