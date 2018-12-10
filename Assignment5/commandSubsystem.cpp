// Serial will be used to communicate with the Putty terminal
// Serial1 will be used to communicate with the Arduino UNO

#include <Arduino.h>

// because we will be using in C libraries, use C naming conventions
extern "C" {
  #include "commandSubsystem.h"
}

void commandFunction(void* data) {
  // Cast to correct pointer
  commandManagementData* comManData = (commandManagementData*) data;

  // Get the command
  char command = *(comManData->commandPtr);

  if (command == 's' || command == 'S') {
    *(comManData->startTasksPtr) = TRUE;
    *(comManData->responseMessagePtr) = "A: S";
    *(comManData->isNewResponsePtr) = TRUE;
  }

  else if(*(comManData->startTasksPtr)){
      if (command == 'p' || command == 'P') {
          *(comManData->startTasksPtr) = FALSE;
          *(comManData->responseMessagePtr) = "A: P";
          *(comManData->isNewResponsePtr) = TRUE;
      } else if (command == 'd' || command == 'D') {
        if(*(comManData->displayOnPtr)){
          *(comManData->displayOnPtr) = FALSE;
        } else {
          *(comManData->displayOnPtr) = TRUE;
        }
        if(*(comManData->startTasksPtr)){
          *(comManData->responseMessagePtr) = "A: D";
          *(comManData->isNewResponsePtr) = TRUE;
        }
      } else if (command == 't' || command == 'T') {
        // Since value must be between 0 and 65535, always make user type 5 digits
        while(Serial.available() < NUMBER_OF_DIGITS){
          // Wait until a valid number has arrived
        }
        char buffer[NUMBER_OF_DIGITS+1];
        int i;
        for (i = 0; i < NUMBER_OF_DIGITS; i++){
          buffer[i] = Serial.read();
        }
        buffer[i+1] = '\0';
        int thrustCommand = atoi(buffer);
        if(thrustCommand >= MIN_THRUST_COMMAND && thrustCommand <= MAX_THRUST_COMMAND){
          *(comManData->thrustCommandPtr) = thrustCommand;
          *(comManData->userThrustValuePtr) = TRUE;
          *(comManData->responseMessagePtr) = "A: T";
          *(comManData->isNewResponsePtr) = TRUE;
        } else {
          *(comManData->responseMessagePtr) = "E";
          *(comManData->isNewResponsePtr) = TRUE;
        }
      } else if (command == 'n' || command == 'N') {
        while(Serial.available() < NUM_INITIALS){
          // Wait until a valid number has arrived
        }
        int i;
        for (i = 0; i < NUM_INITIALS; i++){
          (*(comManData->initials))[i] = Serial.read();
        }
      } else if (command == 'y' || command == 'Y') {
        while(Serial.available() < NUM_FOR_DATE){
          // Wait until a valid number has arrived
        }
        int i;
        for (i = 0; i < NUM_FOR_DATE; i++){
          (*(comManData->date))[i] = Serial.read();
        }
      } else if (command == 'm' || command == 'M') {
        // Since value must be a character, wait for the next input letter
        while(Serial.available() < 1){
          // Wait until a valid number has arrived
        }
        char payload = Serial.read();

        // Determind the payload that is being asked for and send request body to satellite comms
        if(payload == 'b' || payload == 'B'){
          *(comManData->responseMessagePtr) = "M: Battery Level = ";
          *(comManData->isNewResponsePtr) = TRUE;
        } else if(payload == 'f' || payload == 'F'){
          *(comManData->responseMessagePtr) = "M: Fuel Level = ";
          *(comManData->isNewResponsePtr) = TRUE;
        } else if(payload == 'c' || payload == 'C'){
          *(comManData->responseMessagePtr) = "M: Power Consumption = ";
          *(comManData->isNewResponsePtr) = TRUE;
        } else if(payload == 's' || payload == 'S'){
          *(comManData->responseMessagePtr) = "M: Solar Panel State = ";
          *(comManData->isNewResponsePtr) = TRUE;
        } else if(payload == 'i' || payload == 'I'){
          *(comManData->responseMessagePtr) = "M: Image Data = ";
          *(comManData->isNewResponsePtr) = TRUE;
        } else if(payload == 'g' || payload == 'G'){
          *(comManData->responseMessagePtr) = "M: Power Generation = ";
          *(comManData->isNewResponsePtr) = TRUE;
        } else if(payload == 't' || payload == 'T'){
          *(comManData->responseMessagePtr) = "M: Battery Temperature = ";
          *(comManData->isNewResponsePtr) = TRUE;
        } else if(payload == 'd' || payload == 'D'){
          *(comManData->responseMessagePtr) = "M: Transport Distance = ";
          *(comManData->isNewResponsePtr) = TRUE;
        } else {
          *(comManData->responseMessagePtr) = "Invalid payload";
          *(comManData->isNewResponsePtr) = TRUE;
        }
      } else if (command == '1') {
          // fire phasors
          *(comManData -> firePhasor) = TRUE;
      } else if (command == '2') {
          // fire torpedos
          *(comManData -> fireTorpedo) = TRUE;
      }else { // Incorrect/non-existant command
        if(*(comManData->startTasksPtr)){
          *(comManData->responseMessagePtr) = "E";
          *(comManData->isNewResponsePtr) = TRUE;
        }
      }
  }
}
