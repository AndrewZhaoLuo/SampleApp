#ifndef THRUSTERSUBSYSTEM_H
#define THRUSTERSUBSYSTEM_H

typedef struct thrusterSubsystemDataStruct {
    unsigned int* thrustCommandPtr;
    unsigned short* fuelLevelPtr;
} thrusterSubsystemData;

void thrusterSubsystemFunction(void* data);

#endif
