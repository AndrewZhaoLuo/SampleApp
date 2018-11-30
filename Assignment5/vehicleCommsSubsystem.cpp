// Serial will be used to communicate with the Putty terminal
// Serial1 will be used to communicate with the Arduino UNO

#include <Arduino.h>

// because we will be using in C libraries, use C naming conventions
extern "C" {
  #include "print_format.h"
  #include "vehicleCommsSubsystem.h"
}

char incomingByte;
char incomingResponse;

void vehicleCommsFunction(void* data) {
  // Cast to correct pointer
  vehicleCommsData* vehicleData = (vehicleCommsData*) data;

    incomingByte = *(vehicleData->vehicleCommandPtr);
    // Send incoming byte to uno and get response
    Serial1.write(incomingByte);
    Serial.println("SENT");


  while (Serial1.available() > 0){
    incomingResponse = Serial1.read();

    // Set global response
    *(vehicleData->vehicleResponsePtr) = incomingResponse;

    // Command successfully sent to mining vehicle
    if(incomingResponse == 'A'){
      Serial.print("A: ");
      Serial.println((char) toupper(incomingByte));
    }
    // Image complete
    else if (incomingResponse == 'W') {
      Serial.println("W");
    }
    // Image data
    else if (incomingResponse == 'P') {
      Serial.println("P");
    }

    // Request for transport lift-off
    if(incomingResponse == 't' || incomingResponse == 'T'){
      Serial1.write('K');
    }

    // Request to dock: only confirm if vehicle is close to station
    if((incomingResponse == 'd' && *(vehicleData->transportDistPtr) <= 102) || (incomingResponse == 'D' && *(vehicleData->transportDistPtr) <= 102)){
      Serial1.write('C');
    }
  }
}
