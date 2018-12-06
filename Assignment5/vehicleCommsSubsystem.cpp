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

int numDigits(int number);

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
      int digits = numDigits(frequency);

      // Convert to 4 bytes to send over serial
      Serial.print("Frequency: ");
      Serial.println(frequency);
      
      byte buf[4];
      buf[0] = frequency & 255;
      buf[1] = (frequency >> 8) & 255;
      buf[2] = (frequency >> 16) & 255;
      buf[3] = (frequency >> 24) & 255;
      Serial1.write(buf, sizeof(buf));

    }
  }
}

int numDigits(int number){
  int digits = 0;
  while(number){
    number /= 10;
    digits++;
  }
  return digits;
}
