#include <Arduino.h>

// because we will be using in C libraries, use C naming conventions
extern "C" {
  #include "print_format.h"
  #include "vehicleCommsSubsystem.h"
}

char incomingByte;
char response;

void vehicleCommsFunction(void* data) {
  // Cast to correct pointer
  vehicleCommsData* vehicleData = (vehicleCommsData*) data;

  if(Serial.available() > 0){
    incomingByte = Serial.read();
    *(vehicleData->vehicleCommandPtr) = toupper(incomingByte);
    // Send incoming byte to uno and get response
    Serial1.write(incomingByte);
    Serial.println("SENT");
  } 

  if (Serial1.available()){
    response = Serial1.read();
    // Set global response
    *(vehicleData->vehicleResponsePtr) = response;

    if(response == 'A'){
      Serial.print("A: ");
      Serial.println((char) toupper(incomingByte));
    }
  }
}
