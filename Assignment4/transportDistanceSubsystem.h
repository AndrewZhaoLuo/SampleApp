#ifndef TRANSPORT_DISTANCE_SUBSYSTEM_H
#define TRANSPORT_DISTANCE_SUBSYSTEM_H

#define CUTOFF 512

typedef struct transportDistanceDataStruct {
    unsigned int** timeIntervalBuffer;
    unsigned int** meterDistanceBuffer;
    unsigned short* transportDistPtr;
} transportDistanceData;

void transportDistanceFunction(void* data);

#endif
