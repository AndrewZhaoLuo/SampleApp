#ifndef VEHICLE_COMMS_SUBSYSTEM_H
#define VEHICLE_COMMS_SUBSYSTEM_H

#define MIN_DISTANCE_DOCK 102

typedef struct vehicleCommsDataStruct {
    char* vehicleCommandPtr;
    char* vehicleResponsePtr;
    unsigned short* transportDistPtr;
} vehicleCommsData;

void vehicleCommsFunction(void* data);

#endif // VEHICLE_COMMS_SUBSYSTEM_H
