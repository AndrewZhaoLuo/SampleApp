#ifndef PIRATE_DETECTION_SUBSYSTEM_H
#define PIRATE_DETECTION_SUBSYSTEM_H

#include "bool.h"

// map of frequency -> distance is simple
#define DETECTION_MAX_FREQUENCY 1000
#define DETECTION_MIN_FREQUENCY 100
#define DETECTION_TRANSLATION_OFFSET 100
#define DETECTION_MAX_DISTANCE 900
#define DETECTION_MIN_DISTANCE 0
#define DETECTION_THRESHOLD 100
#define DETECTION_CUTOFF 512
#define DETECTION_ENOUGH_SAMPLES 10
#define DETECTION_CONVERT_TO_MILLIS 1000.0

typedef struct pirateDetectionStruct {
    int* pirateDistance;
    Bool* pirateDetected;
} pirateDetectionData;

void pirateDetectionFunction(void* data);

#endif
