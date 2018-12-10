#ifndef TRANSPORT_DISTANCE_SUBSYSTEM_H
#define TRANSPORT_DISTANCE_SUBSYSTEM_H

#define CUTOFF 512
#define MIN_METERS 100
#define MAX_METERS 2000
#define MIN_FREQUENCY 100
#define MAX_FREQUENCY 2000
#define LINEAR_RELATIONSHIP 2100
#define CONVERT_TO_MILLIS 1000.0
#define MIN_DIST_GETTING_SIGNAL 1000
#define TEN_PERCENT 0.10
#define ENOUGH_SAMPLES 20
#define MAX_SAMPLES 1600

typedef struct transportDistanceDataStruct {
    unsigned int* timeIntervalBuffer;
    unsigned int* meterDistanceBuffer;
    unsigned short* transportDistPtr;
} transportDistanceData;

void transportDistanceFunction(void* data);

#endif
