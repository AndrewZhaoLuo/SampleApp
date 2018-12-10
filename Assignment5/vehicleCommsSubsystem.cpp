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

  // Only if there is a new command to read
  if (*(vehicleData->schedVehicleCommsPtr)) {
    incomingByte = *(vehicleData->vehicleCommandPtr);
    // Send incoming byte to uno and get response
    Serial1.write(incomingByte);
    Serial.println("SENT");
  }


  while (Serial1.available() > 0){
    incomingResponse = Serial1.read();

    // Set global response
    *(vehicleData->vehicleResponsePtr) = incomingResponse;

    // Command successfully sent to mining vehicle
    if(incomingResponse == 'A'){
      Serial.print("A: ");
      Serial.println((char) toupper(incomingByte));
    }

    // Request for transport lift-off
    if(incomingResponse == 't' || incomingResponse == 'T'){
      Serial1.write('K');
    }

    // Request to dock: only confirm if vehicle is close to station
    if((incomingResponse == 'd' && *(vehicleData->transportDistPtr) <= 102) || (incomingResponse == 'D' && *(vehicleData->transportDistPtr) <= 102)){
      Serial1.write('C');
    }

    // Start image capture
    if(incomingResponse == 's' || incomingResponse == 'S'){
      Serial1.write('W');
    }

    // Send image data
    if(incomingResponse == 'i' || incomingResponse == 'I'){
      Serial1.write('P');
      int frequency = *(vehicleData->last_freq);

      // Convert to 4 bytes to send over serial
      Serial.print("Frequency: ");
      Serial.println(frequency);

      static int BUF_LENGTH = 4;
      static int MASK = 255;
      byte buf[BUF_LENGTH];

      for (int i = 0; i < BUF_LENGTH; i++) {
        buf[i] = (frequency >> (i * 8) & MASK);
      }
      //buf[0] = (frequency >> 0) & MASK;
      //buf[1] = (frequency >> 8) & MASK;
      //buf[2] = (frequency >> 16) & MASK;
      //buf[3] = (frequency >> 24) & MASK;
      Serial1.write(buf, sizeof(buf));
    }
  }
}
