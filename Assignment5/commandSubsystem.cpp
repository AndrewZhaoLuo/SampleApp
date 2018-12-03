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
  } else if (command == 'p' || command == 'P') {
    if(*(comManData->startTasksPtr)){
      *(comManData->startTasksPtr) = FALSE;
      *(comManData->responseMessagePtr) = "A: P";
      *(comManData->isNewResponsePtr) = TRUE;
    }
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
    
  } else if (command == 'm' || command == 'M') {
    
  } else { // Incorrect/non-existant command
    if(*(comManData->startTasksPtr)){
      *(comManData->responseMessagePtr) = "E";
      *(comManData->isNewResponsePtr) = TRUE;
    }
  }
}
