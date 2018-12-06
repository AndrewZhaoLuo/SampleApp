#ifndef VEHICLE_COMMS_SUBSYSTEM_H
#define VEHICLE_COMMS_SUBSYSTEM_H

#define MIN_DISTANCE_DOCK 102

// for TRUE/FALSE
#include "bool.h"

typedef struct vehicleCommsDataStruct {
    char* vehicleCommandPtr;
    char* vehicleResponsePtr;
    unsigned short* transportDistPtr;
    Bool* schedVehicleCommsPtr;
    int* last_freq;
} vehicleCommsData;

void vehicleCommsFunction(void* data);

#endif // VEHICLE_COMMS_SUBSYSTEM_H
