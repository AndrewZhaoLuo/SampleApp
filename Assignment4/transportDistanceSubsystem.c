#include "transportDistanceSubsystem.h"
#include "globals.h"
#include "clock.h"
#include <Arduino.h>
#include "print_format.h"

void transportDistanceFunction(void* data) {
    // Cast to correct pointer
    transportDistanceData* transportData = (transportDistanceData*) data;

    // For debugging
    /*print_format("Transport dist connection flag: ");
    if (transportDistanceFreqConnectedFlag) {
      print_format("TRUE\n");
    } else {
      print_format("FALSE\n");
    }*/

    if(transportDistanceFreqConnectedFlag) {
      int curr = 0;
      int prev = 0;
      int count = 0;

      unsigned long long startTime = getTimeMillis();
      for(int i = 0; i < MAX_SAMPLES; i++){
        prev = curr;
        curr = analogRead(DISTANCE_TRANSPORT_PIN);
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

      pushSample(transportData->timeIntervalBuffer, (int) timeInterval);

      double durationMS = ((double) duration)/CONVERT_TO_MILLIS;

      double frequency = ((double) count)/ durationMS;

      // For debugging
      int meters;
      if(frequency > MAX_FREQUENCY) {
        meters = MIN_METERS;
      } else if(frequency < MIN_FREQUENCY){
        meters = MAX_METERS;
      } else {
        meters = LINEAR_RELATIONSHIP - ((int) frequency);
      }

      // If the transport vehicle is within 1 km, we know we register the signal
      if (meters <= MIN_DIST_GETTING_SIGNAL) {

        *(transportData->transportDistPtr) = ((unsigned short) meters);

        // Push this distance to the transport distance buffer if greater than 10% from previous value
        int previousSample = getNthPreviousSample(transportData->meterDistanceBuffer, 0);
        double percentFromLast = ((double)(previousSample - meters))/((double) previousSample);
        if(percentFromLast >= TEN_PERCENT || percentFromLast <= -(TEN_PERCENT)){
          pushSample(transportData->meterDistanceBuffer, meters);
        }
      } else {
        // It is farther away, so set the distance to 1000 miles
        *(transportData->transportDistPtr) = MIN_DIST_GETTING_SIGNAL;
      }
    }

}
