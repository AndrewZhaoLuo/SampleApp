#include "pirateDetectionSubsystem.h"
#include "globals.h"
#include "clock.h"
#include <Arduino.h>
#include "print_format.h"

void pirateDetectionFunction(void* data) {
    // Cast to correct pointer
    pirateDetectionData* detectionData = (pirateDetectionData*) data;

    if(transportDistanceFreqConnectedFlag) { // use same central processing unit
      int curr = 0;
      int prev = 0;
      int count = 0;

      unsigned long long startTime = getTimeMillis();
      for(int i = 0; i < 10000; i++){
        prev = curr;
        curr = analogRead(PIRATE_DETECTION_PIN);
        if(curr < CUTOFF && prev >= CUTOFF){
          count++;
        }
        if(count == ENOUGH_SAMPLES){
          break;
        }
      }
      unsigned long long endTime = getTimeMillis();

      // Calculate time elapsed in millis
      unsigned long duration = ((endTime-startTime));

      // Calculate time interval between peaks and push to interval buffer (millis)
      double timeInterval = duration/((double) count);
      double durationMS = ((double) duration) / CONVERT_TO_MILLIS;

      double frequency = ((double) count)/ durationMS;
      int meters = frequency - TRANSLATION_OFFSET;
      if (meters > MAX_DISTANCE) {
        meters = MAX_DISTANCE;
      } else if (meters < MIN_DISTANCE) {
          meters = MIN_DISTANCE;
      }
      *(detectionData -> pirateDistance) = meters;

      if (meters < DETECTION_THRESHOLD) {
        *(detectionData -> pirateDetected) = TRUE;
      } else {
        *(detectionData -> pirateDetected) = FALSE;
      }
    }
}
