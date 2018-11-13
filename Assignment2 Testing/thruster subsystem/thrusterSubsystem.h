#ifndef THRUSTERSUBSYSTEM_H
#define THRUSTERSUBSYSTEM_H

typedef struct thrusterSubsystemDataStruct {
    unsigned int* thrustCommandPtr;
    unsigned short* fuelLevelPtr;
} thrusterSubsystemData;

// Create new struct of local variables
struct localVars {
    int left;
    int right;
    int up;
    int down;
    int magnitude;
    int duration;
};

struct localVars thrusterSubsystemFunction(void* data);

#endif
