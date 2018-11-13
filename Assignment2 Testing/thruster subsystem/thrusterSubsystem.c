#include "globals.h"
#include "thrusterSubsystem.h"


struct localVars thrusterSubsystemFunction(void* data) {
    static double store = 0.0; // for fuel usage < 1


    // Cast to correct pointer
    thrusterSubsystemData* thrusterData = (thrusterSubsystemData*) data;
    int cmd = *(thrusterData->thrustCommandPtr);

    struct localVars localVariables;

    localVariables.left = cmd & 1;
    localVariables.right = (cmd>>1) & 1;
    localVariables.up = (cmd>>2) & 1;
    localVariables.down = (cmd>>3) & 1;

    localVariables.magnitude = (cmd>>4) & 0b1111;
    localVariables.duration = (cmd>>8) & 0b11111111;

    double fuelPerSec = (100.0L/11664000.0L) * localVariables.magnitude;
    double fuelUsed = localVariables.duration * fuelPerSec;
    store += fuelUsed;

    int roundedFuelUsed = (int) store;
    store -= roundedFuelUsed;
    *(thrusterData->fuelLevelPtr) = *(thrusterData->fuelLevelPtr) - roundedFuelUsed;

    return localVariables;

    //printf("SUBSYSTEM THRUSTER\n");
    //printf("\tLeft %d, Right %d, Up %d, Down %d \n\tMagnitude %d, Duration %d\n\tFuel Used Actual %f, Store %f, Rounded Used %d\n\tCommand 0x%X\n",
           //left, right, up, down, magnitude, duration, fuelUsed, store, roundedFuelUsed, cmd);
}
