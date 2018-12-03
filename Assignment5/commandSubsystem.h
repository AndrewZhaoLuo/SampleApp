#ifndef COMMANDSUBSYSTEM_H
#define COMMANDSUBSYSTEM_H

// for TRUE/FALSE
#include "bool.h"

typedef struct commandDataStruct {
  char* commandPtr;
  char** responseMessagePtr;
  Bool* startTasksPtr;
  Bool* displayOnPtr;
  Bool* isNewResponsePtr;
} commandManagementData;

/*
See specification/report for full functionality
*/
void commandFunction(void* data);

void printIfSystemOn (char* message, commandManagementData* data);

#endif
