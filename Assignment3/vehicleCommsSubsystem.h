#ifndef VEHICLE_COMMS_SUBSYSTEM_H
#define VEHICLE_COMMS_SUBSYSTEM_H

typedef struct vehicleCommsDataStruct {
    char* vehicleCommandPtr;
    char* vehicleResponsePtr;
} vehicleCommsData;

void vehicleCommsFunction(void* data);

#endif // VEHICLE_COMMS_SUBSYSTEM_H
