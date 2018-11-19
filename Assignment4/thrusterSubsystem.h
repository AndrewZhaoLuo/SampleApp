#ifndef THRUSTERSUBSYSTEM_H
#define THRUSTERSUBSYSTEM_H

#define DEFAULT_STORE_VALUE 0.0

typedef struct thrusterSubsystemDataStruct {
    unsigned int* thrustCommandPtr;
    unsigned short* fuelLevelPtr;
} thrusterSubsystemData;

void thrusterSubsystemFunction(void* data);

#endif
