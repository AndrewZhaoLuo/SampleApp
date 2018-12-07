#ifndef COMMANDSUBSYSTEM_H
#define COMMANDSUBSYSTEM_H

// Number of digits that must be provided for a valid thrust command
#define NUMBER_OF_DIGITS 5

// for TRUE/FALSE
#include "bool.h"

typedef struct commandDataStruct {
  char* commandPtr;
  char** responseMessagePtr;
  Bool* startTasksPtr;
  Bool* displayOnPtr;
  Bool* isNewResponsePtr;
  Bool* userThrustValuePtr;
  Bool* firePhasor;
  Bool* fireTorpedo;
  unsigned int* thrustCommandPtr;
} commandManagementData;

/*
See specification/report for full functionality
*/
void commandFunction(void* data);

void printIfSystemOn (char* message, commandManagementData* data);

#endif
