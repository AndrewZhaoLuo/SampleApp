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

      // Calculate time elapsed in millis
      unsigned long duration = ((endTime-startTime));

      // TODO: push timeInterval to time interval buffer (convert to seconds)

      double timeInterval = duration/((double) count * 1000.0);

      int miles = timeInterval * 200000.0;

      // If the transport vehicle is within 1 km, we know we register the signal
      if (miles <= 1000.0) {
        
        *(transportData->transportDistPtr) = ((unsigned short) miles);

        // TODO: push this distance to the transport distance buffer if greater than 10% from previous value
        /*if(std::abs(transportDistBuffer.getNthPreviousSample(0) - freq)/transportDistBuffer.getNthPreviousSample(0) >= 0.10){
          transportDistBuffer.pushSample(freq);
        }*/
      } else {
        // It is farther away, so set the distance to 1000 miles
        *(transportData->transportDistPtr) = 1000;
      }
    }
    
}
