// Serial will be used to communicate with the Putty terminal
// Serial1 will be used to communicate with the Arduino UNO

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



  if (Serial1.available() > 0){
    response = Serial1.read();

    // Set global response
    *(vehicleData->vehicleResponsePtr) = response;

    // Command successfully sent to mining vehicle
    if(response == 'A'){
      Serial.print("A: ");
      Serial.println((char) toupper(incomingByte));
    }

    // Request for transport lift-off
    if(response == 't' || response == 'T'){
      Serial1.write('K');
    }

    // Request to dock: only confirm if vehicle is close to station
    if((response == 'd' && *(vehicleData->transportDistPtr) <= 102) || (response == 'D' && *(vehicleData->transportDistPtr) <= 102)){
      Serial1.write('C');
    }
  }
}
