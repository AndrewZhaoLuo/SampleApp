#include "transportDistanceSubsystem.h"
#include "globals.h"
#include "clock.h"
#include <Arduino.h>
#include "print_format.h"

void transportDistanceFunction(void* data) {
    // Cast to correct pointer
    transportDistanceData* transportData = (transportDistanceData*) data;

    // For debugging
    print_format("Transport dist connection flag: ");
    if (transportDistanceFreqConnectedFlag) {
      print_format("TRUE\n");
    } else {
      print_format("FALSE\n");
    }

    if(transportDistanceFreqConnectedFlag) {
      int curr = 0;
      int prev = 0;
      int count = 0;

      unsigned long long startTime = getTimeMillis();
      for(int i = 0; i < 10000; i++){
        prev = curr;
        curr = analogRead(DISTANCE_TRANSPORT_PIN);
        if(curr < CUTOFF && prev >= CUTOFF){
          count++;
        }
        if(count == 100){
          break;
        }
      }
      unsigned long long endTime = getTimeMillis();

      print_format("Count %d\n", count);

      // Calculate time elapsed in millis
      unsigned long duration = ((endTime-startTime));

      // Calculate time interval between peaks and push to interval buffer (millis)
      double timeInterval = duration/((double) count);

      print_format("Time interval: %d\n", (int) timeInterval);
      
      pushSample(*(transportData->timeIntervalBuffer), (int) timeInterval);

      double durationMS = ((double) duration)/1000.0;

      double frequency = ((double) count)/ durationMS;

      // For debugging
      print_format("Frequency: %d\n", (int) frequency);

      int meters;
      if(frequency > 2000) {
        meters = 100;
      } else if(frequency < 100){
        meters = 2000;
      } else {
        meters = 2100 - ((int) frequency);
      }

      print_format("meters: %d\n", meters);

      // If the transport vehicle is within 1 km, we know we register the signal
      if (meters <= 1000.0) {
        
        *(transportData->transportDistPtr) = ((unsigned short) meters);

        // Push this distance to the transport distance buffer if greater than 10% from previous value
        int previousSample = getNthPreviousSample(0, *(transportData->meterDistanceBuffer));
        double percentFromLast = ((double)(previousSample - meters))/((double) previousSample);
        if(percentFromLast >= 0.10 || percentFromLast <= -0.10){
          pushSample(*(transportData->meterDistanceBuffer), meters);
        }
      } else {
        // It is farther away, so set the distance to 1000 miles
        *(transportData->transportDistPtr) = 1000;
      }
    }
    
}
