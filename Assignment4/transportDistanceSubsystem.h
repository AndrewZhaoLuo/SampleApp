#ifndef TRANSPORT_DISTANCE_SUBSYSTEM_H
#define TRANSPORT_DISTANCE_SUBSYSTEM_H

typedef struct transportDistanceDataStruct {
    unsigned int* timeIntervalBuffer;
    unsigned int* meterDistanceBuffer;
    unsigned short* transportDistPtr;
} transportDistanceData;

void transportDistanceFunction(void* data);

#endif // SOLARPANELCONTROLSUBSYSTEM_H_INCLUDED
