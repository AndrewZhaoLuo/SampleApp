#ifndef PIRATE_DETECTION_SUBSYSTEM_H
#define PIRATE_DETECTION_SUBSYSTEM_H

#include "bool.h"

// map of frequency -> distance is simple
#define MAX_FREQUENCY 1000
#define MIN_FREQUENCY 100
#define TRANSLATION_OFFSET 100
#define MAX_DISTANCE 900
#define MIN_DISTANCE 0
#define DETECTION_THRESHOLD 100
#define CUTOFF 512
#define ENOUGH_SAMPLES 10
#define CONVERT_TO_MILLIS 1000.0

typedef struct pirateDetectionStruct {
    int* pirateDistance;
    Bool* pirateDetected;
} pirateDetectionData;

void pirateDetectionFunction(void* data);

#endif
